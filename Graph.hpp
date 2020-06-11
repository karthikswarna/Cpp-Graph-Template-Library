#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>

template<typename T>
class Graph
{
private:
    std::unordered_map<T, std::vector<T>> _ADJACENCY_LIST_;

public:
    Graph();
    ~Graph();

    bool addVertex(T);
    bool addVertices(const std::vector<T> &);
    bool addEdge(T, T);
    bool addEdges(const std::vector<std::pair<T, T>> &);
    
    bool removeVertex(T);
    bool removeVertices(const std::vector<T> &);
    bool removeEdge(T, T);
    bool removeEdges(const std::vector<std::pair<T, T>> &);

    
    void printGraph() const;
    int getDegree(T) const;
};

template<typename T>
Graph<T>::Graph() {}

template<typename T>
Graph<T>::~Graph() { _ADJACENCY_LIST_.clear(); }

template<typename T>
bool Graph<T>::addVertex(T vertex)
{
    try
    {
        _ADJACENCY_LIST_.insert(make_pair(vertex, std::vector<T>()));
        return true;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
}

template<typename T>
bool Graph<T>::addVertices(const std::vector<T> &vertices)
{
    try
    {
        for(const T &v : vertices)
        {
            _ADJACENCY_LIST_.insert(make_pair(v, std::vector<T>()));
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
bool Graph<T>::addEdge(T vertex1, T vertex2)
{
    try
    {
        if(_ADJACENCY_LIST_.find(vertex1) == _ADJACENCY_LIST_.end())
        {
            _ADJACENCY_LIST_[vertex1] = std::vector<T>{vertex2};
        }
        else
        {
            std::vector<T> edge_list = _ADJACENCY_LIST_.at(vertex1);
            if(std::find(edge_list.begin(), edge_list.end(), vertex2) == edge_list.end())
                _ADJACENCY_LIST_.at(vertex1).push_back(vertex2);
        }

        if(_ADJACENCY_LIST_.find(vertex2) == _ADJACENCY_LIST_.end())
        {
            _ADJACENCY_LIST_[vertex2] = std::vector<T>{vertex1};
        }
        else
        {
            std::vector<T> edge_list = _ADJACENCY_LIST_.at(vertex2);
            if(std::find(edge_list.begin(), edge_list.end(), vertex1) == edge_list.end())
                _ADJACENCY_LIST_.at(vertex2).push_back(vertex1);
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
bool Graph<T>::addEdges(const std::vector<std::pair<T, T>> &edges)
{
    try
    {
        for(const std::pair<T, T> &e : edges)
        {
            T vertex1 = e.first;
            T vertex2 = e.second;
            if(_ADJACENCY_LIST_.find(vertex1) == _ADJACENCY_LIST_.end())
            {
                _ADJACENCY_LIST_[vertex1] = std::vector<T>{vertex2};
            }
            else
            {
                std::vector<T> edge_list = _ADJACENCY_LIST_.at(vertex1);
                if(std::find(edge_list.begin(), edge_list.end(), vertex2) == edge_list.end())
                    _ADJACENCY_LIST_.at(vertex1).push_back(vertex2);
            }

            if(_ADJACENCY_LIST_.find(vertex2) == _ADJACENCY_LIST_.end())
            {
                _ADJACENCY_LIST_[vertex2] = std::vector<T>{vertex1};
            }
            else
            {
                std::vector<T> edge_list = _ADJACENCY_LIST_.at(vertex2);
                if(std::find(edge_list.begin(), edge_list.end(), vertex1) == edge_list.end())
                    _ADJACENCY_LIST_.at(vertex2).push_back(vertex1);
            }
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }    
}

template<typename T>
bool Graph<T>::removeVertex(T vertex)
{
    try
    {
        _ADJACENCY_LIST_.erase(vertex);
        for(auto it = _ADJACENCY_LIST_.begin(); it != _ADJACENCY_LIST_.end(); it++)
        {
            if(std::find(it->second.begin(), it->second.end(), vertex) != it->second.end())
            {
                it->second.erase(std::remove(it->second.begin(), it->second.end(), vertex));
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
bool Graph<T>::removeVertices(const std::vector<T> &vertices)
{
    try
    {
        for(const T &vertex : vertices)
        {
            _ADJACENCY_LIST_.erase(vertex);
            for(auto it = _ADJACENCY_LIST_.begin(); it != _ADJACENCY_LIST_.end(); it++)
            {
                if(std::find(it->second.begin(), it->second.end(), vertex) != it->second.end())
                {
                    it->second.erase(std::remove(it->second.begin(), it->second.end(), vertex));
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
bool Graph<T>::removeEdge(T vertex1, T vertex2)
{
    try
    {
        std::vector<T> &edge_list1 = _ADJACENCY_LIST_.at(vertex1);
        if(std::find(edge_list1.begin(), edge_list1.end(), vertex2) != edge_list1.end())
        {
            edge_list1.erase(std::remove(edge_list1.begin(), edge_list1.end(), vertex2));
        }

        std::vector<T> &edge_list2 = _ADJACENCY_LIST_.at(vertex2);
        if(std::find(edge_list2.begin(), edge_list2.end(), vertex1) != edge_list2.end())
        {
            edge_list2.erase(std::remove(edge_list2.begin(), edge_list2.end(), vertex1));
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
bool Graph<T>::removeEdges(const std::vector<std::pair<T, T>> &edges)
{
    try
    {
        for(const std::pair<T, T> &e : edges)
        {
            T vertex1 = e.first;
            T vertex2 = e.second;
            std::vector<T> &edge_list1 = _ADJACENCY_LIST_.at(vertex1);
            if(std::find(edge_list1.begin(), edge_list1.end(), vertex2) != edge_list1.end())
            {
                edge_list1.erase(std::remove(edge_list1.begin(), edge_list1.end(), vertex2));
            }

            std::vector<T> &edge_list2 = _ADJACENCY_LIST_.at(vertex2);
            if(std::find(edge_list2.begin(), edge_list2.end(), vertex1) != edge_list2.end())
            {
                edge_list2.erase(std::remove(edge_list2.begin(), edge_list2.end(), vertex1));
            }
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
}

template<typename T>
void Graph<T>::printGraph() const
{
    std::cout << "ADJACENCY LIST" << '\n';
    for(const std::pair<T, std::vector<T>> &e : _ADJACENCY_LIST_)
    {
        std::cout << e.first << " ->  ";
        for(const T &i : e.second)
            std::cout << i << ", ";
        std::cout << '\n';
    }
}

template<typename T>
int Graph<T>::getDegree(T vertex) const
{
    if(_ADJACENCY_LIST_.find(vertex) != _ADJACENCY_LIST_.end())
        return _ADJACENCY_LIST_.at(vertex).size();
    else
        return -1;
}

#endif