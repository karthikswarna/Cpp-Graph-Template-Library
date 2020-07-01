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
        return node_iterator(this->_ADJACENCY_LIST_.begin(), this->_id_to_node_);
    }

    template<typename T, typename W>
    typename UndirectedGraph<T, W>::node_iterator UndirectedGraph<T, W>::end()
    {
        return node_iterator(this->_ADJACENCY_LIST_.end(), this->_id_to_node_);
    }

    template<typename T, typename W>
    typename UndirectedGraph<T, W>::const_node_iterator UndirectedGraph<T, W>::begin() const
    {
        return const_node_iterator(this->_ADJACENCY_LIST_.begin(), this->_id_to_node_);
    }

    template<typename T, typename W>
    typename UndirectedGraph<T, W>::const_node_iterator UndirectedGraph<T, W>::cbegin() const
    {
        return const_node_iterator(this->_ADJACENCY_LIST_.cbegin(), this->_id_to_node_);
    }

    template<typename T, typename W>
    typename UndirectedGraph<T, W>::const_node_iterator UndirectedGraph<T, W>::end() const
    {
        return const_node_iterator(this->_ADJACENCY_LIST_.end(), this->_id_to_node_);
    }

    template<typename T, typename W>
    typename UndirectedGraph<T, W>::const_node_iterator UndirectedGraph<T, W>::cend() const
    {
        return const_node_iterator(this->_ADJACENCY_LIST_.cend(), this->_id_to_node_);
    }
    
    template<typename T, typename W>
    typename UndirectedGraph<T, W>::edge_iterator UndirectedGraph<T, W>::begin(int)
    {
        typename std::unordered_map<unsigned int, std::vector<Node<W>>>::iterator it = this->_ADJACENCY_LIST_.begin();
        if(this->empty())
            return edge_iterator(it, it, this->_id_to_node_);

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

        return edge_iterator(first_it, last_it, this->_id_to_node_, first_it->second.begin());
    }

    template<typename T, typename W>
    typename UndirectedGraph<T, W>::edge_iterator UndirectedGraph<T, W>::end(int)
    {
        typename std::unordered_map<unsigned int, std::vector<Node<W>>>::iterator it = this->_ADJACENCY_LIST_.begin();
        if(this->empty())
            return edge_iterator(it, it, this->_id_to_node_);

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

        return edge_iterator(last_it, last_it, this->_id_to_node_, last_it->second.end());
    }

    template<typename T, typename W>
    typename UndirectedGraph<T, W>::const_edge_iterator UndirectedGraph<T, W>::begin(int) const
    {
        typename std::unordered_map<unsigned int, std::vector<Node<W>>>::const_iterator it = this->_ADJACENCY_LIST_.begin();
        if(this->empty())
            return const_edge_iterator(it, it, this->_id_to_node_);

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

        return const_edge_iterator(first_it, last_it, this->_id_to_node_, first_it->second.begin());
    }

    template<typename T, typename W>
    typename UndirectedGraph<T, W>::const_edge_iterator UndirectedGraph<T, W>::end(int) const
    {
        typename std::unordered_map<unsigned int, std::vector<Node<W>>>::const_iterator it = this->_ADJACENCY_LIST_.begin();
        if(this->empty())
            return const_edge_iterator(it, it, this->_id_to_node_);

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

        return const_edge_iterator(last_it, last_it, this->_id_to_node_, last_it->second.end());
    }

    template<typename T, typename W>
    typename UndirectedGraph<T, W>::const_edge_iterator UndirectedGraph<T, W>::cbegin(int) const
    {
        typename std::unordered_map<unsigned int, std::vector<Node<W>>>::const_iterator it = this->_ADJACENCY_LIST_.cbegin();
        if(this->empty())
            return const_edge_iterator(it, it, this->_id_to_node_);

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

        return const_edge_iterator(first_it, last_it, this->_id_to_node_, first_it->second.cbegin());
    }

    template<typename T, typename W>
    typename UndirectedGraph<T, W>::const_edge_iterator UndirectedGraph<T, W>::cend(int) const
    {
        typename std::unordered_map<unsigned int, std::vector<Node<W>>>::const_iterator it = this->_ADJACENCY_LIST_.cbegin();
        if(this->empty())
            return const_edge_iterator(it, it, this->_id_to_node_);

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

        return const_edge_iterator(last_it, last_it, this->_id_to_node_, last_it->second.cend());
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
            if(weight > 1)
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
                if(weight > 1)
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
                this->_id_to_node_.erase(id);
                
                this->_ADJACENCY_LIST_.erase(id);
                for(typename std::unordered_map<unsigned int, std::vector<Node<W>>>::iterator it = this->_ADJACENCY_LIST_.begin(); it != this->_ADJACENCY_LIST_.end(); it++)
                {
                    if(std::find(it->second.begin(), it->second.end(), id) != it->second.end())
                    {
                        it->second.erase(std::remove(it->second.begin(), it->second.end(), id), it->second.end());
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
                    this->_id_to_node_.erase(id);
                    
                    this->_ADJACENCY_LIST_.erase(id);
                    for(typename std::unordered_map<unsigned int, std::vector<Node<W>>>::iterator it = this->_ADJACENCY_LIST_.begin(); it != this->_ADJACENCY_LIST_.end(); it++)
                    {
                        if(std::find(it->second.begin(), it->second.end(), id) != it->second.end())
                        {
                            it->second.erase(std::remove(it->second.begin(), it->second.end(), id), it->second.end());
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

    template<typename T, typename W>
    bool UndirectedGraph<T, W>::removeEdge(T vertex1, T vertex2)
    {
        try
        {
            if(this->_node_to_id_.find(vertex1) != this->_node_to_id_.end() && this->_node_to_id_.find(vertex2) != this->_node_to_id_.end())
            {
                unsigned int id1 = this->_node_to_id_.at(vertex1);
                unsigned int id2 = this->_node_to_id_.at(vertex2);

                std::vector<Node<W>> &edge_list1 = this->_ADJACENCY_LIST_.at(id1);
                if(std::find(edge_list1.begin(), edge_list1.end(), id2) != edge_list1.end())
                {
                    edge_list1.erase(std::remove(edge_list1.begin(), edge_list1.end(), id2), edge_list1.end());
                }

                std::vector<Node<W>> &edge_list2 = this->_ADJACENCY_LIST_.at(id2);
                if(std::find(edge_list2.begin(), edge_list2.end(), id1) != edge_list2.end())
                {
                    edge_list2.erase(std::remove(edge_list2.begin(), edge_list2.end(), id1), edge_list2.end());
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

                    std::vector<Node<W>> &edge_list1 = this->_ADJACENCY_LIST_.at(id1);
                    if(std::find(edge_list1.begin(), edge_list1.end(), id2) != edge_list1.end())
                    {
                        edge_list1.erase(std::remove(edge_list1.begin(), edge_list1.end(), id2), edge_list1.end());
                    }

                    std::vector<Node<W>> &edge_list2 = this->_ADJACENCY_LIST_.at(id2);
                    if(std::find(edge_list2.begin(), edge_list2.end(), id1) != edge_list2.end())
                    {
                        edge_list2.erase(std::remove(edge_list2.begin(), edge_list2.end(), id1), edge_list2.end());
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
    bool UndirectedGraph<T, W>::removeEdge(T vertex1, T vertex2, W weight)
    {
        try
        {
            if(this->_node_to_id_.find(vertex1) != this->_node_to_id_.end() && this->_node_to_id_.find(vertex2) != this->_node_to_id_.end())
            {
                unsigned int id1 = this->_node_to_id_.at(vertex1);
                unsigned int id2 = this->_node_to_id_.at(vertex2);

                std::vector<Node<W>> &edge_list1 = this->_ADJACENCY_LIST_.at(id1);
                if(std::find(edge_list1.begin(), edge_list1.end(), Node<W>{id2, weight}) != edge_list1.end())
                {
                    edge_list1.erase(std::remove(edge_list1.begin(), edge_list1.end(), Node<W>{id2, weight}), edge_list1.end());
                }

                std::vector<Node<W>> &edge_list2 = this->_ADJACENCY_LIST_.at(id2);
                if(std::find(edge_list2.begin(), edge_list2.end(), Node<W>{id1, weight}) != edge_list2.end())
                {
                    edge_list2.erase(std::remove(edge_list2.begin(), edge_list2.end(), Node<W>{id1, weight}), edge_list2.end());
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

                    std::vector<Node<W>> &edge_list1 = this->_ADJACENCY_LIST_.at(id1);
                    if(std::find(edge_list1.begin(), edge_list1.end(), Node<W>{id2, weight}) != edge_list1.end())
                    {
                        edge_list1.erase(std::remove(edge_list1.begin(), edge_list1.end(), Node<W>{id2, weight}), edge_list1.end());
                    }

                    std::vector<Node<W>> &edge_list2 = this->_ADJACENCY_LIST_.at(id2);
                    if(std::find(edge_list2.begin(), edge_list2.end(), Node<W>{id1, weight}) != edge_list2.end())
                    {
                        edge_list2.erase(std::remove(edge_list2.begin(), edge_list2.end(), Node<W>{id1, weight}), edge_list2.end());
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
    bool UndirectedGraph<T, W>::isCyclicUtil(unsigned int start, std::unordered_set<unsigned int> &Visited, unsigned int parent) const
    {
        Visited.insert(start);

        for(const Node<W> &node : this->_ADJACENCY_LIST_.at(start))
        {
            if(Visited.find(node.vertex) == Visited.end())
            {
                if(isCyclicUtil(node.vertex, Visited, start))
                    return true;
            }
            else if(node.vertex != parent)
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
}

#include "shortestPath.hpp"

#endif