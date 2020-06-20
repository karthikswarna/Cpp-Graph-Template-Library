#ifndef UNDIRECTED_GRAPH_H
#define UNDIRECTED_GRAPH_H

#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

namespace Graph
{
    template<typename T>
    class UndirectedGraph
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
            // Default constructor.
            UndirectedGraph() noexcept;
            // Destructor.
            ~UndirectedGraph() noexcept;
            
            //Copy Constructor.
            UndirectedGraph(const UndirectedGraph &) noexcept;
            // Copy assignment operator.
            UndirectedGraph& operator=(const UndirectedGraph &) noexcept;
            
            // Move constructor.
            UndirectedGraph(UndirectedGraph &&) noexcept;
            // Move assignment operator.
            UndirectedGraph& operator=(UndirectedGraph &&) noexcept;

            // Overloaded equality operator.
            bool operator==(const UndirectedGraph &) const;
            // Overloaded inequality operator.
            bool operator!=(const UndirectedGraph &) const;


            /*
             * NON-CONST MEMBER FUNCTIONS
             */
            // Swaps the internal data structures of the given graphs.
            void swap(UndirectedGraph &);

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
            // Returns true if the graph is empty, else false. 
            bool empty() const;

            /*
             * ITERATOR-RELATED FUNCTIONS
             */
            class node_iterator;
            class const_node_iterator;
            class edge_iterator;
            class const_edge_iterator;

            node_iterator begin();
            node_iterator end();
            const_node_iterator begin() const;
            const_node_iterator cbegin() const;
            const_node_iterator end() const;
            const_node_iterator cend() const;

            edge_iterator begin(int);
            edge_iterator end(int);
            const_edge_iterator begin(int) const;
            const_edge_iterator cbegin(int) const;
            const_edge_iterator end(int) const;
            const_edge_iterator cend(int) const;
    };
}

#include "UndirectedGraphDefs.hpp"
#include "const_node_iterator.hpp"
#include "const_edge_iterator.hpp"
#include "node_iterator.hpp"
#include "edge_iterator.hpp"

#endif