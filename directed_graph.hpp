#ifndef DIRECTED_GRAPH_H
#define DIRECTED_GRAPH_H

#include "undirected_graph.hpp"

namespace graph
{
    template<typename T, typename W = int>
    class directed_graph : public undirected_graph<T, W>
    {
        public:
            /*
             * SPECIAL MEMBER FUNCTIONS
             */
            // Default constructor
            directed_graph() noexcept;
            // Destructor
            ~directed_graph() noexcept;
            
            //Copy Constructor
            directed_graph(const directed_graph &) noexcept;
            // Copy assignment operator
            directed_graph& operator=(const directed_graph &) noexcept;
            
            // Move constructor
            directed_graph(directed_graph &&) noexcept;
            // Move assignment operator
            directed_graph& operator=(directed_graph &&) noexcept;


            /*
             * NON-CONST MEMBER FUNCTIONS
             */
            // Given two objects, adds the edge between them to the graph, if it doesn't exist already.
            bool addEdge(T, T, W = 1);
            // Given a list of pair of objects, adds each edge to the graph, if it doesn't exist already.
            bool addEdges(const std::vector<std::pair<T, T>> &);
            // Given a list of pair of objects along with weights, adds each edge to the graph, if it doesn't exist already.
            bool addEdges(const std::vector<std::tuple<T, T, W>> &);

            // Given two objects, removes all edges present between them from the graph, if any exists.
            bool removeEdge(T, T);
            // Given a list of pair of objects, removes all edges between each them from the graph, if any exists.
            bool removeEdges(const std::vector<std::pair<T, T>> &);
            // Given two objects and weight, removes the specified edge from the graph, if it exists.
            bool removeEdge(T, T, W);
            // Given a list of tuple of vertices and weights, removes each specified edge from the graph, if it exists.
            bool removeEdges(const std::vector<std::tuple<T, T, W>> &);



            /*
             * CONST MEMBER FUNCTIONS
             */
            // Returns the topological srt of the directed graph.
            std::vector<T> topologicalSort() const;
            // Returns a vector of vectors, where each vector contains vertices of a strongly connected component.
            std::vector<std::vector<T>> stronglyConnectedComponents() const;

            // Returns 0 -> Not Eulerian, 1 -> Semi-Eulerian, 2 -> Eulerian.
            int isEulerian() const;
            // Returns a vector containing the Eulerian path. If the graph is not Eulerian, returns an empty vector.
            std::vector<T> eulerianPath() const;

            // Returns true if the graph is cyclic, else returns false.
            bool isCyclic() const;
            // Returns the (in-degree, out-degree) of a vertex as std::pair<int, int>, if the vertex exists. If the vertex doesn't exist, returns -1.
            std::pair<int, int> degree(T) const;
        
        private:
            using undirected_graph<T, W>::cutEdges;
            using undirected_graph<T, W>::cutVertices;
            using undirected_graph<T, W>::connectedComponents;
            using undirected_graph<T, W>::minimumSpanningTree;

            unsigned int topologicalSortUtil(unsigned int, unsigned int, std::unordered_set<unsigned int> &, std::vector<T> &) const;
            void stronglyConnectedComponentsUtil(unsigned int, unsigned int, std::stack<unsigned int> &, std::unordered_set<unsigned int> &, std::unordered_map<unsigned int, unsigned int> &, std::unordered_map<unsigned int, unsigned int> &, std::vector<std::vector<T>> &) const;
            void eulerianPathUtil(unsigned int, std::unordered_map<unsigned int, unsigned int> &, std::vector<T> &) const;
            bool isCyclicUtil(unsigned int, std::unordered_set<unsigned int> &, std::unordered_set<unsigned int> &, std::unordered_set<unsigned int> &) const;
    };
}

#include "directed_graph_defs.hpp"

#endif