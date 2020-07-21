#ifndef DIRECTED_GRAPH_DEFINITIONS_H
#define DIRECTED_GRAPH_DEFINITIONS_H

#include "DirectedGraph.hpp"

namespace Graph
{
    template<typename T, typename W>
    DirectedGraph<T, W>::DirectedGraph() noexcept
    {
    }

    template<typename T, typename W>
    DirectedGraph<T, W>::~DirectedGraph() noexcept 
    { 
        this->_ADJACENCY_LIST_.clear();
        this->_id_to_node_.clear();
        this->_node_to_id_.clear(); 
    }

    template<typename T, typename W>
    DirectedGraph<T, W>::DirectedGraph(const DirectedGraph &rhs) noexcept
        : Graph::UndirectedGraph<T>(rhs)
    {
    }

    template<typename T, typename W>
    DirectedGraph<T, W>& DirectedGraph<T, W>::operator=(const DirectedGraph &rhs) noexcept
    {
        this->_ADJACENCY_LIST_ = rhs._ADJACENCY_LIST_;
        this->_id_to_node_ = rhs._id_to_node_;
        this->_node_to_id_ = rhs._node_to_id_;
        this->isNegWeighted = rhs.isNegWeighted;
        this->isWeighted = rhs.isWeighted;
        this->_id_ = rhs._id_;
        return *this;
    }
    
    template<typename T, typename W>
    DirectedGraph<T, W>::DirectedGraph(DirectedGraph &&rhs) noexcept
        : Graph::UndirectedGraph<T>(rhs)
    {
    }

    template<typename T, typename W>
    DirectedGraph<T, W>& DirectedGraph<T, W>::operator=(DirectedGraph &&rhs) noexcept
    {
        this->_ADJACENCY_LIST_ = std::move(rhs._ADJACENCY_LIST_);
        this->_id_to_node_ = std::move(rhs._id_to_node_);
        this->_node_to_id_ = std::move(rhs._node_to_id_);
        this->isNegWeighted = std::move(rhs.isNegWeighted);
        this->isWeighted = std::move(rhs.isWeighted);
        this->_id_ = std::move(rhs._id_);
        return *this;
    }

    template<typename T, typename W>
    bool DirectedGraph<T, W>::addEdge(T vertex1, T vertex2, W weight)
    {
        try
        {
            // If vertex1 is not previously there, add it to the list of nodes.
            if(this->_node_to_id_.find(vertex1) == this->_node_to_id_.end())
            {
                this->_id_to_node_.insert(std::make_pair(this->_id_, vertex1));
                this->_node_to_id_.insert(std::make_pair(vertex1, this->_id_));
                this->_ADJACENCY_LIST_.insert(std::make_pair(this->_id_, std::vector<Node<W>>{}));
                (this->_id_)++;
            }

            // If vertex2 is not previously there, add it to the list of nodes.
            if(this->_node_to_id_.find(vertex2) == this->_node_to_id_.end())
            {
                this->_id_to_node_.insert(std::make_pair(this->_id_, vertex2));
                this->_node_to_id_.insert(std::make_pair(vertex2, this->_id_));
                this->_ADJACENCY_LIST_.insert(std::make_pair(this->_id_, std::vector<Node<W>>{}));
                (this->_id_)++;
            }

            unsigned int id1 = this->_node_to_id_.at(vertex1);
            unsigned int id2 = this->_node_to_id_.at(vertex2);

            if(weight < 0)
                this->isNegWeighted = true;
            if(weight > 1)
                this->isWeighted = true;

            std::vector<Node<W>> edge_list = this->_ADJACENCY_LIST_.at(id1);
            if(std::find(edge_list.begin(), edge_list.end(), Node<W>{id2, weight}) == edge_list.end())
                this->_ADJACENCY_LIST_.at(id1).push_back(Node<W>{id2, weight});

            return true;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            return false;
        }
    }

    template<typename T, typename W>
    bool DirectedGraph<T, W>::addEdges(const std::vector<std::pair<T, T>> &edges)
    {
        try
        {
            for(const std::pair<T, T> &e : edges)
            {
                T vertex1 = e.first;
                T vertex2 = e.second;
                
                // If vertex1 is not previously there, add it to the list of nodes.
                if(this->_node_to_id_.find(vertex1) == this->_node_to_id_.end())
                {
                    this->_id_to_node_.insert(std::make_pair(this->_id_, vertex1));
                    this->_node_to_id_.insert(std::make_pair(vertex1, this->_id_));
                    this->_ADJACENCY_LIST_.insert(std::make_pair(this->_id_, std::vector<Node<W>>{}));
                    (this->_id_)++;
                }

                // If vertex2 is not previously there, add it to the list of nodes.
                if(this->_node_to_id_.find(vertex2) == this->_node_to_id_.end())
                {
                    this->_id_to_node_.insert(std::make_pair(this->_id_, vertex2));
                    this->_node_to_id_.insert(std::make_pair(vertex2, this->_id_));
                    this->_ADJACENCY_LIST_.insert(std::make_pair(this->_id_, std::vector<Node<W>>{}));
                    (this->_id_)++;
                }

                unsigned int id1 = this->_node_to_id_.at(vertex1);
                unsigned int id2 = this->_node_to_id_.at(vertex2);

                std::vector<Node<W>> edge_list = this->_ADJACENCY_LIST_.at(id1);
                if(std::find(edge_list.begin(), edge_list.end(), id2) == edge_list.end())
                    this->_ADJACENCY_LIST_.at(id1).push_back(Node<W>{id2});
            }

            return true;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            return false;
        }    
    }

    template<typename T, typename W>
    bool DirectedGraph<T, W>::addEdges(const std::vector<std::tuple<T, T, W>> &edges)
    {
        try
        {
            for(const std::tuple<T, T, W> &e : edges)
            {
                T vertex1 = std::get<0>(e);
                T vertex2 = std::get<1>(e);
                W weight = std::get<2>(e);

                // If vertex1 is not previously there, add it to the list of nodes.
                if(this->_node_to_id_.find(vertex1) == this->_node_to_id_.end())
                {
                    this->_id_to_node_.insert(std::make_pair(this->_id_, vertex1));
                    this->_node_to_id_.insert(std::make_pair(vertex1, this->_id_));
                    this->_ADJACENCY_LIST_.insert(std::make_pair(this->_id_, std::vector<Node<W>>{}));
                    (this->_id_)++;
                }

                // If vertex2 is not previously there, add it to the list of nodes.
                if(this->_node_to_id_.find(vertex2) == this->_node_to_id_.end())
                {
                    this->_id_to_node_.insert(std::make_pair(this->_id_, vertex2));
                    this->_node_to_id_.insert(std::make_pair(vertex2, this->_id_));
                    this->_ADJACENCY_LIST_.insert(std::make_pair(this->_id_, std::vector<Node<W>>{}));
                    (this->_id_)++;
                }

                unsigned int id1 = this->_node_to_id_.at(vertex1);
                unsigned int id2 = this->_node_to_id_.at(vertex2);

                if(weight < 0)
                    this->isNegWeighted = true;
                if(weight > 1)
                    this->isWeighted = true;

                std::vector<Node<W>> edge_list = this->_ADJACENCY_LIST_.at(id1);
                if(std::find(edge_list.begin(), edge_list.end(), Node<W>{id2, weight}) == edge_list.end())
                    this->_ADJACENCY_LIST_.at(id1).push_back(Node<W>{id2, weight});
            }

            return true;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            return false;
        }    
    }

    template<typename T, typename W>
    bool DirectedGraph<T, W>::removeEdge(T vertex1, T vertex2)
    {
        try
        {
            if(this->_node_to_id_.find(vertex1) != this->_node_to_id_.end() && this->_node_to_id_.find(vertex2) != this->_node_to_id_.end())
            {
                std::vector<Node<W>> &edge_list1 = this->_ADJACENCY_LIST_.at(this->_node_to_id_.at(vertex1));
                if(std::find(edge_list1.begin(), edge_list1.end(), this->_node_to_id_.at(vertex2)) != edge_list1.end())
                {
                    edge_list1.erase(std::remove(edge_list1.begin(), edge_list1.end(), this->_node_to_id_.at(vertex2)), edge_list1.end());
                }
            }

            return true;
        }
        catch(const std::exception& e)
        {
            std::cout << e.what() << '\n';
            return false;
        }
    }

    template<typename T, typename W>
    bool DirectedGraph<T, W>::removeEdges(const std::vector<std::pair<T, T>> &edges)
    {
        try
        {
            for(const std::pair<T, T> &e : edges)
            {
                T vertex1 = e.first;
                T vertex2 = e.second;
    
                if(this->_node_to_id_.find(vertex1) != this->_node_to_id_.end() && this->_node_to_id_.find(vertex2) != this->_node_to_id_.end())
                {
                    std::vector<Node<W>> &edge_list1 = this->_ADJACENCY_LIST_.at(this->_node_to_id_.at(vertex1));
                    if(std::find(edge_list1.begin(), edge_list1.end(), this->_node_to_id_.at(vertex2)) != edge_list1.end())
                    {
                        edge_list1.erase(std::remove(edge_list1.begin(), edge_list1.end(), this->_node_to_id_.at(vertex2)), edge_list1.end());
                    }
                }
            }

            return true;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            return false;
        }
    }

    template<typename T, typename W>
    bool DirectedGraph<T, W>::removeEdge(T vertex1, T vertex2, W weight)
    {
        try
        {
            if(this->_node_to_id_.find(vertex1) != this->_node_to_id_.end() && this->_node_to_id_.find(vertex2) != this->_node_to_id_.end())
            {
                std::vector<Node<W>> &edge_list1 = this->_ADJACENCY_LIST_.at(this->_node_to_id_.at(vertex1));
                if(std::find(edge_list1.begin(), edge_list1.end(), Node<W>{this->_node_to_id_.at(vertex2), weight}) != edge_list1.end())
                {
                    edge_list1.erase(std::remove(edge_list1.begin(), edge_list1.end(), Node<W>{this->_node_to_id_.at(vertex2), weight}), edge_list1.end());
                }
            }

            return true;
        }
        catch(const std::exception& e)
        {
            std::cout << e.what() << '\n';
            return false;
        }
    }

    template<typename T, typename W>
    bool DirectedGraph<T, W>::removeEdges(const std::vector<std::tuple<T, T, W>> &edges)
    {
        try
        {
            for(const std::tuple<T, T, W> &e : edges)
            {
                T vertex1 = std::get<0>(e);
                T vertex2 = std::get<1>(e);
                W weight = std::get<2>(e);

                if(this->_node_to_id_.find(vertex1) != this->_node_to_id_.end() && this->_node_to_id_.find(vertex2) != this->_node_to_id_.end())
                {
                    std::vector<Node<W>> &edge_list1 = this->_ADJACENCY_LIST_.at(this->_node_to_id_.at(vertex1));
                    if(std::find(edge_list1.begin(), edge_list1.end(), Node<W>{this->_node_to_id_.at(vertex2), weight}) != edge_list1.end())
                    {
                        edge_list1.erase(std::remove(edge_list1.begin(), edge_list1.end(), Node<W>{this->_node_to_id_.at(vertex2), weight}), edge_list1.end());
                    }
                }
            }

            return true;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            return false;
        }
    }

    template<typename T, typename W>
    std::vector<std::vector<T>> DirectedGraph<T, W>::getStronglyConnectedComponents() const
    {
        unsigned int id = 0;
        std::stack<unsigned int> S;
        std::vector<std::vector<T>> SCC;
        std::unordered_set<unsigned int> onStack;
        std::unordered_map<unsigned int, unsigned int> Ids; // This also acts as 'Visited' array.
        std::unordered_map<unsigned int, unsigned int> Low;

        // A SCC is a subtree in a DFS tree. So, start DFS for every tree in DFS forest to find all SCC's.
        for(const std::pair<unsigned int, T> &vertex : this->_id_to_node_)
            if(Ids.find(vertex.first) == Ids.end())
                getSCCUtil(vertex.first, id, S, onStack, Ids, Low, SCC);
            
        return SCC;
    }

    template<typename T, typename W>
    void DirectedGraph<T, W>::getSCCUtil(unsigned int current, unsigned int id, std::stack<unsigned int> &S, std::unordered_set<unsigned int> &onStack, std::unordered_map<unsigned int, unsigned int> &Ids, std::unordered_map<unsigned int, unsigned int> &Low, std::vector<std::vector<T>> &SCC) const
    {
        // As soon as a node is visited, push it onto the stack and assign it an id and a low-link value.
        S.push(current);
        onStack.insert(current);
        Ids[current] = Low[current] = id++;

        // Loop through all the neighbours of the current node.
        for(const Node<W> &next : this->_ADJACENCY_LIST_.at(current))
        {
            // Do DFS for unvisited nodes.
            if(Ids.find(next.vertex) == Ids.end())
                getSCCUtil(next.vertex, id, S, onStack, Ids, Low, SCC);
            
            // If the 'next' is on the stack, it means that there is a path from 'next' to 'current' which we used to visit 'current'. But now there is also a path from 'current' to 'next'.
            // So, 'current', 'next' belong to same SCC. This step allows low-link values to propagate throughout cycles.
            if(onStack.find(next.vertex) != onStack.end())
                Low[current] = std::min(Low[current], Low[next.vertex]);
        }

        // If the low-link value is equal to the id for a node, it is the start of a SCC.
        if(Ids[current] == Low[current])
        {
            // Finding the component by popping off the stack until the start node(current).
            std::vector<T> Component;
            while(true)
            {
                unsigned int top = S.top();
                S.pop();

                Component.push_back(this->_id_to_node_.at(top));
                onStack.erase(top);
                Low[top] = Ids[current];
                if(top == current) 
                {
                    SCC.push_back(Component);
                    break;
                }
            }
        }
    }

    // template<typename T, typename W>
    // bool UndirectedGraph<T, W>::isCyclic() const
    // {
    //     std::unordered_set<unsigned int> Visited;
    //     std::unordered_set<unsigned int> recStack;

    //     for(const std::pair<unsigned int, std::vector<Node<W>>> &edges : this->_ADJACENCY_LIST_)
    //         if(isCyclicUtil(edges.first, Visited, recStack))
    //             return true;

    //     return false;
    // }

    // template<typename T, typename W>
    // bool UndirectedGraph<T, W>::isCyclicUtil(unsigned int start, std::unordered_set<unsigned int> &Visited, std::unordered_set<unsigned int> &recStack) const
    // {
    //     if(Visited.find(start) == Visited.end())
    //     {
    //         Visited.insert(start);
    //         recStack.insert(start);

    //         for(const Node<W> &node : this->_ADJACENCY_LIST_.at(start))
    //         {
    //             if(Visited.find(node.vertex) == Visited.end() && isCyclicUtil(node.vertex, Visited, recStack))
    //                 return true;
    //             else if(recStack.find(node.vertex) != recStack.end())
    //                 return true;
    //         }
    //     }

    //     recStack.erase(start);
    //     return false;
    // }

    template<typename T, typename W>
    bool DirectedGraph<T, W>::isCyclic() const
    {
        std::unordered_set<unsigned int> whiteSet;      // Unvisited
        std::unordered_set<unsigned int> greySet;       // Visited, but not completely processed.
        std::unordered_set<unsigned int> blackSet;      // Visited completely.

        for(const std::pair<unsigned int, std::vector<Node<W>>> &i : this->_ADJACENCY_LIST_)
            whiteSet.insert(i.first);
        
        while(whiteSet.size() > 0)
        {
            if(isCyclicUtil(*whiteSet.begin(), whiteSet, greySet, blackSet))
                return true;
        }
        
        return false;
    }

    template<typename T, typename W>
    bool DirectedGraph<T, W>::isCyclicUtil(unsigned int start, std::unordered_set<unsigned int> &whiteSet, std::unordered_set<unsigned int> &greySet, std::unordered_set<unsigned int> &blackSet) const
    {
        greySet.insert(start);
        whiteSet.erase(start);

        for(Node<W> dest : this->_ADJACENCY_LIST_.at(start))
        {
            if(blackSet.find(dest.vertex) != blackSet.end())
                continue;
            if(greySet.find(dest.vertex) != greySet.end())
                return true;
            if(whiteSet.find(dest.vertex) != whiteSet.end() && isCyclicUtil(dest.vertex, whiteSet, greySet, blackSet))
                return true;
        }

        greySet.erase(start);
        blackSet.insert(start);
        return false;
    }

    template<typename T, typename W>
    std::vector<T> DirectedGraph<T, W>::TopologicalSort() const
    {
        if(isCyclic())
            return std::vector<T>{};

        std::unordered_set<unsigned int> Visited;
        unsigned int index = this->_ADJACENCY_LIST_.size() - 1;
        std::vector<T> TopSort(index + 1);

        for(const std::pair<unsigned int, std::vector<Node<W>>> &edges : this->_ADJACENCY_LIST_)
            if(Visited.find(edges.first) == Visited.end())
                index = DFSUtil(index, edges.first, Visited, TopSort);

        return TopSort;
    }

    template<typename T, typename W>
    unsigned int DirectedGraph<T, W>::DFSUtil(unsigned int index, unsigned int start, std::unordered_set<unsigned int> &Visited, std::vector<T> &TopSort) const
    {
        Visited.insert(start);

        for(Node<W> dest : this->_ADJACENCY_LIST_.at(start))
            if(Visited.find(dest.vertex) == Visited.end())
                index = DFSUtil(index, dest.vertex, Visited, TopSort);

        TopSort[index] = this->_id_to_node_.at(start);
        return index - 1;
    }
    
    template<typename T, typename W>
    std::pair<int, int> DirectedGraph<T, W>::getDegree(T vertex) const
    {
        if(this->_node_to_id_.find(vertex) != this->_node_to_id_.end())
        {
            unsigned int id = this->_node_to_id_.at(vertex);

            int out_degree = this->_ADJACENCY_LIST_.at(id).size();
            int in_degree = 0;
            for(const std::pair<unsigned int, std::vector<Node<W>>> &edges : this->_ADJACENCY_LIST_)
            {
                if(std::find(edges.second.begin(), edges.second.end(), id) != edges.second.end())
                    in_degree++;
            }

            return std::pair<int, int>(in_degree, out_degree);
        }
        else
            return std::pair<int, int>(-1, -1);
    }
}

#endif