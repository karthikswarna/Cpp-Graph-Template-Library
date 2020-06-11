#ifndef GRAPH_H
#define GRAPH_H

#include <set>
#include <queue>
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

    // Given an object, adds it to the graph, if it doesn't exist already.
    bool addVertex(T);
    // Given a list of objects, adds each of them to the graph, if it doesn't exist already.
    bool addVertices(const std::vector<T> &);
    // Given two objects, adds the edge between them to the graph, if it doesn't exist already.
    bool addEdge(T, T);
    // Given a list of pair of objects, adds each edge to the graph, if it doesn't exist already.
    bool addEdges(const std::vector<std::pair<T, T>> &);
    
    // Given an object, removes it and its edges from the graph, if it exists.
    bool removeVertex(T);
    // Given a list of objects, removes each of them and its edges from the graph, if it exists.
    bool removeVertices(const std::vector<T> &);
    // Given two objects, removes the edge between them from the graph, if it exists.
    bool removeEdge(T, T);
    // Given a list of pair of objects, removes each edge from the graph, if it exists.
    bool removeEdges(const std::vector<std::pair<T, T>> &);

    // Helper function to print DFS; takes starting vertex and set of visited vertices.
    void printDFS(const T &, std::set<T> &) const;
    // Function to print DFS; prints each connected component on different line.
    void printDFS() const;
    // Helper function to print BFS; takes starting vertex and set of visited vertices.
    void printBFS(const T &, std::set<T> &) const;
    // Function to print BFS; prints each connected component on different line.
    void printBFS() const;

    // Prints the Adjacency list of the graph.
    void printGraph() const;
    // Returns the degree of a vertex, if it exists. If the vertex doesn't exist, returns -1.
    int getDegree(T) const;
};

#include "GraphDefinitions.hpp"

#endif