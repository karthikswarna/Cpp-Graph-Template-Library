all:
	g++ SimpleGraph.hpp SimpleGraphDefs.hpp DirectedGraph.hpp DirectedGraphDefs.hpp
test:
	g++ test.cpp
clean:
	rm -rf a.out SimpleGraph.hpp.gch SimpleGraphDefs.hpp.gch DirectedGraph.hpp.gch DirectedGraphDefs.hpp.gch