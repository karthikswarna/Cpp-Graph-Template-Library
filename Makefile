all:
	g++ UndirectedGraph.hpp UndirectedGraphDefs.hpp DirectedGraph.hpp DirectedGraphDefs.hpp node_iterator.hpp const_node_iterator.hpp edge_iterator.hpp const_edge_iterator.hpp
test:
	g++ test.cpp
clean:
	rm -rf a.out UndirectedGraph.hpp.gch UndirectedGraphDefs.hpp.gch DirectedGraph.hpp.gch DirectedGraphDefs.hpp.gch node_iterator.hpp.gch const_node_iterator.hpp.gch edge_iterator.hpp.gch const_edge_iterator.hpp.gch