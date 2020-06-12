#ifndef DIRECTED_GRAPH_DEFINITIONS_H
#define DIRECTED_GRAPH_DEFINITIONS_H

#include "DirectedGraph.hpp"

namespace Graph
{
    template<typename T>
    DirectedGraph<T>::DirectedGraph() {}

    template<typename T>
    DirectedGraph<T>::~DirectedGraph() { this->_ADJACENCY_LIST_.clear(); }

    template<typename T>
    bool DirectedGraph<T>::addEdge(T vertex1, T vertex2)
    {
        try
        {
            if(this->_ADJACENCY_LIST_.find(vertex1) == this->_ADJACENCY_LIST_.end())
            {
                this->_ADJACENCY_LIST_[vertex1] = std::vector<T>{vertex2};
            }
            else
            {
                std::vector<T> edge_list = this->_ADJACENCY_LIST_.at(vertex1);
                if(std::find(edge_list.begin(), edge_list.end(), vertex2) == edge_list.end())
                    this->_ADJACENCY_LIST_.at(vertex1).push_back(vertex2);
            }

            return true;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            return false;
        }
    }

    template<typename T>
    bool DirectedGraph<T>::addEdges(const std::vector<std::pair<T, T>> &edges)
    {
        try
        {
            for(const std::pair<T, T> &e : edges)
            {
                T vertex1 = e.first;
                T vertex2 = e.second;
                if(this->_ADJACENCY_LIST_.find(vertex1) == this->_ADJACENCY_LIST_.end())
                {
                    this->_ADJACENCY_LIST_[vertex1] = std::vector<T>{vertex2};
                }
                else
                {
                    std::vector<T> edge_list = this->_ADJACENCY_LIST_.at(vertex1);
                    if(std::find(edge_list.begin(), edge_list.end(), vertex2) == edge_list.end())
                        this->_ADJACENCY_LIST_.at(vertex1).push_back(vertex2);
                }
            }

            return true;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            return false;
        }    
    }

    template<typename T>
    bool DirectedGraph<T>::removeEdge(T vertex1, T vertex2)
    {
        try
        {
            if(this->_ADJACENCY_LIST_.find(vertex1) != this->_ADJACENCY_LIST_.end())
            {
                std::vector<T> &edge_list = this->_ADJACENCY_LIST_.at(vertex1);
                if(std::find(edge_list.begin(), edge_list.end(), vertex2) != edge_list.end())
                {
                    edge_list.erase(std::remove(edge_list.begin(), edge_list.end(), vertex2));
                }
            }

            return true;
        }
        catch(const std::exception& e)
        {
            std::cout << e.what() << '\n';
            return false;
        }
    }

    template<typename T>
    bool DirectedGraph<T>::removeEdges(const std::vector<std::pair<T, T>> &edges)
    {
        try
        {
            for(const std::pair<T, T> &e : edges)
            {
                T vertex1 = e.first;
                T vertex2 = e.second;
    
                if(this->_ADJACENCY_LIST_.find(vertex1) != this->_ADJACENCY_LIST_.end())
                {
                    std::vector<T> &edge_list = this->_ADJACENCY_LIST_.at(vertex1);
                    if(std::find(edge_list.begin(), edge_list.end(), vertex2) != edge_list.end())
                    {
                        edge_list.erase(std::remove(edge_list.begin(), edge_list.end(), vertex2));
                    }
                }
            }

            return true;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            return false;
        }
    }

    template<typename T>
    std::pair<int, int> DirectedGraph<T>::getDegree(T vertex) const
    {
        if(this->_ADJACENCY_LIST_.find(vertex) != this->_ADJACENCY_LIST_.end())
        {
            int out_degree = this->_ADJACENCY_LIST_.at(vertex).size();
            int in_degree = 0;
            for(const std::pair<T, std::vector<T>> &edges : this->_ADJACENCY_LIST_)
            {
                if(std::find(edges.second.begin(), edges.second.end(), vertex) != edges.second.end())
                    in_degree++;
            }

            return std::pair<int, int>(in_degree, out_degree);
        }
        else
            return std::pair<int, int>(-1, -1);
    }
}

#endif