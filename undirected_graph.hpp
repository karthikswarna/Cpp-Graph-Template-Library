#ifndef UNDIRECTED_GRAPH_H
#define UNDIRECTED_GRAPH_H

#include <stack>
#include <queue>
#include <tuple>
#include <vector>
#include <climits>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

namespace Graph
{
    template<typename W = int>
    class Node
    {
        static_assert(std::is_arithmetic<W>::value, "\"Weight type must be numeric\"");

        public:
            unsigned int vertex;
            W weight;

            Node(unsigned int v) : vertex (v)
            {
                weight = 1;
            }
            Node(unsigned int v, W w) : vertex (v), weight(w)
            {
            }

            bool operator==(const unsigned int v) const
            {
                return vertex == v;
            }

            bool operator==(const Node &N) const
            {
                return vertex == N.vertex && weight == N.weight;
            }
    };

    template<typename T, typename W = int>
    class undirected_graph
    {   
        protected:
            std::unordered_map<unsigned int, std::vector<Node<W>>> _ADJACENCY_LIST_;
            std::unordered_map<unsigned int, T> _id_to_node_;
            std::unordered_map<T, unsigned int> _node_to_id_;
            bool isNegWeighted{false};
            bool isWeighted{false};
            unsigned int _id_{1};       // 0 can be used as sentinel.

            // Function to check whether the graph is still weighted/negative Weighted.
            void checkGraph();
        public:
            /*
             *  SPECIAL MEMBER FUNCTIONS
             */
            // Default constructor.
            undirected_graph() noexcept;
            // Destructor.
            ~undirected_graph() noexcept;
            
            //Copy Constructor.
            undirected_graph(const undirected_graph &) noexcept;
            // Copy assignment operator.
            undirected_graph& operator=(const undirected_graph &) noexcept;
            
            // Move constructor.
            undirected_graph(undirected_graph &&) noexcept;
            // Move assignment operator.
            undirected_graph& operator=(undirected_graph &&) noexcept;

            // Overloaded equality operator.
            bool operator==(const undirected_graph &) const;
            // Overloaded inequality operator.
            bool operator!=(const undirected_graph &) const;


            /*
             *  NON-CONST MEMBER FUNCTIONS
             */
            // Swaps the internal data structures of the given graphs.
            void swap(undirected_graph &);
            // Clears the container.
            void clear();

            // Given an object, adds it to the graph, if it doesn't exist already.
            bool addVertex(T);
            // Given a list of objects, adds each of them to the graph, if it doesn't exist already.
            bool addVertices(const std::vector<T> &);
            // Given two objects, adds the edge between them to the graph, if it doesn't exist already.
            virtual bool addEdge(T, T, W weight = 1);
            // Given a list of pair of objects, adds each edge to the graph, if it doesn't exist already.
            virtual bool addEdges(const std::vector<std::pair<T, T>> &);
            // Given a list of tuple of objects along with weights, adds each edge to the graph, if it doesn't exist already.
            virtual bool addEdges(const std::vector<std::tuple<T, T, W>> &);
            
            // Given an object, removes it and its edges from the graph, if it exists.
            bool removeVertex(T);
            // Given a list of objects, removes each of them and its edges from the graph, if it exists.
            bool removeVertices(const std::vector<T> &);
            // Given two objects, removes all edges present between them from the graph, if any exists.
            virtual bool removeEdge(T, T);
            // Given a list of pair of objects, removes all edges between each them from the graph, if any exists.
            virtual bool removeEdges(const std::vector<std::pair<T, T>> &);
            // Given two objects and weight, removes the specified edge from the graph, if it exists.
            virtual bool removeEdge(T, T, W);
            // Given a list of tuple of vertices and weights, removes each specified edge from the graph, if it exists.
            virtual bool removeEdges(const std::vector<std::tuple<T, T, W>> &);


            /*
             *  CONST MEMBER FUNCTIONS
             */
            // Helper function to print DFS; takes starting vertex and set of visited vertices.
            void printDFS(unsigned int, std::unordered_set<unsigned int> &) const;
            // Function to print DFS; prints each connected component on different line.
            void printDFS() const;
            // Helper function to print BFS; takes starting vertex and set of visited vertices.
            void printBFS(unsigned int, std::unordered_set<unsigned int> &) const;
            // Function to print BFS; prints each connected component on different line.
            void printBFS() const;

            /*
             *  If the destination is not reachable, distance is inf.
             *  If the destination is a part of negative cycle, distance is -inf.
             *  If any of the vertex is invalid, distance is -1.
             *  If the destination is not reachable || If the destination is a part of negative cycle || If any of the vertex is invalid, path is EMPTY VECTOR.
             */
            // Given two vertices, returns the length of shortest path between them.
            double shortestDistance(T, T) const;
            // Given two vertices, returns the shortest path between them.
            std::vector<T> shortestPath(T, T) const;
            // Given a vertex, returns the length of shortest paths from it to all other vertices.
            std::unordered_map<T, double> singleSourceShortestDistances(unsigned int) const;
            // Given a vertex, returns the shortest path from it to all other vertices.
            std::unordered_map<T, std::vector<T>> singleSourceShortestPaths(unsigned int) const;
            // Returns the length of shortest paths for all pairs of vertices.
            std::unordered_map<T, std::unordered_map<T, double>> allPairsShortestDistances() const;
            // Returns the shortest path for all pairs of vertices.
            std::unordered_map<T, std::unordered_map<T, std::vector<T>>> allPairsShortestPaths() const;

            // Returns a vector of pairs containing cut edges.
            virtual std::vector<std::pair<T, T>> cutEdges() const;
            // Returns a vector containing cut vertices.
            virtual std::vector<T> cutVertices() const;
            // Returns a vector of vectors, where each vector contains vertices of a connected component.
            virtual std::vector<std::vector<T>> connectedComponents() const;
            // Returns a vector of edges which are a part of a minimum spanning tree. If MST doesn't exist, returns an empty vector.
            virtual std::vector<std::tuple<T, T, W>> minimumSpanningTree() const;

            // Returns 0 -> Not Eulerian, 1 -> Semi-Eulerian, 2 -> Eulerian.
            virtual int isEulerian() const;
            // Returns a vector containing the Eulerian path. If the graph is not Eulerian, returns an empty vector.
            virtual std::vector<T> eulerianPath() const;

            // Returns true of the graph contains a cycle.
            virtual bool isCyclic() const;

            // Prints the Adjacency list of the graph.
            void printGraph() const;
            // Prints the Adjacency list of the graph along with weights.
            void printWeightedGraph() const;
            // Returns the degree of a vertex, if it exists. If the vertex doesn't exist, returns -1.
            int degree(T) const;
            // Returns true if the graph is empty, else false. 
            bool empty() const;
            // Utility function to check the (id - node) mapping.
            void printMap() const;

            /*
             *  ITERATOR-RELATED FUNCTIONS
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

        private:
            void cutEdgesUtil(unsigned int, unsigned int, unsigned int &, std::vector<std::pair<T, T>> &, std::unordered_set<unsigned int> &, std::unordered_map<unsigned int, unsigned int> &, std::unordered_map<unsigned int, unsigned int> &) const;
            void cutVerticesUtil(unsigned int &, std::vector<T> &, std::unordered_set<unsigned int> &, std::unordered_map<unsigned int, unsigned int> &, std::unordered_map<unsigned int, unsigned int> &, unsigned int, unsigned int) const;
            virtual void eulerianPathUtil(unsigned int, std::unordered_map<unsigned int, std::vector<Node<W>>> &, std::unordered_map<unsigned int, unsigned int> &, std::vector<T> &) const;
            virtual void isEulerianUtil(unsigned int, std::unordered_set<unsigned int> &) const;
            bool isCyclicUtil(unsigned int, std::unordered_set<unsigned int> &, unsigned int) const;

            /*
             *  SHORTEST PATH RELATED FUNCTIONS
             *  If two valid vertices are given, returns (bestDistancesMap, bestPathsMap) tuple,
             *  except for bidirectionalSearch which returns (bestDistance, bestPath) tuple.
             *  Use Bellman-Ford for negative weighted graphs, Bidirectional Search/BFS for unweighted graphs, Dijkstra for others.
             *  BFS for SSSP, Bidirectional Search for when both source and destination are given.
             */
            // To disable early stopping(for SSSP problem), call this function without second parameter.
            std::tuple<std::unordered_map<unsigned int, double>, std::unordered_map<unsigned int, unsigned int>> Dijkstra(unsigned int, unsigned int = 0) const;
            std::tuple<std::unordered_map<unsigned int, double>, std::unordered_map<unsigned int, unsigned int>> bellmanFord(unsigned int) const;
            std::tuple<std::unordered_map<unsigned int, double>, std::unordered_map<unsigned int, unsigned int>> breadthFirstSearch(unsigned int) const;
            std::tuple<double, std::vector<T>> bidirectionalSearch(unsigned int, unsigned int) const;
            std::tuple<std::unordered_map<unsigned int, std::unordered_map<unsigned int, double>>, std::unordered_map<unsigned int, std::unordered_map<unsigned int, unsigned int>>> floydWarshall() const;
    };
}

#include "undirected_graph_defs.hpp"
#include "const_node_iterator.hpp"
#include "const_edge_iterator.hpp"
#include "node_iterator.hpp"
#include "edge_iterator.hpp"

#endif