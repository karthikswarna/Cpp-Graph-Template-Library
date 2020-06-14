#ifndef SIMPLE_GRAPH_H
#define SIMPLE_GRAPH_H

#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

namespace Graph
{
    template<typename T>
    class SimpleGraph
    {
        protected:
            std::unordered_map<unsigned int, std::vector<unsigned int>> _ADJACENCY_LIST_;
            std::unordered_map<unsigned int, T> _id_to_node_;
            std::unordered_map<T, unsigned int> _node_to_id_;
            unsigned int _id_{0};

        public:
            /*
             * SPECIAL MEMBER FUNCTIONS
             */
            // Default constructor
            SimpleGraph() noexcept;
            // Destructor
            ~SimpleGraph() noexcept;
            
            //Copy Constructor
            SimpleGraph(const SimpleGraph &) noexcept;
            // Copy assignment operator
            SimpleGraph& operator=(const SimpleGraph &) noexcept;
            
            // Move constructor
            SimpleGraph(SimpleGraph &&) noexcept;
            // Move assignment operator
            SimpleGraph& operator=(SimpleGraph &&) noexcept;


            /*
             * NON-CONST MEMBER FUNCTIONS
             */
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


            /*
             * CONST MEMBER FUNCTIONS
             */
            // Helper function to print DFS; takes starting vertex and set of visited vertices.
            void printDFS(unsigned int, std::unordered_set<unsigned int> &) const;
            // Function to print DFS; prints each connected component on different line.
            void printDFS() const;
            // Helper function to print BFS; takes starting vertex and set of visited vertices.
            void printBFS(unsigned int, std::unordered_set<unsigned int> &) const;
            // Function to print BFS; prints each connected component on different line.
            void printBFS() const;

            // Prints the Adjacency list of the graph.
            void printGraph() const;
            // Returns the degree of a vertex, if it exists. If the vertex doesn't exist, returns -1.
            int getDegree(T) const;
    };
}

#include "SimpleGraphDefs.hpp"

#endif