# <div align="center">**C++ Graph Template Library**</div>

## **Introduction**
An STL-style C++ library for creating, manipulating, analysing graphs.
This is written using C++14 and is tested only on latest version of GNU C++.


## **Compilation**
To compile the project on a UNIX-based system use the command ```make```.


## **API**

* For dealing with undirected and directed graphs separately the library provides two different class templates namely
    * ```undirected_graph<T, W>```
    * ```directed_graph<T, W>```

* The template parameter ```T``` denotes the data type for *nodes/vertices* in the graph and the parameter ```W``` denotes the data type for *weights* of the edges. ```W``` parameter is optional (default value being ```int```). Note that ```W``` can only be a numeric type (i.e ```int```, ```float```, ```double``` etc.).

* It also provides 4 types of iterator sub-classes for each of the two graph class templates. They are  
    * ```node_iterator```
    * ```const_node_iterator```
    * ```edge_iterator```
    * ```const_edge_iterator```

* ```node_iterator``` can be used to change the value/name of a vertex. ```edge_iterator``` can be used only to change the weight of the edge but not the vertices that it connects. ```const_node_iterator``` and ```const_edge_iterator``` cannot modify the graph object that they iterate over.

### **Methods common to both undirected_graph<T, W> and directed_graph<T ,W>**
#### A) Methods which modify the graph
Method prototype                                            | Arguments | Return value
----------------------------------------------------------- | --------- | ------------
bool addVertex(T);                                          | A vertex to be added to the graph. | Returns true if the vertex is added successfully, else false.
bool addVertices(const std::vector<T> &);                   | A vector of vertices to be added to the graph. | Returns true if the vertices are added successfully, else false.
bool addEdge(T, T, W weight = 1);                           | Two vertices between which the edge is to be added. Weight is optional(1 by default). | Returns true if the edge is added successfully, else false.
bool addEdges(const std::vector<std::pair<T, T>> &);        | A vector of std::pair<T, T>'s (each pair being an edge) and weight is 1 by default. | Returns true if the edges are added successfully, else false.
bool addEdges(const std::vector<std::tuple<T, T, W>> &);    | A vector of std::tuple<T, T, W>'s (each tuple being a weighted edge). | Returns true if the edges are added successfully, else false.
bool removeVertex(T);                                       | A vertex to be removed from the graph. | Returns true if the vertex is removed successfully, else false.
bool removeVertices(const std::vector<T> &);                | A vector of vertices to be removed from the graph. | Returns true if the vertices are removed successfully, else false.
bool removeEdge(T, T);                                      | Two vertices between which the edge is to be removed. The edge is removed regardless of what the weight is. | Returns true if the edge is removed successfully, else false.
bool removeEdges(const std::vector<std::pair<T, T>> &);     | A vector of edges which are to be removed from the graph. An edge is removed regardless of what the weight is. | Returns true if the edges are removed successfully, else false.
bool removeEdge(T, T, W);                                   | Two vertices between which the edge is to be removed. The edge is removed only if the weight is matched. | Returns true if the edge is removed successfully, else false.
bool removeEdges(const std::vector<std::tuple<T, T, W>> &); | A vector of weighted edges which are to be removed from the graph. The edge is removed only if the weight is matched. | Returns true if the edges are removed successfully, else false.
void swap(undirected_graph &);                              | An undirected_graph<T, W> which is to be swapped with the current graph. | -
void clear();                                               | - | -

#### B) Methods which analyse the structure of the graph
Method prototype                                                                            | Arguments | Return value
------------------------------------------------------------------------------------------- | --------- | ------------
void printGraph() const;                                                                    | - | -
void printWeightedGraph() const;                                                            | - | -
bool empty() const;                                                                         | - | Returns true if the graph is empty, else false.
void printDFS() const;                                                                      | - | -
void printBFS() const;                                                                      | - | -
bool isCyclic() const;                                                                      | - | Returns true if the graph is cyclic, else false.
int isEulerian() const;                                                                     | - | Returns 0 -> if the graph is not Eulerian, 1 -> if the graph is Semi-Eulerian, 2 -> if the graph is Eulerian.
std::vector<T> eulerianPath() const;                                                        | - |Returns a vector of vertices which forms the eulerian path if the graph is Eulerian/Semi-Eulerian, else returns an empty vector.
double shortestDistance(T, T) const;                                                        | Two vertices for which shortest distance is to be found. | Returns the shortest distance if the two vertices are reachable. 
std::vector<T> shortestPath(T, T) const;                                                    | Two vertices for which shortest path is to be found. | Returns a vector containg the shortest path if the two vertices are reachable.
std::unordered_map<T, double> singleSourceShortestDistances(unsigned int) const;            | A vertex from which single source shortest distances to be found. | Returns an associative array that maps (destination_vertex => shortest_distance_from_source) for all the vertices.
std::unordered_map<T, std::vector<T>> singleSourceShortestPaths(unsigned int) const;        | A vertex from which single source shortest distances to be found. | Returns an associative array that maps (destination_vertex => shortest_path_from_source) for all the vertices.
std::unordered_map<T, std::unordered_map<T, double>> allPairsShortestDistances() const;     | - | Returns a 2D associative array that maps ((source_vertex, destination_vertex) => shortest_distance) for all pairs of vertices in the graph.
std::unordered_map<T, std::unordered_map<T, std::vector<T>>> allPairsShortestPaths() const; | - | Returns a 2D associative array that maps ((source_vertex, destination_vertex) => path) for all pairs of vertices in the graph. Here, the path is returned as a vector of vertices.


##### NOTE:
1. In all the shortest path, shortest distance related functions the following conventions are followed: 
    * If the destination is not reachable, distance is ```inf```. If the destination is a part of negative cycle, distance is ```-inf```. If any of the vertex is invalid, distance is ```-1```.
    * If the destination is not reachable OR If the destination is a part of negative cycle OR If any of the vertex is invalid, returns an EMPTY VECTOR.
2. The unordered_map in C++ can be used as an associative array.
   Ex:
   ```cpp
        // 1D Associative array.
        std::unordered_map<string, int> M = {{"node1", 10}, {"node2", 20}, {"node3", 30}};
        int d1 = M["node1"];
        int d2 = M["node2"];

        // 2D Associative array.
        std::unordered_map<string, std::unordered_map<string, int>> M = { { "node1", {{"node2", 30}, {"node3", 40}} }, 
                                                                          { "node2", {{"node1", 30}, {"node3", 50}} }, 
                                                                          { "node3", {{"node1", 40}, {"node2", 50}} } };
        int d3 = M["node1"]["node2"];
        int d4 = M["node2"]["node3"];
        int d5 = M["node3"]["node1"];
   ```


### **Methods specific to undirected_graph<T, W>**
Method prototype                                                 |                 Arguments                 |         Return value
---------------------------------------------------------------- | ----------------------------------------- | ---------------------------------
std::vector<std::pair<T, T>> cutEdges() const;                   |                    -                      | Returns a vector of pairs (each pair being a cut edge).
std::vector<T> cutVertices() const;                              |                    -                      | Returns a vector of cut vertices.
std::vector<std::vector<T>> connectedComponents() const;         |                    -                      | Returns a vector of connected components. Each component is returned as a vector of vertices.
std::vector<std::tuple<T, T, W>> minimumSpanningTree() const;    |                    -                      | Returns a vector of weighted edges where each edge is a part of the minimum spanning tree, if it exists. Returns an empty vector if it doesn't exist.
int degree(T) const;                                             | A vertex for which degree is to be found. | Returns the degree of the vertex.


### **Methods specific to directed_graph<T, W>**
Method prototype                                                 |                 Arguments                 |         Return value
---------------------------------------------------------------- | ----------------------------------------- | ---------------------------------
std::vector<T> topologicalSort() const;                          |                     -                     | Returns a vector of vertices which forms the topological sort of the graph if it exist. If the topological sort cannot be formed, returns an empty vector.
std::vector<std::vector<T>> stronglyConnectedComponents() const; |                     -                     | Returns a vector of strongly connected components. Each component is returned as a vector of vertices.
std::pair<int, int> degree(T) const;                             | A vertex for which degree is to be found. | Returns the (indegree-outdegree) pair for the given vertex. If the vertex doesn't exist, returns (-1, -1).

### **Methods specific to node_iterator**
Method prototype                                                 |                 Arguments                 |         Return value
---------------------------------------------------------------- | ----------------------------------------- | ---------------------------------
void setNode(T);                                                 | A new value for the vertex which is being pointed by the iterator object. | -

### **Methods specific to edge_iterator**
Method prototype                                                 |                 Arguments                 |         Return value
---------------------------------------------------------------- | ----------------------------------------- | ---------------------------------
void setWeight(W);                                               | A new value for the weight of the edge pointed by the iterator object. | -
W getWeight() const;                                             |                     -   | Returns the weight of the edge pointed by the iterator.

## **Examples**

### Undirected graph
```cpp
    #include "graph.hpp"
    using namespace std;

    graph::undirected_graph<int, float> G;
    G.addVertex(1);
    G.addVertices(vector<int>{5, 7});
    G.addEdge(5, 2, 6.78);
    G.addEdges(vector<pair<int, int>>{pair<int, int>(1, 3), pair<int, int>(1, 4), pair<int, int>(6, 1)});
    G.addEdges(vector<tuple<int, int, float>>{tuple<int, int, float>(4, 6, 1.0009), tuple<int, int, float>(5, 3, 3)});

    cout << G.degree(1) << endl;
    cout << G.degree(4) << endl;
    cout << G.degree(7) << endl;
 
    G.printDFS();
    G.printBFS();
    G.printGraph();
    G.printWeightedGraph();

    // node_iterator
    graph::undirected_graph<int, float>::node_iterator it = G.begin();
    for(; it != G.end(); it++)
        cout << *it << " ";

    // const_node_iterator with cbegin, cend
    graph::undirected_graph<int, float>::const_node_iterator it3 = G.cbegin();
    for(; it3 != G.end(); it3++)
        cout << *it3 << " ";

    // edge_iterator
    graph::undirected_graph<int, float>::edge_iterator eit = G.begin(0);
    for(; eit != G.end(0); eit++)
        cout << (*eit).first << ' ' << (*eit).second << endl;

    // const_edge_iterator with cbegin, cend
    graph::undirected_graph<int, float>::const_edge_iterator eit3 = G.cbegin(0);
    for(; eit3 != G.end(0); eit3++)
        cout << (*eit3).first << ' ' << (*eit3).second << endl;


    // Distance between two vertices.
    cout << G.shortestDistance(1, 6) << endl;
    V = G.shortestPath(1, 6);
    for(auto i : V)
        cout << i << ' ';
    cout << endl << endl;

    // Single source shortest paths.
    cout << "SSS Distances:\n";
    unordered_map<int, double> D = G.singleSourceShortestDistances(1);
    for(auto i : D)
        cout << i.first << " " << i.second << endl;
    cout << endl;

    cout << "SSS Paths:\n";
    unordered_map<int, vector<int>> P = G.singleSourceShortestPaths(1);
    for(auto i : P)
    {
        cout << i.first << ": ";
        for(auto e : i.second)
            cout << e << " -> ";
        cout << endl;
    }
    cout << endl;

    // All Pairs shortest paths.
    unordered_map<int, unordered_map<int, double>> D1;
    unordered_map<int, unordered_map<int, vector<int>>> P1;
    D1 = G.allPairsShortestDistances();
    P1 = G.allPairsShortestPaths();
    
    cout << "APSP Distances:\n";
    for(auto i : D1)
        for(auto j : i.second)
            cout << i.first << ' ' << j.first << ' ' << j.second << endl;
    cout << endl << endl;

    cout << "APSP Paths:\n";
    for(auto i : P1)
        for(auto j : i.second)
        {
            cout << i.first << ' ' << j.first << ":  ";
            for(auto k : j.second)
                cout << k << " -> ";
            cout << endl;
        }
    cout << endl << endl;

    // Cut bridges, vertices, connected components
    vector<pair<int, int>> CE = G.cutEdges();
    vector<int> CV = G.cutVertices();

    cout << "Cut Edges: \n";
    for(auto i : CE)
        cout << i.first << ' ' << i.second << endl;
    cout << endl;

    cout << "Cut Vertices: \n";
    for(auto i : CV)
        cout << i << ' ';
    cout << endl;

    cout << "Connected Components: \n";
    vector<vector<int>> CC = G.connectedComponents();
    for(auto i : CC)
    {
        for(auto j : i)
            cout << j << ' ';
        cout << endl;
    }
    cout << endl;

    // Minimum spanning tree.
    cout << "Minimum Spanning Tree: \n";
    vector<tuple<int, int, float>> MST = G.minimumSpanningTree();
    for(auto i : MST)
        cout << get<0>(i) << ' ' << get<1>(i) << ' ' << get<2>(i) << endl;
    cout << endl;

    // Eulerian graphs.
    cout << "Eulerian: " << G.isEulerian() << endl << "Path: ";
    std::vector<int> EP = G.eulerianPath();
    for(auto i : EP)
        cout << i << ' ';
    cout << endl;

    G.removeVertex(5);
    G.removeVertex(4);
    G.removeVertices(vector<int>{4, 5});
    G.removeEdge(7, 8);
    G.removeEdges(vector<pair<int, int>>{pair<int, int>(2, 6)});
```

### Directed graph
```cpp
    graph::directed_graph<int, float> G2;
    G2.addVertex(1);
    G2.addVertices(vector<int>{5, 7});
    G2.addEdge(5, 2, 6.78);
    G2.addEdges(vector<pair<int, int>>{pair<int, int>(1, 3), pair<int, int>(1, 4), pair<int, int>(6, 1)});
    G2.addEdges(vector<tuple<int, int, float>>{tuple<int, int, float>(4, 6, 1.0009), tuple<int, int, float>(5, 3, 3)});

    cout << "In-degree: " << G2.degree(1).first << ", " << "Out-degree:" << G2.degree(1).second << endl;
    cout << "In-degree: " << G2.degree(4).first << ", " << "Out-degree:" << G2.degree(4).second << endl;
    cout << "In-degree: " << G2.degree(7).first << ", " << "Out-degree:" << G2.degree(7).second << endl;

    // Topological sort.
    cout << "TOPOLOGICAL SORT:" << endl;
    vector<int> V = G2.TopologicalSort();
    for(int x: V)
        cout << x << ' ';
    cout << endl;

    // Strongly connected components.
    cout << "Connected Components: \n";
    vector<vector<int>> CC = G2.stronglyConnectedComponents();
    for(auto i : CC)
    {
        for(auto j : i)
            cout << j << ' ';
        cout << endl;
    }
    cout << endl;
```

### Two graphs can also be compared
```cpp
    graph::undirected_graph<int> G3;
    G3.addVertices(vector<int>{1,2,3});
    G3.addEdges(vector<pair<int, int>>{pair<int, int>(1,2), pair<int, int>(2, 3), pair<int, int>(3, 1)});

    G1.printGraph();
    G3.printGraph();
       
    G3.swap(G1);

    G1.printGraph();
    G3.printGraph();
    
    cout << boolalpha << (G1 == G3) << endl << (G1 != G3) << endl << G1.empty() << endl << G3.empty() << endl;
```