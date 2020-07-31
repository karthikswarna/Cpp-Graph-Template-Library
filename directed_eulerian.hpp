#ifndef DIRECTED_EULERIAN_H
#define DIRECTED_EULERIAN_H

#include "directed_graph.hpp"

namespace Graph
{
    template<typename T, typename W>
    int directed_graph<T, W>::isEulerian() const
    {
        // Empty graph is Eulerian.
        if(this->_ADJACENCY_LIST_.empty())
            return 2;

        // STEP-1: Check if all non-zero degree vertices are connected. If the number of SCC's with more than one node > 1 then graph is disconnected => not Eulerian. 
        std::vector<std::vector<T>> SCC = stronglyConnectedComponents();
        if(std::count_if(SCC.begin(), SCC.end(), [](std::vector<T> CC){ return (CC.size() > 1); }) > 1)
            return 0;


        // STEP-2: Finding the in-degree and out-degree of all the vertices.
        unsigned numOfEdges = 0;
        std::unordered_map<unsigned int, unsigned int> Indegree;
        std::unordered_map<unsigned int, unsigned int> Outdegree;
        for(const std::pair<unsigned int, std::vector<Node<W>>> &adj_list : this->_ADJACENCY_LIST_)
        {
            unsigned int id = adj_list.first;

            int out_degree = adj_list.second.size();
            int in_degree = 0;
            for(const std::pair<unsigned int, std::vector<Node<W>>> &adj_list2 : this->_ADJACENCY_LIST_)
            {
                if(std::find(adj_list2.second.begin(), adj_list2.second.end(), id) != adj_list2.second.end())
                    in_degree++;
            }

            numOfEdges += out_degree;
            Indegree[id] = in_degree;
            Outdegree[id] = out_degree;
        }
        // If the graph has zero edges then it is Eulerian. 
        if(numOfEdges == 0)
            return 2;

        // Deciding whether Eulerian, Semi-Eulerian, not EUlerian.
        unsigned int startCount = 0, endCount = 0;
        for(const std::pair<unsigned int, std::vector<Node<W>>> &adj_list : this->_ADJACENCY_LIST_)
        {
            unsigned int vertex = adj_list.first;

            if(Outdegree[vertex] - Indegree[vertex] > 1 || Indegree[vertex] - Outdegree[vertex] > 1)
                return 0;
            else if(Outdegree[vertex] - Indegree[vertex] == 1)
                startCount++;
            else if(Indegree[vertex] - Outdegree[vertex] == 1)
                endCount++;
        }
        if(!((startCount == 0 && endCount == 0) || (startCount == 1 && endCount == 1)))
            return 0;
        
        return (startCount == 1 && endCount == 1) ? 1 : 2;
    }

    template<typename T, typename W>
    std::vector<T> directed_graph<T, W>::eulerianPath() const
    {
        // Return empty Eulerian Path for empty graph.
        if(this->_ADJACENCY_LIST_.empty())
            return std::vector<T>();

        // Finding the in-degree and out-degree of all the vertices.
        unsigned numOfEdges = 0;
        std::unordered_map<unsigned int, unsigned int> Indegree;
        std::unordered_map<unsigned int, unsigned int> Outdegree;
        for(const std::pair<unsigned int, std::vector<Node<W>>> &adj_list : this->_ADJACENCY_LIST_)
        {
            unsigned int id = adj_list.first;

            int out_degree = adj_list.second.size();
            int in_degree = 0;
            for(const std::pair<unsigned int, std::vector<Node<W>>> &adj_list2 : this->_ADJACENCY_LIST_)
            {
                if(std::find(adj_list2.second.begin(), adj_list2.second.end(), id) != adj_list2.second.end())
                    in_degree++;
            }

            numOfEdges += out_degree;
            Indegree[id] = in_degree;
            Outdegree[id] = out_degree;
        }
        if(numOfEdges == 0)
            return std::vector<T>();


        // Checking if the graph is Eulerian.
        unsigned int startCount = 0, endCount = 0;
        for(const std::pair<unsigned int, std::vector<Node<W>>> &adj_list : this->_ADJACENCY_LIST_)
        {
            unsigned int vertex = adj_list.first;

            if(Outdegree[vertex] - Indegree[vertex] > 1 || Indegree[vertex] - Outdegree[vertex] > 1)
                return std::vector<T>();
            else if(Outdegree[vertex] - Indegree[vertex] == 1)
                startCount++;
            else if(Indegree[vertex] - Outdegree[vertex] == 1)
                endCount++;
        }
        if(!((startCount == 0 && endCount == 0) || (startCount == 1 && endCount == 1)))
            return std::vector<T>();


        // Finding the starting node for DFS.
        unsigned int start;
        for(const std::pair<unsigned int, std::vector<Node<W>>> &adj_list : this->_ADJACENCY_LIST_)
        {
            unsigned int vertex = adj_list.first;

            if(Outdegree[vertex] - Indegree[vertex] == 1)
            {
                start = vertex;
                break;
            }
            if(Outdegree[vertex] > 0)
                start = vertex;
        }


        // DFS.
        std::vector<T> Path;
        eulerianPathUtil(start, Outdegree, Path);
        std::reverse(Path.begin(), Path.end());

        // If the graph is disconnected, Eulerian path doesn't exist.
        if(Path.size() != numOfEdges + 1)
            return std::vector<T>();   
    
        return Path;
    }

    template<typename T, typename W>
    void directed_graph<T, W>::eulerianPathUtil(unsigned int current, std::unordered_map<unsigned int, unsigned int> &Outdegree, std::vector<T> &Path) const
    {
        unsigned int &degree = Outdegree.at(current);
        unsigned int next_edge;

        // While the current node still has outgoing edges.
        while(degree != 0)
        {
            // Select the next unvisited edge, mark it visited, continue DFS from that edge.
            next_edge = this->_ADJACENCY_LIST_.at(current).at(--degree).vertex;
            eulerianPathUtil(next_edge, Outdegree, Path);
        }

        // Add current node to the solution.
        Path.push_back(this->_id_to_node_.at(current));
    }
};

#endif