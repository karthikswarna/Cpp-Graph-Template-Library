#ifndef EULERIAN_H
#define EULERIAN_H

#include "undirected_graph.hpp"

namespace Graph
{
    template<typename T, typename W>
    int undirected_graph<T, W>::isEulerian() const
    {
        // Empty graph is Eulerian.
        if(this->_ADJACENCY_LIST_.empty())
            return 2;

        // STEP-1: Check if all non-zero degree vertices are connected.
        unsigned int start;
        unsigned int numOfEdges = 0;
        std::unordered_set<unsigned int> Visited;
        for(const std::pair<unsigned int, std::vector<Node<W>>> &adj_list : this->_ADJACENCY_LIST_)
        {
            if(adj_list.second.size() > 0)
                start = adj_list.first;
            numOfEdges += adj_list.second.size();
        }
        numOfEdges /= 2;

        // If the graph has zero edges then it is Eulerian. 
        if(numOfEdges == 0)
            return 2;

        isEulerianUtil(start, Visited);

        // If any vertex is unvisited now, it is not connected => not Eulerian.
        for(const std::pair<unsigned int, std::vector<Node<W>>> &adj_list : this->_ADJACENCY_LIST_)
            if(Visited.find(adj_list.first) == Visited.end() && adj_list.second.size() > 0)
                return 0;


        // STEP-2: Find the number of odd-degree vertices.
        int oddVertices = 0;
        for(const std::pair<unsigned int, std::vector<Node<W>>> &vertex : this->_ADJACENCY_LIST_)
            if(vertex.second.size() & 1)
                oddVertices++;
        
        // If oddVertices > 2 then is not Eulerian.
        if(oddVertices > 2)
            return 0;

        // Return 1 if it has Eulerian Path(Semi-Eulerian), 2 if it has Eulerian Cycle.
        return (oddVertices == 2) ? 1 : 2;
    }

    template<typename T, typename W>
    void undirected_graph<T, W>::isEulerianUtil(unsigned int current, std::unordered_set<unsigned int> &Visited) const
    {
        // DFS.
        Visited.insert(current);

        for(const Node<W> &node: this->_ADJACENCY_LIST_.at(current))
            if(Visited.find(node.vertex) == Visited.end())
                isEulerianUtil(node.vertex, Visited);
    }

    template<typename T, typename W>
    std::vector<T> undirected_graph<T, W>::eulerianPath() const
    {
        // Empty Eulerian Path for empty graph.
        if(this->_ADJACENCY_LIST_.empty())
            return std::vector<T>();

        bool startFound = false;
        unsigned int numOfEdges = 0;
        unsigned int oddVertices = 0;
        unsigned int start = (this->_ADJACENCY_LIST_.begin())->first;
        std::unordered_map<unsigned int, unsigned int> Degree;

        // Finding the degree of all the vertices. Also finding the appropriate start node.
        for(const std::pair<unsigned int, std::vector<Node<W>>> &adj_list : this->_ADJACENCY_LIST_)
        {
            unsigned int node = adj_list.first;
            unsigned int size = adj_list.second.size();
            Degree[node] = size;
            numOfEdges += size;

            // If there are no odd degree vertices, this selects the start node with non-zero degree.
            if(startFound == false && size > 0)
                startFound = node;

            // If the degree is odd.
            if(Degree[node] & 1)
            {
                oddVertices++;
                startFound = true;
                start = node;
            }
        }
        // Each edge is present two times in adjacency list. So halve it.
        numOfEdges /= 2;


        // If oddVertices > 2 then the graph is not Eulerian. If numOfEdges == 0 then Eulerian path is empty. 
        if(oddVertices > 2 || numOfEdges == 0)
            return std::vector<T>();


        // Find Eulerian Path using DFS from 'start'.
        std::vector<T> Path;
        std::unordered_map<unsigned int, std::vector<Node<W>>> _ADJ_LIST_COPY_ = this->_ADJACENCY_LIST_;
        eulerianPathUtil(start, _ADJ_LIST_COPY_, Degree, Path);

        // If all non-zero degree vertices are connected then Eulerian Path is found, else return empty path.
        if(Path.size() != numOfEdges + 1)
            return std::vector<T>();
        
        return Path;
    }

    template<typename T, typename W>
    void undirected_graph<T, W>::eulerianPathUtil(unsigned int current, std::unordered_map<unsigned int, std::vector<Node<W>>> &_ADJ_LIST_COPY_, std::unordered_map<unsigned int, unsigned int> &Degree, std::vector<T> &Path) const
    {
        unsigned int &degree = Degree.at(current);
        unsigned int next_edge;

        // While the current node still has outgoing edges.
        while(degree != 0)
        {
            --degree;
            // If the edge is already visited, skip that edge.
            if(_ADJ_LIST_COPY_.at(current).at(degree) == Node<W>{0})
                continue;

            // Select the next unvisited edge, mark it visited, continue DFS from that edge.
            next_edge = _ADJ_LIST_COPY_.at(current).at(degree).vertex;
            _ADJ_LIST_COPY_.at(current).at(degree) = Node<W>{0};
            *( std::find(_ADJ_LIST_COPY_.at(next_edge).begin(), _ADJ_LIST_COPY_.at(next_edge).end(), current) ) = Node<W>{0};
            eulerianPathUtil(next_edge, _ADJ_LIST_COPY_, Degree, Path);
        }

        // Add current node to the solution.
        Path.push_back(this->_id_to_node_.at(current));
    }
};

#endif