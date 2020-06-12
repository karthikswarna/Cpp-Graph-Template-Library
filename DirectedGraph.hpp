#ifndef DIRECTED_GRAPH_H
#define DIRECTED_GRAPH_H

#include <vector>
#include <unordered_map>
#include "SimpleGraph.hpp"

namespace Graph
{
    template<typename T>
    class DirectedGraph : public SimpleGraph<T>
    {
        public:
            DirectedGraph();
            ~DirectedGraph();

            // Given two objects, adds the edge between them to the graph, if it doesn't exist already.
            bool addEdge(T, T);
            // Given a list of pair of objects, adds each edge to the graph, if it doesn't exist already.
            bool addEdges(const std::vector<std::pair<T, T>> &);
            
            // Given two objects, removes the edge between them from the graph, if it exists.
            bool removeEdge(T, T);
            // Given a list of pair of objects, removes each edge from the graph, if it exists.
            bool removeEdges(const std::vector<std::pair<T, T>> &);

            // Returns the (in-degree, out-degree) of a vertex as std::pair<int, int>, if the vertex exists. 
            // If the vertex doesn't exist, returns -1.
            std::pair<int, int> getDegree(T) const;
    };
}

#include "DirectedGraphDefs.hpp"

#endif