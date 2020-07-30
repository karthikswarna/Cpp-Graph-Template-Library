#ifndef DIRECTED_GRAPH_H
#define DIRECTED_GRAPH_H

#include "UndirectedGraph.hpp"

namespace Graph
{
    template<typename T, typename W = int>
    class DirectedGraph : public UndirectedGraph<T, W>
    {
        public:
            /*
             * SPECIAL MEMBER FUNCTIONS
             */
            // Default constructor
            DirectedGraph() noexcept;
            // Destructor
            ~DirectedGraph() noexcept;
            
            //Copy Constructor
            DirectedGraph(const DirectedGraph &) noexcept;
            // Copy assignment operator
            DirectedGraph& operator=(const DirectedGraph &) noexcept;
            
            // Move constructor
            DirectedGraph(DirectedGraph &&) noexcept;
            // Move assignment operator
            DirectedGraph& operator=(DirectedGraph &&) noexcept;


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
            std::vector<T> getTopologicalSort() const;
            // Returns a vector of vectors, where each vector contains vertices of a strongly connected component.
            std::vector<std::vector<T>> getStronglyConnectedComponents() const;

            // Returns 0 -> Not Eulerian, 1 -> Semi-Eulerian, 2 -> Eulerian.
            int isEulerian() const;
            // Returns a vector containing the Eulerian path. If the graph is not Eulerian, returns an empty vector.
            std::vector<T> getEulerianPath() const;

            // Returns true if the graph is cyclic, else returns false.
            bool isCyclic() const;
            // Returns the (in-degree, out-degree) of a vertex as std::pair<int, int>, if the vertex exists. If the vertex doesn't exist, returns -1.
            std::pair<int, int> getDegree(T) const;
        
        private:
            using UndirectedGraph<T, W>::getCutEdges;
            using UndirectedGraph<T, W>::getCutVertices;
            using UndirectedGraph<T, W>::getConnectedComponents;
            using UndirectedGraph<T, W>::getMinimumSpanningTree;

            unsigned int getTopologicalSortUtil(unsigned int, unsigned int, std::unordered_set<unsigned int> &, std::vector<T> &) const;
            void getSCCUtil(unsigned int, unsigned int, std::stack<unsigned int> &, std::unordered_set<unsigned int> &, std::unordered_map<unsigned int, unsigned int> &, std::unordered_map<unsigned int, unsigned int> &, std::vector<std::vector<T>> &) const;
            void getEulerianPathUtil(unsigned int, std::unordered_map<unsigned int, unsigned int> &, std::vector<T> &) const;
            bool isCyclicUtil(unsigned int, std::unordered_set<unsigned int> &, std::unordered_set<unsigned int> &, std::unordered_set<unsigned int> &) const;
    };
}

#include "DirectedGraphDefs.hpp"

#endif