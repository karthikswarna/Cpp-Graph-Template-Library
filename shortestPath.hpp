#ifndef SHORTEST_PATH_H
#define SHORTEST_PATH_H

#include "UndirectedGraph.hpp"

namespace Graph
{
    template<typename T, typename W>
    double UndirectedGraph<T, W>::shortestDistance(T start, T end) const
    {
        // If any of the vertex is invalid, return -1.
        if(this->_node_to_id_.find(start) == this->_node_to_id_.end() || this->_node_to_id_.find(end) == this->_node_to_id_.end())
            return -1;


        if(isNegWeighted)
            return std::get<0>(bellmanFord(this->_node_to_id_.at(start), this->_node_to_id_.at(end)));
        else
        {
            if(isWeighted)
                return std::get<0>(Dijkstra(this->_node_to_id_.at(start), this->_node_to_id_.at(end)));
            else
                bidirectionalSearch();                
        }
    }

    template<typename T, typename W>
    std::vector<T> UndirectedGraph<T, W>::shortestPath(T start, T end) const
    {
        // If any of the vertex is invalid, return empty vector.
        if(this->_node_to_id_.find(start) == this->_node_to_id_.end() || this->_node_to_id_.find(end) == this->_node_to_id_.end())
            return std::vector<T>();


        if(isNegWeighted)
        {
            unsigned int s = this->_node_to_id_.at(start);
            unsigned int e = this->_node_to_id_.at(end);
            double minDist;
            std::unordered_map<unsigned int, unsigned int> Prev;
            std::tie(minDist, Prev) = bellmanFord(s, e);
            
            std::vector<T> Path;
            // If the vertex is unreachable, return empty path.
            if(minDist == std::numeric_limits<double>::infinity() || minDist == std::numeric_limits<double>::infinity() * -1)
                return Path;
            
            // Reconstructing the path.
            for(unsigned int curr = e; ; curr = Prev.at(curr))
            {
                Path.push_back(this->_id_to_node_.at(curr));
                if(curr == s) break;
            }
            std::reverse(Path.begin(), Path.end());

            return Path;
        }
        else
        {
            if(isWeighted)
            {
                unsigned int s = this->_node_to_id_.at(start);
                unsigned int e = this->_node_to_id_.at(end);
                double minDist;
                std::unordered_map<unsigned int, unsigned int> Prev;
                std::tie(minDist, Prev) = Dijkstra(s, e);
                
                std::vector<T> Path;
                // If the vertex is unreachable, return empty path.
                if(minDist == std::numeric_limits<double>::infinity())
                    return Path;
                
                // Reconstructing the path.
                for(unsigned int curr = e; ; curr = Prev.at(curr))
                {
                    Path.push_back(this->_id_to_node_.at(curr));
                    if(curr == s) break;
                }
                std::reverse(Path.begin(), Path.end());

                return Path;
            }
            else
                bidirectionalSearch();                
        }
    }

    struct comp
    { 
        constexpr bool operator()(const std::pair<unsigned int, double> &a, const std::pair<unsigned int, double> &b) const noexcept
        {
            return a.second > b.second;
        }
    };

    template<typename T, typename W>
    std::tuple<double, std::unordered_map<unsigned int, unsigned int>> UndirectedGraph<T, W>::Dijkstra(unsigned int start, unsigned int end) const
    {
        typedef std::pair<unsigned int, double> pair;

        std::unordered_set<unsigned int> Visited;
        std::priority_queue<pair, std::vector<pair>, comp> Q;   // (vertex - distance) priority queue.
        std::unordered_map<unsigned int, double> Distance;      // (vertex - bestDistance) mapping.
        std::unordered_map<unsigned int, unsigned int> Prev;    // (child - parent) mapping.
        double minDist = 0;
        double newDist = 0;
        Distance[start] = 0;
        Q.push(pair(start, 0));

        while(!Q.empty())
        {
            // Select the next best node to explore(best - min distance).
            start = Q.top().first;
            minDist = Q.top().second;
            Q.pop();
            
            // If the distance found for the vertex is less than distance in current pair, then discard it.
            if(Distance.find(start) != Distance.end() && Distance[start] < minDist)
                continue;
            
            for(const Node<W> &node : this->_ADJACENCY_LIST_.at(start))
            {
                // The best distance for a vertex cannot be updated, if the vertex is already completely explored(exploring - exploring its neighbours).
                if(Visited.find(node.vertex) == Visited.end())
                {
                    // If next better distance is found or if the distance for the vertex is infinity.
                    newDist = Distance[start] + node.weight;
                    if(Distance.find(node.vertex) == Distance.end() || newDist < Distance[node.vertex])
                    {
                        Distance[node.vertex] = newDist;
                        Prev[node.vertex] = start;
                        Q.push(pair(node.vertex, newDist));
                    }
                }
            }

            // Early stopping condition.
            if(start == end)
                return std::tuple<double, std::unordered_map<unsigned int, unsigned int>>(Distance[end], Prev);

            // After exploring the current vertex, add it to visited set.
            Visited.insert(start);
        }

        // If the end node is unreachable, distance is infinity.
        if(Distance.find(end) == Distance.end())
            return std::tuple<double, std::unordered_map<unsigned int, unsigned int>>(std::numeric_limits<double>::infinity(), Prev);

        return std::tuple<double, std::unordered_map<unsigned int, unsigned int>>(Distance[end], Prev);
    }

    template<typename T, typename W>
    std::tuple<double, std::unordered_map<unsigned int, unsigned int>> UndirectedGraph<T, W>::bellmanFord(unsigned int start, unsigned int end) const
    {
        std::unordered_map<unsigned int, double> Distance;
        std::unordered_map<unsigned int, unsigned int> Prev;
        double newDist = 0;
        int V = this->_node_to_id_.size();
        Distance[start] = 0;

        for(int i = 1; i <= V - 1; ++i)
        {
            for(const std::pair<unsigned int, std::vector<Node<W>>> &edge_list : this->_ADJACENCY_LIST_)
            {
                if(Distance.find(edge_list.first) == Distance.end())
                    Distance[edge_list.first] = std::numeric_limits<double>::infinity();
                
                for(const Node<W> &node : edge_list.second)
                {
                    newDist = Distance[edge_list.first] + node.weight;
                    if(Distance.find(node.vertex) == Distance.end() || newDist < Distance[node.vertex])
                    {
                        Distance[node.vertex] = newDist;
                        Prev[node.vertex] = edge_list.first;
                    }
                }
            }
        }
        
        // V - 1 iterations are necessary to detect all vertices which are part of negative cycle and also vertices that can be reached form the cycle.
        for(int i = 1; i <= V - 1; ++i)
        {
            for(const std::pair<unsigned int, std::vector<Node<W>>> &edge_list : this->_ADJACENCY_LIST_)
            {
                for(const Node<W> &node : edge_list.second)
                {
                    if(Distance[edge_list.first] + node.weight < Distance[node.vertex])
                        Distance[node.vertex] = std::numeric_limits<double>::infinity() * -1;
                }
            }
        }

        return std::tuple<double, std::unordered_map<unsigned int, unsigned int>>(Distance[end], Prev);
    }

    template<typename T, typename W>
    void UndirectedGraph<T, W>::bidirectionalSearch() const
    {

    }
}

#endif