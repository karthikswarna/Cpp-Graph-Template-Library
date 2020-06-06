#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <vector>

template<typename T>
class Graph
{
private:
    std::unordered_map<T, std::vector<T>> _ADJACENCY_LIST_;

public:
    Graph(int);

    bool addVertex(T x);
    bool addVertices(std::vector<T>);
    bool addEdge(T x, T y);
    bool addEdges(std::vector<std::pair<T, T>>);
    
    bool removeVertex(T x);
    bool removeVertices(std::vector<T>);
    bool removeEdge(T x, T y);
    bool removeEdges(std::vector<std::pair<T, T>>);

    int getDegree(T x);
};

#endif