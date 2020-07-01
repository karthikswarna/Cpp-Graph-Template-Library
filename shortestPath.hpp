#ifndef SHORTEST_PATH_H
#define SHORTEST_PATH_H

#include "UndirectedGraph.hpp"

namespace Graph
{
    template<typename T, typename W>
    long long UndirectedGraph<T, W>::shortestDistance(T start, T end) const
    {
        // If any of the vertex is invalid, return -1.
        if(this->_node_to_id_.find(start) == this->_node_to_id_.end() || this->_node_to_id_.find(end) == this->_node_to_id_.end())
            return -1;


        if(isNegWeighted)
            bellmanFord();
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
            bellmanFord();
        else
        {
            if(isWeighted)
            {
                unsigned int s = this->_node_to_id_.at(start);
                unsigned int e = this->_node_to_id_.at(end);
                unsigned int minDist;
                std::unordered_map<unsigned int, unsigned int> Prev;
                std::tie(minDist, Prev) = Dijkstra(s, e);
                
                std::vector<T> Path;
                // If the vertex is unreachable, return empty path.
                if(minDist == -1)
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
        constexpr bool operator()(const std::pair<unsigned int, unsigned int> &a, const std::pair<unsigned int, unsigned int> &b) const noexcept
        {
            return a.second > b.second;
        }
    };

    template<typename T, typename W>
    std::tuple<long long, std::unordered_map<unsigned int, unsigned int>> UndirectedGraph<T, W>::Dijkstra(unsigned int start, unsigned int end) const
    {
        typedef std::pair<unsigned int, long long> pair;

        std::unordered_set<unsigned int> Visited;
        std::priority_queue<pair, std::vector<pair>, comp> Q;
        std::unordered_map<unsigned int, long long> Distance;
        std::unordered_map<unsigned int, unsigned int> Prev;
        unsigned int minDist = 0;
        unsigned int newDist = 0;
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
                return std::tuple<long long, std::unordered_map<unsigned int, unsigned int>>(Distance[end], Prev);

            // After exploring the current vertex, add it to visited set.
            Visited.insert(start);
        }

        // If the end node is unreachable, distance is infinity.
        if(Distance.find(end) == Distance.end())
            return std::tuple<long long, std::unordered_map<unsigned int, unsigned int>>(-1, Prev);

        return std::tuple<long long, std::unordered_map<unsigned int, unsigned int>>(Distance[end], Prev);
    }

    template<typename T, typename W>
    void UndirectedGraph<T, W>::bellmanFord() const
    {

    }

    template<typename T, typename W>
    void UndirectedGraph<T, W>::bidirectionalSearch() const
    {

    }
}

#endif