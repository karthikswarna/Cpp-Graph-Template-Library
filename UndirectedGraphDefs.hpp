#ifndef UNDIRECTED_GRAPH_DEFINITIONS_H
#define UNDIRECTED_GRAPH_DEFINITIONS_H

#include "UndirectedGraph.hpp"

namespace Graph
{
    /*
     * ITERATOR RELATED FUNCTIONS
     */
    template<typename T, typename W>
    typename UndirectedGraph<T, W>::node_iterator UndirectedGraph<T, W>::begin()
    {
        return node_iterator(this->_ADJACENCY_LIST_.begin(), &this->_id_to_node_, &this->_node_to_id_);
    }

    template<typename T, typename W>
    typename UndirectedGraph<T, W>::node_iterator UndirectedGraph<T, W>::end()
    {
        return node_iterator(this->_ADJACENCY_LIST_.end(), &this->_id_to_node_, &this->_node_to_id_);
    }

    template<typename T, typename W>
    typename UndirectedGraph<T, W>::const_node_iterator UndirectedGraph<T, W>::begin() const
    {
        return const_node_iterator(this->_ADJACENCY_LIST_.begin(), &this->_id_to_node_);
    }

    template<typename T, typename W>
    typename UndirectedGraph<T, W>::const_node_iterator UndirectedGraph<T, W>::cbegin() const
    {
        return const_node_iterator(this->_ADJACENCY_LIST_.cbegin(), &this->_id_to_node_);
    }

    template<typename T, typename W>
    typename UndirectedGraph<T, W>::const_node_iterator UndirectedGraph<T, W>::end() const
    {
        return const_node_iterator(this->_ADJACENCY_LIST_.end(), &this->_id_to_node_);
    }

    template<typename T, typename W>
    typename UndirectedGraph<T, W>::const_node_iterator UndirectedGraph<T, W>::cend() const
    {
        return const_node_iterator(this->_ADJACENCY_LIST_.cend(), &this->_id_to_node_);
    }
    
    template<typename T, typename W>
    typename UndirectedGraph<T, W>::edge_iterator UndirectedGraph<T, W>::begin(int)
    {
        typename std::unordered_map<unsigned int, std::vector<Node<W>>>::iterator it = this->_ADJACENCY_LIST_.begin();
        if(this->empty())
            return edge_iterator(it, it, &this->_id_to_node_);

        typename std::unordered_map<unsigned int, std::vector<Node<W>>>::iterator first_it = it;    // This has the first non-empty mapping.
        typename std::unordered_map<unsigned int, std::vector<Node<W>>>::iterator last_it = it;     // This has the last non-empty mapping.
        bool flag = false;

        // Finding first_it and last_it.    
        while(it != this->_ADJACENCY_LIST_.end())
        {
            if(!(it->second.empty()))
            {
                if(flag == false)
                {
                    first_it = it;
                    flag = true;
                }

                last_it = it;
            }

            ++it;
        }

        return edge_iterator(first_it, last_it, &this->_id_to_node_, first_it->second.begin());
    }

    template<typename T, typename W>
    typename UndirectedGraph<T, W>::edge_iterator UndirectedGraph<T, W>::end(int)
    {
        typename std::unordered_map<unsigned int, std::vector<Node<W>>>::iterator it = this->_ADJACENCY_LIST_.begin();
        if(this->empty())
            return edge_iterator(it, it, &this->_id_to_node_);

        typename std::unordered_map<unsigned int, std::vector<Node<W>>>::iterator first_it = it;
        typename std::unordered_map<unsigned int, std::vector<Node<W>>>::iterator last_it = it;
        bool flag = false;

        while(it != this->_ADJACENCY_LIST_.end())
        {
            if(!(it->second.empty()))
            {
                if(flag == false)
                {
                    first_it = it;
                    flag = true;
                }

                last_it = it;
            }

            ++it;
        }

        return edge_iterator(last_it, last_it, &this->_id_to_node_, last_it->second.end());
    }

    template<typename T, typename W>
    typename UndirectedGraph<T, W>::const_edge_iterator UndirectedGraph<T, W>::begin(int) const
    {
        typename std::unordered_map<unsigned int, std::vector<Node<W>>>::const_iterator it = this->_ADJACENCY_LIST_.begin();
        if(this->empty())
            return const_edge_iterator(it, it, &this->_id_to_node_);

        typename std::unordered_map<unsigned int, std::vector<Node<W>>>::const_iterator first_it = it;    // This has the first non-empty mapping.
        typename std::unordered_map<unsigned int, std::vector<Node<W>>>::const_iterator last_it = it;     // This has the last non-empty mapping.
        bool flag = false;

        // Finding first_it and last_it.    
        while(it != this->_ADJACENCY_LIST_.end())
        {
            if(!(it->second.empty()))
            {
                if(flag == false)
                {
                    first_it = it;
                    flag = true;
                }

                last_it = it;
            }

            ++it;
        }

        return const_edge_iterator(first_it, last_it, &this->_id_to_node_, first_it->second.begin());
    }

    template<typename T, typename W>
    typename UndirectedGraph<T, W>::const_edge_iterator UndirectedGraph<T, W>::end(int) const
    {
        typename std::unordered_map<unsigned int, std::vector<Node<W>>>::const_iterator it = this->_ADJACENCY_LIST_.begin();
        if(this->empty())
            return const_edge_iterator(it, it, &this->_id_to_node_);

        typename std::unordered_map<unsigned int, std::vector<Node<W>>>::const_iterator first_it = it;
        typename std::unordered_map<unsigned int, std::vector<Node<W>>>::const_iterator last_it = it;
        bool flag = false;

        while(it != this->_ADJACENCY_LIST_.end())
        {
            if(!(it->second.empty()))
            {
                if(flag == false)
                {
                    first_it = it;
                    flag = true;
                }

                last_it = it;
            }

            ++it;
        }

        return const_edge_iterator(last_it, last_it, &this->_id_to_node_, last_it->second.end());
    }

    template<typename T, typename W>
    typename UndirectedGraph<T, W>::const_edge_iterator UndirectedGraph<T, W>::cbegin(int) const
    {
        typename std::unordered_map<unsigned int, std::vector<Node<W>>>::const_iterator it = this->_ADJACENCY_LIST_.cbegin();
        if(this->empty())
            return const_edge_iterator(it, it, &this->_id_to_node_);

        typename std::unordered_map<unsigned int, std::vector<Node<W>>>::const_iterator first_it = it;    // This has the first non-empty mapping.
        typename std::unordered_map<unsigned int, std::vector<Node<W>>>::const_iterator last_it = it;     // This has the last non-empty mapping.
        bool flag = false;

        // Finding first_it and last_it.    
        while(it != this->_ADJACENCY_LIST_.cend())
        {
            if(!(it->second.empty()))
            {
                if(flag == false)
                {
                    first_it = it;
                    flag = true;
                }

                last_it = it;
            }

            ++it;
        }

        return const_edge_iterator(first_it, last_it, &this->_id_to_node_, first_it->second.cbegin());
    }

    template<typename T, typename W>
    typename UndirectedGraph<T, W>::const_edge_iterator UndirectedGraph<T, W>::cend(int) const
    {
        typename std::unordered_map<unsigned int, std::vector<Node<W>>>::const_iterator it = this->_ADJACENCY_LIST_.cbegin();
        if(this->empty())
            return const_edge_iterator(it, it, &this->_id_to_node_);

        typename std::unordered_map<unsigned int, std::vector<Node<W>>>::const_iterator first_it = it;
        typename std::unordered_map<unsigned int, std::vector<Node<W>>>::const_iterator last_it = it;
        bool flag = false;

        while(it != this->_ADJACENCY_LIST_.cend())
        {
            if(!(it->second.empty()))
            {
                if(flag == false)
                {
                    first_it = it;
                    flag = true;
                }

                last_it = it;
            }

            ++it;
        }

        return const_edge_iterator(last_it, last_it, &this->_id_to_node_, last_it->second.cend());
    }

    /*
     * NON-ITERATOR RELATED FUNCTIONS
     */
    template<typename T, typename W>
    UndirectedGraph<T, W>::UndirectedGraph() noexcept
    {
    }

    template<typename T, typename W>
    UndirectedGraph<T, W>::~UndirectedGraph() noexcept 
    {
        this->_ADJACENCY_LIST_.clear();
        this->_id_to_node_.clear();
        this->_node_to_id_.clear();
    }

    template<typename T, typename W>
    UndirectedGraph<T, W>::UndirectedGraph(const UndirectedGraph &rhs) noexcept
        : _ADJACENCY_LIST_ ( rhs._ADJACENCY_LIST_ )
        , _id_to_node_ ( rhs._id_to_node_ )
        , _node_to_id_ (rhs._node_to_id_)
        , isNegWeighted ( rhs.isNegWeighted )
        , isWeighted ( rhs.isWeighted )
        , _id_ ( rhs._id_ )
    {
    }

    template<typename T, typename W>
    UndirectedGraph<T, W>& UndirectedGraph<T, W>::operator=(const UndirectedGraph &rhs) noexcept
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
    UndirectedGraph<T, W>::UndirectedGraph(UndirectedGraph &&rhs) noexcept
        : _ADJACENCY_LIST_ ( std::move(rhs._ADJACENCY_LIST_) )
        , _id_to_node_ ( std::move(rhs._id_to_node_) )
        , _node_to_id_ ( std::move(rhs._node_to_id_) )
        , isNegWeighted (std::move(rhs.isNegWeighted) )
        , isWeighted ( std::move(rhs.isWeighted) )
        , _id_ ( std::move(rhs._id_) )
    {
    }

    template<typename T, typename W>
    UndirectedGraph<T, W>& UndirectedGraph<T, W>::operator=(UndirectedGraph &&rhs) noexcept
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
    bool UndirectedGraph<T, W>::operator==(const UndirectedGraph &rhs) const
    {
        return this->_ADJACENCY_LIST_ == rhs._ADJACENCY_LIST_
            && this->_id_to_node_ == rhs._id_to_node_
            && this->_node_to_id_ == rhs._node_to_id_
            && this->isNegWeighted == rhs.isNegWeighted
            && this->isWeighted == rhs.isWeighted;
    }

    template<typename T, typename W>
    bool UndirectedGraph<T, W>::operator!=(const UndirectedGraph &rhs) const
    {
        return this->_ADJACENCY_LIST_ != rhs._ADJACENCY_LIST_
            || this->_id_to_node_ != rhs._id_to_node_
            || this->_node_to_id_ != rhs._node_to_id_
            || this->isNegWeighted != rhs.isNegWeighted
            || this->isWeighted != rhs.isWeighted;
    }

    template<typename T, typename W>
    void UndirectedGraph<T, W>::swap(UndirectedGraph &rhs)
    {
        this->_ADJACENCY_LIST_.swap(rhs._ADJACENCY_LIST_);
        this->_id_to_node_.swap(rhs._id_to_node_);
        this->_node_to_id_.swap(rhs._node_to_id_);
        std::swap(this->isNegWeighted, rhs.isNegWeighted);
        std::swap(this->isWeighted, rhs.isWeighted);
        std::swap(this->_id_, rhs._id_);
    }

    template<typename T, typename W>
    void UndirectedGraph<T, W>::clear()
    {
        this->_ADJACENCY_LIST_.clear();
        this->_id_to_node_.clear();
        this->_node_to_id_.clear();
        this->isNegWeighted = false;
        this->isWeighted = false;
        this->_id_ = 1;
    }

    template<typename T, typename W>
    bool UndirectedGraph<T, W>::addVertex(T vertex)
    {
        try
        {
            if(this->_node_to_id_.find(vertex) == this->_node_to_id_.end())
            {
                this->_id_to_node_.insert(std::make_pair(this->_id_, vertex));
                this->_node_to_id_.insert(std::make_pair(vertex, this->_id_));
                this->_ADJACENCY_LIST_.insert(std::make_pair(this->_id_, std::vector<Node<W>>()));
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

    template<typename T, typename W>
    bool UndirectedGraph<T, W>::addVertices(const std::vector<T> &vertices)
    {
        try
        {
            for(const T &vertex : vertices)
            {
                if(this->_node_to_id_.find(vertex) == this->_node_to_id_.end())
                {
                    this->_id_to_node_.insert(std::make_pair(this->_id_, vertex));
                    this->_node_to_id_.insert(std::make_pair(vertex, this->_id_));
                    this->_ADJACENCY_LIST_.insert(std::make_pair(this->_id_, std::vector<Node<W>>()));
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

    template<typename T, typename W>
    bool UndirectedGraph<T, W>::addEdge(T vertex1, T vertex2, W weight)
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
            if(weight != 1)
                this->isWeighted = true;

            std::vector<Node<W>> edge_list = this->_ADJACENCY_LIST_.at(id1);
            if(std::find(edge_list.begin(), edge_list.end(), Node<W>{id2, weight}) == edge_list.end())
                this->_ADJACENCY_LIST_.at(id1).push_back(Node<W>{id2, weight});

            edge_list = this->_ADJACENCY_LIST_.at(id2);
            if(std::find(edge_list.begin(), edge_list.end(), Node<W>{id1, weight}) == edge_list.end())
                this->_ADJACENCY_LIST_.at(id2).push_back(Node<W>{id1, weight});

            return true;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            return false;
        }
    }

    template<typename T, typename W>
    bool UndirectedGraph<T, W>::addEdges(const std::vector<std::pair<T, T>> &edges)
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

                edge_list = this->_ADJACENCY_LIST_.at(id2);
                if(std::find(edge_list.begin(), edge_list.end(), id1) == edge_list.end())
                    this->_ADJACENCY_LIST_.at(id2).push_back(Node<W>{id1});
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
    bool UndirectedGraph<T, W>::addEdges(const std::vector<std::tuple<T, T, W>> &edges)
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
                if(weight != 1)
                    this->isWeighted = true;

                std::vector<Node<W>> edge_list = this->_ADJACENCY_LIST_.at(id1);
                if(std::find(edge_list.begin(), edge_list.end(), Node<W>{id2, weight}) == edge_list.end())
                    this->_ADJACENCY_LIST_.at(id1).push_back(Node<W>{id2, weight});

                edge_list = this->_ADJACENCY_LIST_.at(id2);
                if(std::find(edge_list.begin(), edge_list.end(), Node<W>{id1, weight}) == edge_list.end())
                    this->_ADJACENCY_LIST_.at(id2).push_back(Node<W>{id1, weight});
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
    bool UndirectedGraph<T, W>::removeVertex(T vertex)
    {
        try
        {
            if(this->_node_to_id_.find(vertex) != this->_node_to_id_.end())
            {
                unsigned int id = this->_node_to_id_.at(vertex);
                
                // Removing from _id_to_node_.
                this->_id_to_node_.erase(id);

                // Removing from _ADJACENCY_LIST_.
                this->_ADJACENCY_LIST_.erase(id);
                for(typename std::unordered_map<unsigned int, std::vector<Node<W>>>::iterator it = this->_ADJACENCY_LIST_.begin(); it != this->_ADJACENCY_LIST_.end(); it++)
                {
                    if(std::find(it->second.begin(), it->second.end(), id) != it->second.end())
                    {
                        // Erase-Remove Idiom to remove vertex from the list.
                        it->second.erase(std::remove(it->second.begin(), it->second.end(), id), it->second.end());
                    }
                }

                // Removing from _node_to_id_.
                this->_node_to_id_.erase(vertex);

                // Decrementing the id values for id's greater than the id of removed vertex.
                // for(std::pair<unsigned int, T> &node : this->_id_to_node_)
                //     if(node.first > id)
                //         --node.first;

                // for(std::pair<T, unsigned int> &node : this->_node_to_id_)
                //     if(node.second > id)
                //         --node.second;

                bool stillWeighted = false;
                bool stillNegWeighted = false;
                for(const std::pair<unsigned int, std::vector<Node<W>>> &edges : this->_ADJACENCY_LIST_)
                {
                    // if(edges.first > id)
                    //     --edges.first;

                    for(const Node<W> &node : edges.second)
                    {
                        // if(node.vertex > id)
                        //     --node.vertex;

                        // Finding whether the graph is still weighted/negative weighted.
                        if(node.weight < 0)
                            stillNegWeighted = true;
                        if(node.weight != 1)
                            stillWeighted = true;
                    }
                }

                // (this->_id_)--;
                this->isWeighted = stillWeighted;
                this->isNegWeighted = stillNegWeighted;
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
    bool UndirectedGraph<T, W>::removeVertices(const std::vector<T> &vertices)
    {
        try
        {
            for(const T &vertex : vertices)
            {
                if(this->_node_to_id_.find(vertex) != this->_node_to_id_.end())
                {
                    unsigned int id = this->_node_to_id_.at(vertex);

                    // Removing from _id_to_node_.
                    this->_id_to_node_.erase(id);

                    // Removing from _ADJACENCY_LIST_.
                    this->_ADJACENCY_LIST_.erase(id);
                    for(typename std::unordered_map<unsigned int, std::vector<Node<W>>>::iterator it = this->_ADJACENCY_LIST_.begin(); it != this->_ADJACENCY_LIST_.end(); it++)
                    {
                        if(std::find(it->second.begin(), it->second.end(), id) != it->second.end())
                        {
                            // Erase-Remove Idiom to remove vertex from the list.
                            it->second.erase(std::remove(it->second.begin(), it->second.end(), id), it->second.end());
                        }
                    }

                    // Removing from _node_to_id_.
                    this->_node_to_id_.erase(vertex);

                    // Decrementing the id values for id's greater than the id of removed vertex.
                    // for(std::pair<unsigned int, T> &node : this->_id_to_node_)
                    //     if(node.first > id)
                    //         --node.first;

                    // for(std::pair<T, unsigned int> &node : this->_node_to_id_)
                    //     if(node.second > id)
                    //         --node.second;

                    bool stillWeighted = false;
                    bool stillNegWeighted = false;
                    for(const std::pair<unsigned int, std::vector<Node<W>>> &edges : this->_ADJACENCY_LIST_)
                    {
                        // if(edges.first > id)
                        //     --edges.first;

                        for(const Node<W> &node : edges.second)
                        {
                            // if(node.vertex > id)
                            //     --node.vertex;

                            // Finding whether the graph is still weighted/negative weighted.
                            if(node.weight < 0)
                                stillNegWeighted = true;
                            if(node.weight != 1)
                                stillWeighted = true;
                        }
                    }

                    // (this->_id_)--;
                    this->isWeighted = stillWeighted;
                    this->isNegWeighted = stillNegWeighted;
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
    bool UndirectedGraph<T, W>::removeEdge(T vertex1, T vertex2)
    {
        try
        {
            if(this->_node_to_id_.find(vertex1) != this->_node_to_id_.end() && this->_node_to_id_.find(vertex2) != this->_node_to_id_.end())
            {
                unsigned int id1 = this->_node_to_id_.at(vertex1);
                unsigned int id2 = this->_node_to_id_.at(vertex2);

                // Removing id2 from adjacency list of id1.
                std::vector<Node<W>> &edge_list1 = this->_ADJACENCY_LIST_.at(id1);
                if(std::find(edge_list1.begin(), edge_list1.end(), id2) != edge_list1.end())
                {
                    edge_list1.erase(std::remove(edge_list1.begin(), edge_list1.end(), id2), edge_list1.end());
                }

                // Removing id1 from adjacency list of id2.
                std::vector<Node<W>> &edge_list2 = this->_ADJACENCY_LIST_.at(id2);
                if(std::find(edge_list2.begin(), edge_list2.end(), id1) != edge_list2.end())
                {
                    edge_list2.erase(std::remove(edge_list2.begin(), edge_list2.end(), id1), edge_list2.end());
                }

                this->checkGraph();
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
    bool UndirectedGraph<T, W>::removeEdges(const std::vector<std::pair<T, T>> &edges)
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

                    // Removing id2 from adjacency list of id1.
                    std::vector<Node<W>> &edge_list1 = this->_ADJACENCY_LIST_.at(id1);
                    if(std::find(edge_list1.begin(), edge_list1.end(), id2) != edge_list1.end())
                    {
                        edge_list1.erase(std::remove(edge_list1.begin(), edge_list1.end(), id2), edge_list1.end());
                    }

                    // Removing id1 from adjacency list of id2.
                    std::vector<Node<W>> &edge_list2 = this->_ADJACENCY_LIST_.at(id2);
                    if(std::find(edge_list2.begin(), edge_list2.end(), id1) != edge_list2.end())
                    {
                        edge_list2.erase(std::remove(edge_list2.begin(), edge_list2.end(), id1), edge_list2.end());
                    }

                    this->checkGraph();
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
    bool UndirectedGraph<T, W>::removeEdge(T vertex1, T vertex2, W weight)
    {
        try
        {
            if(this->_node_to_id_.find(vertex1) != this->_node_to_id_.end() && this->_node_to_id_.find(vertex2) != this->_node_to_id_.end())
            {
                unsigned int id1 = this->_node_to_id_.at(vertex1);
                unsigned int id2 = this->_node_to_id_.at(vertex2);

                // Removing id2 from adjacency list of id1.
                std::vector<Node<W>> &edge_list1 = this->_ADJACENCY_LIST_.at(id1);
                if(std::find(edge_list1.begin(), edge_list1.end(), Node<W>{id2, weight}) != edge_list1.end())
                {
                    edge_list1.erase(std::remove(edge_list1.begin(), edge_list1.end(), Node<W>{id2, weight}), edge_list1.end());
                }

                // Removing id1 from adjacency list of id2.
                std::vector<Node<W>> &edge_list2 = this->_ADJACENCY_LIST_.at(id2);
                if(std::find(edge_list2.begin(), edge_list2.end(), Node<W>{id1, weight}) != edge_list2.end())
                {
                    edge_list2.erase(std::remove(edge_list2.begin(), edge_list2.end(), Node<W>{id1, weight}), edge_list2.end());
                }

                this->checkGraph();
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
    bool UndirectedGraph<T, W>::removeEdges(const std::vector<std::tuple<T, T, W>> &edges)
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
                    unsigned int id1 = this->_node_to_id_.at(vertex1);
                    unsigned int id2 = this->_node_to_id_.at(vertex2);

                    // Removing id2 from adjacency list of id1.
                    std::vector<Node<W>> &edge_list1 = this->_ADJACENCY_LIST_.at(id1);
                    if(std::find(edge_list1.begin(), edge_list1.end(), Node<W>{id2, weight}) != edge_list1.end())
                    {
                        edge_list1.erase(std::remove(edge_list1.begin(), edge_list1.end(), Node<W>{id2, weight}), edge_list1.end());
                    }

                    // Removing id1 from adjacency list of id2.
                    std::vector<Node<W>> &edge_list2 = this->_ADJACENCY_LIST_.at(id2);
                    if(std::find(edge_list2.begin(), edge_list2.end(), Node<W>{id1, weight}) != edge_list2.end())
                    {
                        edge_list2.erase(std::remove(edge_list2.begin(), edge_list2.end(), Node<W>{id1, weight}), edge_list2.end());
                    }

                    this->checkGraph();
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
    void UndirectedGraph<T, W>::printDFS(unsigned int start, std::unordered_set<unsigned int> &Visited) const
    {
        Visited.insert(start);
        std::cout << this->_id_to_node_.at(start);
        
        std::vector<Node<W>> edge_list = this->_ADJACENCY_LIST_.at(start);
        for(Node<W> N : edge_list)
        {
            if(Visited.find(N.vertex) == Visited.end())
            {
                std::cout << " -> ";
                printDFS(N.vertex, Visited);
            }
        }
    }

    template<typename T, typename W>
    void UndirectedGraph<T, W>::printDFS() const
    {
        std::cout << "DEPTH FIRST SEARCH\n";

        std::unordered_set<unsigned int> Visited;
        for(const std::pair<unsigned int, std::vector<Node<W>>> &edges : this->_ADJACENCY_LIST_)
        {
            if(Visited.find(edges.first) == Visited.end())
            {
                printDFS(edges.first, Visited);
                std::cout << '\n';
            }
        }
    }

    template<typename T, typename W>
    void UndirectedGraph<T, W>::printBFS(unsigned int start, std::unordered_set<unsigned int> &Visited) const
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

            for(Node<W> N : this->_ADJACENCY_LIST_.at(temp))
            {
                if(Visited.find(N.vertex) == Visited.end())
                {
                    Visited.insert(N.vertex);
                    Q.push(N.vertex);
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

    template<typename T, typename W>
    void UndirectedGraph<T, W>::printBFS() const
    {
        std::cout << "BREADTH FIRST SEARCH" << '\n';

        std::unordered_set<unsigned int> Visited;
        for(const std::pair<unsigned int, std::vector<Node<W>>> &edges : this->_ADJACENCY_LIST_)
        {
            if(Visited.find(edges.first) == Visited.end())
            {
                Visited.insert(edges.first);
                printBFS(edges.first, Visited);
            }
        }
    }

    template<typename T, typename W>
    std::vector<std::pair<T, T>> UndirectedGraph<T, W>::getCutEdges() const
    {
        unsigned int id = 0;
        std::vector<std::pair<T, T>> Bridges;
        std::unordered_set<unsigned int> Visited;
        std::unordered_map<unsigned int, unsigned int> Ids;
        std::unordered_map<unsigned int, unsigned int> Low;

        for(const std::pair<unsigned int, T> &vertex : this->_id_to_node_)
            if(Visited.find(vertex.first) == Visited.end())
                getCutEdgesUtil(vertex.first, 0, id, Bridges, Visited, Ids, Low);
        
        return Bridges;
    }

    template<typename T, typename W>
    void UndirectedGraph<T, W>::getCutEdgesUtil(unsigned int current, unsigned int parent, unsigned int &id, std::vector<std::pair<T, T>> &Bridges, std::unordered_set<unsigned int> &Visited, std::unordered_map<unsigned int, unsigned int> &Ids, std::unordered_map<unsigned int, unsigned int> &Low) const
    {
        Visited.insert(current);
        Ids[current] = Low[current] = id++;

        for(const Node<W> &node : this->_ADJACENCY_LIST_.at(current))
        {
            unsigned int child = node.vertex;

            // The edge leads back to parent in DFS tree(in undirected graph).
            if(child == parent) continue;
            
            // Visited[child] = false - The edge is part of DFS tree.
            if(Visited.find(child) == Visited.end())
            {
                getCutEdgesUtil(child, current, id, Bridges, Visited, Ids, Low);
                
                // Relaxation while recursive callback(propagating the low-link values). 
                Low[current] = std::min(Low[current], Low[child]);
                
                // Finding the bridges - There is no back-edge from 'child' to any of the ancestors, including to 'current'.
                if(Low[child] > Ids[current])
                    Bridges.push_back(std::pair<T, T>(this->_id_to_node_.at(current), this->_id_to_node_.at(child)));
            }
            // Visited[child] = true && child ≠ parent - The edge is back edge to one of the ancestors.
            else
                // Updating the low-link values using back-edges.
                Low[current] = std::min(Low[current], Ids[child]);
        }
    }

    template<typename T, typename W>
    std::vector<T> UndirectedGraph<T, W>::getCutVertices() const
    {
        unsigned int id = 0;
        std::vector<T> ArtPoints;
        std::unordered_set<unsigned int> Visited;
        std::unordered_map<unsigned int, unsigned int> Ids;
        std::unordered_map<unsigned int, unsigned int> Low;

        for(const std::pair<unsigned int, T> &vertex : this->_id_to_node_)
            if(Visited.find(vertex.first) == Visited.end())
                getCutVerticesUtil(id, ArtPoints, Visited, Ids, Low, vertex.first, 0);
        
        return ArtPoints;
    }

    template<typename T, typename W>
    void UndirectedGraph<T, W>::getCutVerticesUtil(unsigned int &id, std::vector<T> &ArtPoints, std::unordered_set<unsigned int> &Visited, std::unordered_map<unsigned int, unsigned int> &Ids, std::unordered_map<unsigned int, unsigned int> &Low, unsigned int current, unsigned int parent) const
    {
        Visited.insert(current);
        Ids[current] = Low[current] = id++;

        int rootNodeOutgoingEdgeCount = 0;

        for(const Node<W> &node : this->_ADJACENCY_LIST_.at(current))
        {
            unsigned int child = node.vertex;

            // The edge leads back to parent in DFS tree(in undirected graph).
            if(current == parent) continue;

            // Visited[child] = false - The edge is part of DFS tree.
            if(Visited.find(child) == Visited.end())
            {
                getCutVerticesUtil(id, ArtPoints, Visited, Ids, Low, child, current);

                // Relaxation while recursive callback(propagating the low-link values). 
                Low[current] = std::min(Low[current], Low[child]);

                // Finding the articulation points - There is no back-edge from 'child' to any of the ancestors(back-edge to 'current' is allowed).
                if(Low[child] >= Ids[current] && parent != 0)
                    ArtPoints.push_back(this->_id_to_node_.at(current));
                
                rootNodeOutgoingEdgeCount++;
            }
            // Visited[child] = true && child ≠ parent - The edge is back-edge to one of the ancestors.
            else
                // Updating the low-link values using back-edges.
                Low[current] = std::min(Low[current], Ids[child]);
            
        }

        // If the parent node in this call is the root node && and has more than one outgoing edges - it is an articulation point.
        if(parent == 0 && rootNodeOutgoingEdgeCount > 1)
            ArtPoints.push_back(this->_id_to_node_.at(current));
    }

    template<typename T, typename W>
    std::vector<std::vector<T>> UndirectedGraph<T, W>::getConnectedComponents() const
    {
        std::queue<unsigned int> Q;
        std::unordered_set<unsigned int> Visited;
        std::vector<std::vector<T>> ConnectedComponents;

        // For each connected component.
        for(const std::pair<unsigned int, T> &vertex : this->_id_to_node_)
        {
            if(Visited.find(vertex.first) == Visited.end())
            {
                std::vector<T> Component;
                Component.push_back(this->_id_to_node_.at(vertex.first));
                Visited.insert(vertex.first);
                Q.push(vertex.first);
                
                // Find all vertices in the component.
                while(!Q.empty())
                {
                    unsigned int top = Q.front();
                    Q.pop();

                    for(const Node<W> &node : this->_ADJACENCY_LIST_.at(top))
                    {
                        if(Visited.find(node.vertex) == Visited.end())
                        {
                            Component.push_back(this->_id_to_node_.at(node.vertex));
                            Visited.insert(node.vertex);
                            Q.push(node.vertex);
                        }
                    }
                }

                ConnectedComponents.push_back(Component);
            }
        }

        return ConnectedComponents;
    }

    template<typename W>
    struct minTupleComp
    { 
        constexpr bool operator()(const std::tuple<unsigned int, unsigned int, W> &a, const std::tuple<unsigned int, unsigned int, W> &b) const noexcept
        {
            return std::get<2>(a) > std::get<2>(b);
        }
    };

    // Lazy implementation of the Prim's algorithm for finding MST in an undirected graph.
    template<typename T, typename W>
    std::vector<std::tuple<T, T, W>> UndirectedGraph<T, W>::getMinimumSpanningTree() const
    {
        // Empty spanning tree for empty graph.
        if(this->_ADJACENCY_LIST_.size() == 0)
            return std::vector<std::tuple<T, T, W>>();

        typedef std::tuple<unsigned int, unsigned int, W> tuple;

        std::priority_queue<tuple, std::vector<tuple>, minTupleComp<W>> Q;
        int maxEdges = this->_id_to_node_.size() - 1;
        std::unordered_set<unsigned int> mstVertices;                       // Set of vertices which are added in the MST.
        std::vector<std::tuple<T, T, W>> mstEdges;                          // Vector of edges added in the MST.
        int edgeCount = 0;                                                  // Tracks the number of edges included in the MST.
        
        // Initialization phase. Add 's' to the MST vertex set and add all its edges into the priority queue.
        unsigned int s = (this->_id_to_node_.begin())->first;
        mstVertices.insert(s);
        for(const Node<W> &node : this->_ADJACENCY_LIST_.at(s))
            if(node.vertex != s)                                            // Simplified check for vertices not in mstVertices set.
                Q.push(tuple(s, node.vertex, node.weight));

        // Loop until a MST is found or priority queue is empty.
        while(!Q.empty() && edgeCount != maxEdges)
        {
            tuple edge = Q.top();
            s = std::get<1>(edge);
            Q.pop();

            // If the current vertex is already in MST, discard this tuple.
            if(mstVertices.find(s) != mstVertices.end())
                continue;

            // Add the edge to the MST.
            mstEdges.push_back( std::tuple<T, T, W>( this->_id_to_node_.at(std::get<0>(edge)), this->_id_to_node_.at(std::get<1>(edge)), std::get<2>(edge) ) );
            edgeCount++;

            // Add the current vertex to MST & push all the edges of current vertex into priority queue. 
            mstVertices.insert(s);
            for(const Node<W> &node : this->_ADJACENCY_LIST_.at(s))
                if(mstVertices.find(node.vertex) == mstVertices.end())
                    Q.push(tuple(s, node.vertex, node.weight));
        }

        if(edgeCount != maxEdges)
            return std::vector<std::tuple<T, T, W>>();

        return mstEdges;
    }

    // There is a cycle in a graph only if there is a back-edge present in the graph.
    template<typename T, typename W>
    bool UndirectedGraph<T, W>::isCyclic() const
    {
        std::unordered_set<unsigned int> Visited;

        for(const std::pair<unsigned int, std::vector<Node<W>>> &edges : this->_ADJACENCY_LIST_)
            if(Visited.find(edges.first) == Visited.end())
                if(isCyclicUtil(edges.first, Visited, 0))
                    return true;

        return false;
    }

    template<typename T, typename W>
    bool UndirectedGraph<T, W>::isCyclicUtil(unsigned int current, std::unordered_set<unsigned int> &Visited, unsigned int parent) const
    {
        Visited.insert(current);

        for(const Node<W> &child : this->_ADJACENCY_LIST_.at(current))
        {
            if(Visited.find(child.vertex) == Visited.end())
                if(isCyclicUtil(child.vertex, Visited, current))
                    return true;
            // Visited[child] = true && child != parent -- There is a back-edge between 'child' and 'current'
            else if(child.vertex != parent)
                return true;
        }

        return false;
    }

    template<typename T, typename W>
    void UndirectedGraph<T, W>::printGraph() const
    {
        std::cout << "ADJACENCY LIST" << '\n';
        for(const std::pair<unsigned int, std::vector<Node<W>>> &e : this->_ADJACENCY_LIST_)
        {
            std::cout << this->_id_to_node_.at(e.first) << " ->  ";
            for(typename std::vector<Node<W>>::const_iterator it = e.second.begin(); it < e.second.end(); it++)
            {
                std::cout << this->_id_to_node_.at(it->vertex);
                if(it != e.second.end() - 1)
                    std::cout << ", ";
            }
            std::cout << '\n';
        }
    }

    template<typename T, typename W>
    void UndirectedGraph<T, W>::printWeightedGraph() const
    {
        std::cout << "ADJACENCY LIST" << '\n';
        for(const std::pair<unsigned int, std::vector<Node<W>>> &e : this->_ADJACENCY_LIST_)
        {
            std::cout << this->_id_to_node_.at(e.first) << " ->  ";
            for(typename std::vector<Node<W>>::const_iterator it = e.second.begin(); it < e.second.end(); it++)
            {
                std::cout << '(' << this->_id_to_node_.at(it->vertex) << ", " << it->weight << ')';
                if(it != e.second.end() - 1)
                    std::cout << ", ";
            }
            std::cout << '\n';
        }
    }

    template<typename T, typename W>
    int UndirectedGraph<T, W>::getDegree(T vertex) const
    {
        if(this->_node_to_id_.find(vertex) != this->_node_to_id_.end())
            return this->_ADJACENCY_LIST_.at(this->_node_to_id_.at(vertex)).size();
        else
            return -1;
    }

    template<typename T, typename W>
    bool UndirectedGraph<T, W>::empty() const
    {
        return this->_id_to_node_.empty();
    }
    
    template<typename T, typename W>
    void UndirectedGraph<T, W>::printMap() const
    {
        std::cout << "VERTEX MAP" << '\n';
        for(const std::pair<unsigned int, T> &e : this->_id_to_node_)
        {
            std::cout << e.first << ' ' << e.second << std::endl;
        }
    }

    template<typename T, typename W>
    void UndirectedGraph<T, W>::checkGraph()
    {
        // Finding whether the graph is still weighted/negative Weighted.
        bool stillWeighted = false;
        bool stillNegWeighted = false;
        for(const std::pair<unsigned int, std::vector<Node<W>>> &edges : this->_ADJACENCY_LIST_)
        {
            for(const Node<W> &node : edges.second)
            {
                if(node.weight < 0)
                    stillNegWeighted = true;
                if(node.weight != 1)
                    stillWeighted = true;
            }
        }

        this->isWeighted = stillWeighted;
        this->isNegWeighted = stillNegWeighted;
    }
}

#include "shortestPath.hpp"
#include "UndirectedEulerian.hpp"

#endif