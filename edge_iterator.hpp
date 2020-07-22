#ifndef EDGE_ITERATOR_H
#define EDGE_ITERATOR_H

#include "UndirectedGraph.hpp"

namespace Graph
{
    template<typename T, typename W>
    class UndirectedGraph<T, W>::edge_iterator
    {
        friend class UndirectedGraph<T, W>;

        private:
            typename std::unordered_map<unsigned int, std::vector<Node<W>>>::iterator _it_;
            typename std::vector<Node<W>>::iterator _it2_;
            std::unordered_map<unsigned int, T> *_id_to_node_ptr_;
            typename std::unordered_map<unsigned int, std::vector<Node<W>>>::iterator _last_it_;

            edge_iterator(const typename std::unordered_map<unsigned int, std::vector<Node<W>>>::iterator &,    // Gives iterator to the adjacency list(current iterator).
                          const typename std::unordered_map<unsigned int, std::vector<Node<W>>>::iterator &,    // Gives iterator to the last non-empty mapping in the container(used in bound checking, this is constant for a Graph if not new edges are added).
                          std::unordered_map<unsigned int, T> *,                                                // Reference to the _id_to_node_ in the Graph.
                          const typename std::vector<Node<W>>::iterator & = (std::vector<Node<W>>{}).begin());  // Gives iterator to the vector in the current mapping.

        public:
            /*
             *  SPECIAL MEMBER FUNCTIONS
             */
            // Default constructor.
            edge_iterator();
            // Destructor.
            ~edge_iterator();

            // Copy constructor.
            edge_iterator(const edge_iterator &);
            // Copy assignment operator.
            edge_iterator& operator=(const edge_iterator &);

            // Move constructor.
            edge_iterator(edge_iterator &&) noexcept;
            // Move assignment operator.
            edge_iterator& operator=(edge_iterator &&) noexcept;


            /*
             *  OVERLOADED OPERATORS
             */
            // Overloaded equality operator.
            bool operator==(const edge_iterator &) const;
            // Overloaded inequality operator.
            bool operator!=(const edge_iterator &) const;
            // Overloaded pre-increment operator.
            edge_iterator& operator++();
            // Overloaded post-increment operator.
            edge_iterator operator++(int);

            // Overloaded dereference operator.
            std::pair<const T&, const T&> operator*() const;
            // Overloaded member selection operator.
            std::pair<const T*, const T*> operator->() const;

            /*
             *  MEMBER FUNCTIONS
             */
            // Function used to SET the weight of an edge pointed by the iterator.
            void setWeight(W);
            // Function used to GET the weight of an edge pointed by the iterator.
            W getWeight() const;
    };


    template<typename T, typename W>
    UndirectedGraph<T, W>::edge_iterator::edge_iterator()
    {
    }

    template<typename T, typename W>
    UndirectedGraph<T, W>::edge_iterator::~edge_iterator()
    {
    }

    template<typename T, typename W>
    UndirectedGraph<T, W>::edge_iterator::edge_iterator(const edge_iterator &rhs)
        : _it_ ( rhs._it_ )
        , _it2_ ( rhs._it2_ )
        , _last_it_ ( rhs._last_it_ )
        , _id_to_node_ptr_ ( rhs._id_to_node_ptr_ )
    {
    }
    
    template<typename T, typename W>
    typename UndirectedGraph<T, W>::edge_iterator& UndirectedGraph<T, W>::edge_iterator::operator=(const edge_iterator &rhs)
    {
        _it_ = rhs._it_;
        _it2_ = rhs._it2_;
        _last_it_ = rhs._last_it_;
        _id_to_node_ptr_ = rhs._id_to_node_ptr_;
        return *this;
    }

    template<typename T, typename W>
    UndirectedGraph<T, W>::edge_iterator::edge_iterator(edge_iterator &&rhs) noexcept
        : _it_ ( std::move(rhs._it_) )                          // Member-wise move phase.
        , _it2_ ( std::move(rhs._it2_) )
        , _last_it_ ( std::move(rhs._last_it_) )
        , _id_to_node_ptr_ ( std::move(rhs._id_to_node_ptr_) )
    {
        rhs._id_to_node_ptr_ = nullptr;                         // Reset phase.
    }
    
    template<typename T, typename W>
    typename UndirectedGraph<T, W>::edge_iterator& UndirectedGraph<T, W>::edge_iterator::operator=(edge_iterator &&rhs) noexcept
    {
        // Clean-up phase is not required(as the pointer is not used for ownership of memory).
    
        // Member-wise move phase.
        _it_ = std::move(rhs._it_);
        _it2_ = std::move(rhs._it2_);
        _last_it_ = std::move(rhs._last_it_);
        _id_to_node_ptr_ = std::move(rhs._id_to_node_ptr_);

        // Reset phase.
        rhs._id_to_node_ptr_ = nullptr;

        return *this;
    }

    // Private constructor. Only move version is sufficienct.
    template<typename T, typename W>
    UndirectedGraph<T, W>::edge_iterator::edge_iterator(const typename std::unordered_map<unsigned int, std::vector<Node<W>>>::iterator &rhs, const typename std::unordered_map<unsigned int, std::vector<Node<W>>>::iterator &rhs3, std::unordered_map<unsigned int, T> *_id_to_node_, const typename std::vector<Node<W>>::iterator &rhs2)
        : _it_ ( std::move(rhs) )                       // Member-wise move phase.
        , _it2_ ( std::move(rhs2) )
        , _last_it_ ( std::move(rhs3) )
        , _id_to_node_ptr_ ( std::move(_id_to_node_) )
    {
        _id_to_node_ = nullptr;                         // Reset phase.
    }

    template<typename T, typename W>
    bool UndirectedGraph<T, W>::edge_iterator::operator==(const edge_iterator &rhs) const
    {
        return _it2_ == rhs._it2_;
    }

    template<typename T, typename W>
    bool UndirectedGraph<T, W>::edge_iterator::operator!=(const edge_iterator &rhs) const
    {
        return _it2_ != rhs._it2_;
    }

    template<typename T, typename W>
    typename UndirectedGraph<T, W>::edge_iterator& UndirectedGraph<T, W>::edge_iterator::operator++()
    {
        // If it is not last non-empty mapping, but last element in current mapping, then goto next mapping.
        if(_it2_ == _it_->second.end() - 1 && _it_ != _last_it_)
        {
            ++_it_;
            while(_it_->second.empty())
                ++_it_;

            _it2_ = _it_->second.begin();
        }
        else
            ++_it2_;

        return *this;
    }

    template<typename T, typename W>
    typename UndirectedGraph<T, W>::edge_iterator UndirectedGraph<T, W>::edge_iterator::operator++(int)
    {
        edge_iterator old = *this;

        // If it is not last non-empty mapping, but last element in current mapping, then goto next mapping.
        if(_it2_ == _it_->second.end() - 1 && _it_ != _last_it_)
        {
            ++_it_;
            while(_it_->second.empty())
                ++_it_;

            _it2_ = _it_->second.begin();
        }
        else
            ++_it2_;

        return old;
    }

    template<typename T, typename W>
    std::pair<const T&, const T&> UndirectedGraph<T, W>::edge_iterator::operator*() const
    {
        return std::pair<T&, T&>( _id_to_node_ptr_->at(_it_->first), _id_to_node_ptr_->at(_it2_->vertex) );
    }

    template<typename T, typename W>
    std::pair<const T*, const T*> UndirectedGraph<T, W>::edge_iterator::operator->() const
    {
        return std::pair<T*, T*>( &(_id_to_node_ptr_->at(_it_->first)), &(_id_to_node_ptr_->at(_it2_->vertex)) );
    }

    template<typename T, typename W>
    void UndirectedGraph<T, W>::edge_iterator::setWeight(W weight)
    {
        _it2_->weight = weight;
    }

    template<typename T, typename W>
    W UndirectedGraph<T, W>::edge_iterator::getWeight() const
    {
        return _it2_->weight;
    }
}

#endif