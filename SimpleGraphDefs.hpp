#ifndef SIMPLE_GRAPH_DEFINITIONS_H
#define SIMPLE_GRAPH_DEFINITIONS_H

#include "SimpleGraph.hpp"

namespace Graph
{
    template<typename T>
    SimpleGraph<T>::SimpleGraph() noexcept
    {
    }

    template<typename T>
    SimpleGraph<T>::SimpleGraph(const SimpleGraph &rhs) noexcept
        : _ADJACENCY_LIST_ ( rhs._ADJACENCY_LIST_ )
        , _id_to_node_ ( rhs._id_to_node_ )
        , _node_to_id_ (rhs._node_to_id_)
        , _id_ ( rhs._id_ )
    {
    }

    template<typename T>
    SimpleGraph<T>::SimpleGraph(SimpleGraph &&rhs) noexcept
        : _ADJACENCY_LIST_ ( std::move(rhs._ADJACENCY_LIST_) )
        , _id_to_node_ ( std::move(rhs._id_to_node_) )
        , _node_to_id_ ( std::move(rhs._node_to_id_) )
        , _id_ ( std::move(rhs._id_) )
    {
    }

    template<typename T>
    SimpleGraph<T>& SimpleGraph<T>::operator=(const SimpleGraph &rhs) noexcept
    {
        this->_ADJACENCY_LIST_ = rhs._ADJACENCY_LIST_;
        this->_id_to_node_ = rhs._id_to_node_;
        this->_node_to_id_ = rhs._node_to_id_;
        this->_id_ = rhs._id_;
        return *this;
    }

    template<typename T>
    SimpleGraph<T>& SimpleGraph<T>::operator=(SimpleGraph &&rhs) noexcept
    {
        this->_ADJACENCY_LIST_ = std::move(rhs._ADJACENCY_LIST_);
        this->_id_to_node_ = std::move(rhs._id_to_node_);
        this->_node_to_id_ = std::move(rhs._node_to_id_);
        this->_id_ = std::move(rhs._id_);
        return *this;
    }

    template<typename T>
    SimpleGraph<T>::~SimpleGraph() noexcept 
    { 
        this->_ADJACENCY_LIST_.clear();
        this->_id_to_node_.clear();
        this->_node_to_id_.clear();
    }

    template<typename T>
    bool SimpleGraph<T>::addVertex(T vertex)
    {
        try
        {
            if(this->_node_to_id_.find(vertex) == this->_node_to_id_.end())
            {
                this->_id_to_node_.insert(std::make_pair(this->_id_, vertex));
                this->_node_to_id_.insert(std::make_pair(vertex, this->_id_));
                this->_ADJACENCY_LIST_.insert(std::make_pair(this->_id_, std::vector<unsigned int>()));
                (this->_id_)++;
            }
            return true;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            return false;
        }
    }

    template<typename T>
    bool SimpleGraph<T>::addVertices(const std::vector<T> &vertices)
    {
        try
        {
            for(const T &vertex : vertices)
            {
                if(this->_node_to_id_.find(vertex) == this->_node_to_id_.end())
                {
                    this->_id_to_node_.insert(std::make_pair(this->_id_, vertex));
                    this->_node_to_id_.insert(std::make_pair(vertex, this->_id_));
                    this->_ADJACENCY_LIST_.insert(std::make_pair(this->_id_, std::vector<unsigned int>()));
                    (this->_id_)++;
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

    template<typename T>
    bool SimpleGraph<T>::addEdge(T vertex1, T vertex2)
    {
        try
        {
            // If vertex1 is not previously there, add it to the list of nodes.
            if(this->_node_to_id_.find(vertex1) == this->_node_to_id_.end())
            {
                this->_id_to_node_.insert(std::make_pair(this->_id_, vertex1));
                this->_node_to_id_.insert(std::make_pair(vertex1, this->_id_));
                this->_ADJACENCY_LIST_.insert(std::make_pair(this->_id_, std::vector<unsigned int>{}));
                (this->_id_)++;
            }

            // If vertex2 is not previously there, add it to the list of nodes.
            if(this->_node_to_id_.find(vertex2) == this->_node_to_id_.end())
            {
                this->_id_to_node_.insert(std::make_pair(this->_id_, vertex2));
                this->_node_to_id_.insert(std::make_pair(vertex2, this->_id_));
                this->_ADJACENCY_LIST_.insert(std::make_pair(this->_id_, std::vector<unsigned int>{}));
                (this->_id_)++;
            }

            int id1 = this->_node_to_id_.at(vertex1);
            int id2 = this->_node_to_id_.at(vertex2);

            std::vector<unsigned int> edge_list = this->_ADJACENCY_LIST_.at(id1);
            if(std::find(edge_list.begin(), edge_list.end(), id2) == edge_list.end())
                this->_ADJACENCY_LIST_.at(id1).push_back(id2);

            edge_list = this->_ADJACENCY_LIST_.at(id2);
            if(std::find(edge_list.begin(), edge_list.end(), id1) == edge_list.end())
                this->_ADJACENCY_LIST_.at(id2).push_back(id1);

            return true;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            return false;
        }
    }

    template<typename T>
    bool SimpleGraph<T>::addEdges(const std::vector<std::pair<T, T>> &edges)
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
                    this->_ADJACENCY_LIST_.insert(std::make_pair(this->_id_, std::vector<unsigned int>{}));
                    (this->_id_)++;
                }

                // If vertex2 is not previously there, add it to the list of nodes.
                if(this->_node_to_id_.find(vertex2) == this->_node_to_id_.end())
                {
                    this->_id_to_node_.insert(std::make_pair(this->_id_, vertex2));
                    this->_node_to_id_.insert(std::make_pair(vertex2, this->_id_));
                    this->_ADJACENCY_LIST_.insert(std::make_pair(this->_id_, std::vector<unsigned int>{}));
                    (this->_id_)++;
                }

                int id1 = this->_node_to_id_.at(vertex1);
                int id2 = this->_node_to_id_.at(vertex2);

                std::vector<unsigned int> edge_list = this->_ADJACENCY_LIST_.at(id1);
                if(std::find(edge_list.begin(), edge_list.end(), id2) == edge_list.end())
                    this->_ADJACENCY_LIST_.at(id1).push_back(id2);

                edge_list = this->_ADJACENCY_LIST_.at(id2);
                if(std::find(edge_list.begin(), edge_list.end(), id1) == edge_list.end())
                    this->_ADJACENCY_LIST_.at(id2).push_back(id1);
            }

            return true;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            return false;
        }    
    }

    template<typename T>
    bool SimpleGraph<T>::removeVertex(T vertex)
    {
        try
        {
            if(this->_node_to_id_.find(vertex) != this->_node_to_id_.end())
            {
                unsigned int id = this->_node_to_id_.at(vertex);
                this->_id_to_node_.erase(id);
                
                this->_ADJACENCY_LIST_.erase(id);
                for(typename std::unordered_map<unsigned int, std::vector<unsigned int>>::iterator it = this->_ADJACENCY_LIST_.begin(); it != this->_ADJACENCY_LIST_.end(); it++)
                {
                    if(std::find(it->second.begin(), it->second.end(), id) != it->second.end())
                    {
                        it->second.erase(std::remove(it->second.begin(), it->second.end(), id));
                    }
                }
                
                this->_node_to_id_.erase(vertex);
            }

            return true;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            return false;
        }
    }

    template<typename T>
    bool SimpleGraph<T>::removeVertices(const std::vector<T> &vertices)
    {
        try
        {
            for(const T &vertex : vertices)
            {
                if(this->_node_to_id_.find(vertex) != this->_node_to_id_.end())
                {
                    unsigned int id = this->_node_to_id_.at(vertex);
                    this->_id_to_node_.erase(id);
                    
                    this->_ADJACENCY_LIST_.erase(id);
                    for(typename std::unordered_map<unsigned int, std::vector<unsigned int>>::iterator it = this->_ADJACENCY_LIST_.begin(); it != this->_ADJACENCY_LIST_.end(); it++)
                    {
                        if(std::find(it->second.begin(), it->second.end(), id) != it->second.end())
                        {
                            it->second.erase(std::remove(it->second.begin(), it->second.end(), id));
                        }
                    }
                    
                    this->_node_to_id_.erase(vertex);
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

    template<typename T>
    bool SimpleGraph<T>::removeEdge(T vertex1, T vertex2)
    {
        try
        {
            if(this->_node_to_id_.find(vertex1) != this->_node_to_id_.end() && this->_node_to_id_.find(vertex2) != this->_node_to_id_.end())
            {
                unsigned int id1 = this->_node_to_id_.at(vertex1);
                unsigned int id2 = this->_node_to_id_.at(vertex2);

                std::vector<unsigned int> &edge_list1 = this->_ADJACENCY_LIST_.at(id1);
                if(std::find(edge_list1.begin(), edge_list1.end(), id2) != edge_list1.end())
                {
                    edge_list1.erase(std::remove(edge_list1.begin(), edge_list1.end(), id2));
                }

                std::vector<unsigned int> &edge_list2 = this->_ADJACENCY_LIST_.at(id2);
                if(std::find(edge_list2.begin(), edge_list2.end(), id1) != edge_list2.end())
                {
                    edge_list2.erase(std::remove(edge_list2.begin(), edge_list2.end(), id1));
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

    template<typename T>
    bool SimpleGraph<T>::removeEdges(const std::vector<std::pair<T, T>> &edges)
    {
        try
        {
            for(const std::pair<T, T> &e : edges)
            {
                T vertex1 = e.first;
                T vertex2 = e.second;
                
                if(this->_node_to_id_.find(vertex1) != this->_node_to_id_.end() && this->_node_to_id_.find(vertex2) != this->_node_to_id_.end())
                {
                    unsigned int id1 = this->_node_to_id_.at(vertex1);
                    unsigned int id2 = this->_node_to_id_.at(vertex2);

                    std::vector<unsigned int> &edge_list1 = this->_ADJACENCY_LIST_.at(id1);
                    if(std::find(edge_list1.begin(), edge_list1.end(), id2) != edge_list1.end())
                    {
                        edge_list1.erase(std::remove(edge_list1.begin(), edge_list1.end(), id2));
                    }

                    std::vector<unsigned int> &edge_list2 = this->_ADJACENCY_LIST_.at(id2);
                    if(std::find(edge_list2.begin(), edge_list2.end(), id1) != edge_list2.end())
                    {
                        edge_list2.erase(std::remove(edge_list2.begin(), edge_list2.end(), id1));
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

    template<typename T>
    void SimpleGraph<T>::printDFS(unsigned int start, std::unordered_set<unsigned int> &Visited) const
    {
        Visited.insert(start);
        std::cout << this->_id_to_node_.at(start);
        
        std::vector<unsigned int> edge_list = this->_ADJACENCY_LIST_.at(start);
        for(unsigned int v : edge_list)
        {
            if(Visited.find(v) == Visited.end())
            {
                std::cout << " -> ";
                printDFS(v, Visited);
            }
        }
    }

    template<typename T>
    void SimpleGraph<T>::printDFS() const
    {
        std::cout << "DEPTH FIRST SEARCH\n";

        std::unordered_set<unsigned int> Visited;
        for(const std::pair<unsigned int, std::vector<unsigned int>> &edges : this->_ADJACENCY_LIST_)
        {
            if(Visited.find(edges.first) == Visited.end())
            {
                printDFS(edges.first, Visited);
                std::cout << '\n';
            }
        }
    }

    template<typename T>
    void SimpleGraph<T>::printBFS(unsigned int start, std::unordered_set<unsigned int> &Visited) const
    {
        std::queue<unsigned int> Q;
        std::vector<unsigned int> path;
        unsigned int temp = start;
        Q.push(temp);
        Visited.insert(temp);

        while(!Q.empty())
        {
            temp = Q.front();
            Q.pop();
            path.push_back(temp);

            for(unsigned int v : this->_ADJACENCY_LIST_.at(temp))
            {
                if(Visited.find(v) == Visited.end())
                {
                    Visited.insert(v);
                    Q.push(v);
                }
            }
        }

        for(typename std::vector<unsigned int>::iterator it = path.begin(); it < path.end(); it++)
        {
            std::cout << this->_id_to_node_.at(*it);

            if(it != path.end() - 1)
                std::cout << " -> ";
        }
        std::cout << '\n';
    }

    template<typename T>
    void SimpleGraph<T>::printBFS() const
    {
        std::cout << "BREADTH FIRST SEARCH" << '\n';

        std::unordered_set<unsigned int> Visited;
        for(const std::pair<unsigned int, std::vector<unsigned int>> &edges : this->_ADJACENCY_LIST_)
        {
            if(Visited.find(edges.first) == Visited.end())
            {
                Visited.insert(edges.first);
                printBFS(edges.first, Visited);
            }
        }
    }

    template<typename T>
    void SimpleGraph<T>::printGraph() const
    {
        std::cout << "ADJACENCY LIST" << '\n';
        for(const std::pair<unsigned int, std::vector<unsigned int>> &e : this->_ADJACENCY_LIST_)
        {
            std::cout << this->_id_to_node_.at(e.first) << " ->  ";
            for(typename std::vector<unsigned int>::const_iterator it = e.second.begin(); it < e.second.end(); it++)
            {
                std::cout << this->_id_to_node_.at(*it);
                if(it != e.second.end() - 1)
                    std::cout << ", ";
            }
            std::cout << '\n';
        }
    }

    template<typename T>
    int SimpleGraph<T>::getDegree(T vertex) const
    {
        if(this->_node_to_id_.find(vertex) != this->_node_to_id_.end())
            return this->_ADJACENCY_LIST_.at(this->_node_to_id_.at(vertex)).size();
        else
            return -1;
    }
}

#endif