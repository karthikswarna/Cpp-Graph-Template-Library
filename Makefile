all:
	g++ undirected_graph.hpp undirected_graph_defs.hpp directed_graph.hpp directed_graph_defs.hpp shortest_path.hpp undirected_eulerian.hpp directed_eulerian.hpp node_iterator.hpp const_node_iterator.hpp edge_iterator.hpp const_edge_iterator.hpp
test:
	g++ test.cpp
clean:
	rm -rf a.out undirected_graph.hpp.gch undirected_graph_defs.hpp.gch directed_graph.hpp.gch directed_graph_defs.hpp.gch shortest_path.hpp.gch undirected_eulerian.hpp.gch directed_eulerian.hpp.gch node_iterator.hpp.gch const_node_iterator.hpp.gch edge_iterator.hpp.gch const_edge_iterator.hpp.gch