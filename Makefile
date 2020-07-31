all:
	g++ graph.hpp
test:
	g++ test.cpp
clean:
	rm -rf a.out graph.hpp.gch