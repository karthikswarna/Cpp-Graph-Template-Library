#ifndef DIRECTED_GRAPH_H
#define DIRECTED_GRAPH_H

#include "UndirectedGraph.hpp"

namespace Graph
{
    template<typename T>
    class DirectedGraph : public UndirectedGraph<T>
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
            bool addEdge(T, T);
            // Given a list of pair of objects, adds each edge to the graph, if it doesn't exist already.
            bool addEdges(const std::vector<std::pair<T, T>> &);

            // Given two objects, removes the edge between them from the graph, if it exists.
            bool removeEdge(T, T);
            // Given a list of pair of objects, removes each edge from the graph, if it exists.
            bool removeEdges(const std::vector<std::pair<T, T>> &);


            /*
             * CONST MEMBER FUNCTIONS
             */
            // Returns true if the graph is cyclic, else returns false.
            bool isCyclic() const;
            // Returns the topological srt of the directed graph.
            std::vector<T> TopologicalSort() const;
            // Returns the (in-degree, out-degree) of a vertex as std::pair<int, int>, if the vertex exists. 
            // If the vertex doesn't exist, returns -1.
            std::pair<int, int> getDegree(T) const;
        
        private:
            // Utility Function used for topoligical sort.
            unsigned int DFSUtil(unsigned int, unsigned int, std::unordered_set<unsigned int> &, std::vector<T> &) const;
            // Utility function for finding cycles in directed graph.
            bool isCyclic(unsigned int, std::unordered_set<unsigned int> &, std::unordered_set<unsigned int> &, std::unordered_set<unsigned int> &) const;
            
    };
}

#include "DirectedGraphDefs.hpp"

#endif