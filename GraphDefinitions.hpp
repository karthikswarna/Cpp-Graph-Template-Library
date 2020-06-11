#ifndef GRAPH_DEFINITIONS_H
#define GRAPH_DEFINITIONS_H

#include "Graph.hpp"

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
        for(typename std::unordered_map<T, std::vector<T>>::iterator it = _ADJACENCY_LIST_.begin(); it != _ADJACENCY_LIST_.end(); it++)
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
            for(typename std::unordered_map<T, std::vector<T>>::iterator it = _ADJACENCY_LIST_.begin(); it != _ADJACENCY_LIST_.end(); it++)
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
void Graph<T>::printDFS(const T &start, std::set<T> &Visited) const
{
    Visited.insert(start);
    std::cout << start;
    
    std::vector<T> edge_list = _ADJACENCY_LIST_.at(start);
    for(const T &v : edge_list)
    {
        if(Visited.find(v) == Visited.end())
        {
            std::cout << " -> ";
            printDFS(v, Visited);
        }
    }
}

template<typename T>
void Graph<T>::printDFS() const
{
    std::cout << "DEPTH FIRST SEARCH\n";

    std::set<T> Visited;
    for(const std::pair<T, std::vector<T>> &edges : _ADJACENCY_LIST_)
    {
        if(Visited.find(edges.first) == Visited.end())
        {
            printDFS(edges.first, Visited);
            std::cout << '\n';
        }
    }
}

template<typename T>
void Graph<T>::printBFS(const T &start, std::set<T> &Visited) const
{
    std::queue<T> Q;
    std::vector<T> path;
    T temp = start;
    Q.push(temp);
    Visited.insert(temp);

    while(!Q.empty())
    {
        temp = Q.front();
        Q.pop();
        path.push_back(temp);

        for(const T &v : _ADJACENCY_LIST_.at(temp))
        {
            if(Visited.find(v) == Visited.end())
            {
                Visited.insert(v);
                Q.push(v);
            }
        }
    }

    for(typename std::vector<T>::iterator it = path.begin(); it < path.end(); it++)
    {
        std::cout << *it;

        if(it != path.end() - 1)
            std::cout << " -> ";
    }
    std::cout << '\n';
}

template<typename T>
void Graph<T>::printBFS() const
{
    std::cout << "BREADTH FIRST SEARCH" << '\n';

    std::set<T> Visited;
    for(const std::pair<T, std::vector<T>> &edges : _ADJACENCY_LIST_)
    {
        if(Visited.find(edges.first) == Visited.end())
        {
            Visited.insert(edges.first);
            printBFS(edges.first, Visited);
        }
    }
}

template<typename T>
void Graph<T>::printGraph() const
{
    std::cout << "ADJACENCY LIST" << '\n';
    for(const std::pair<T, std::vector<T>> &e : _ADJACENCY_LIST_)
    {
        std::cout << e.first << " ->  ";
        for(typename std::vector<T>::const_iterator it = e.second.begin(); it < e.second.end(); it++)
        {
            std::cout << *it;
            if(it != e.second.end() - 1)
                std::cout << ", ";
        }
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