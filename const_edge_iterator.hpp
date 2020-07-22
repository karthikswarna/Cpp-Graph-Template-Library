#ifndef CONST_EDGE_ITERATOR_H
#define CONST_EDGE_ITERATOR_H

#include "edge_iterator.hpp"

namespace Graph
{
    template<typename T, typename W>
    class UndirectedGraph<T, W>::const_edge_iterator
    {
        friend class UndirectedGraph<T, W>;

        private:
            typename std::unordered_map<unsigned int, std::vector<Node<W>>>::const_iterator _it_;
            typename std::vector<Node<W>>::const_iterator _it2_;
            std::unordered_map<unsigned int, T> const* _id_to_node_ptr_;                                                    // Pointer to const map.
            typename std::unordered_map<unsigned int, std::vector<Node<W>>>::const_iterator _last_it_;

            const_edge_iterator(const typename std::unordered_map<unsigned int, std::vector<Node<W>>>::const_iterator &,    // Gives iterator to the adjacency list(current iterator).
                                const typename std::unordered_map<unsigned int, std::vector<Node<W>>>::const_iterator &,    // Gives iterator to the last non-empty mapping in the container(used in bound checking, this is constant for a Graph if not new edges are added).
                                std::unordered_map<unsigned int, T> const*,                                                 // Reference to the _id_to_node_ in the Graph.
                                const typename std::vector<Node<W>>::const_iterator & = (std::vector<Node<W>>{}).begin());  // Gives iterator to the vector in the current mapping.

        public:
            /*
             *  SPECIAL MEMBER FUNCTIONS
             */
            // Default constructor.
            const_edge_iterator();
            // Destructor.
            ~const_edge_iterator();

            // Copy constructor.
            const_edge_iterator(const const_edge_iterator &);
            // Copy assignment operator.
            const_edge_iterator& operator=(const const_edge_iterator &);

            // Move constructor.
            const_edge_iterator(const_edge_iterator &&) noexcept;
            // Move assignment operator.
            const_edge_iterator& operator=(const_edge_iterator &&) noexcept;


             /*
             *  ADDITIONAL CONSTRUCTORS
             */
            // Copy constructor with edge_iterator.
            const_edge_iterator(const typename UndirectedGraph<T, W>::edge_iterator &);
            // Move constructor with edge_iterator.
            const_edge_iterator(typename UndirectedGraph<T, W>::edge_iterator &&) noexcept;


            /*
             *  OVERLOADED OPERATORS
             */
            // Overloaded equality operator.
            bool operator==(const const_edge_iterator &) const;
            // Overloaded inequality operator.
            bool operator!=(const const_edge_iterator &) const;
            // Overloaded pre-increment operator.
            const_edge_iterator& operator++();
            // Overloaded post-increment operator.
            const_edge_iterator operator++(int);

            // Overloaded dereference operator.
            const std::pair<const T&, const T&> operator*() const;
            // Overloaded member selection operator.
            const std::pair<const T*, const T*> operator->() const;

            /*
             *  MEMBER FUNCTIONS
             */
            // Function used to GET the weight of an edge pointed by the iterator.
            W getWeight() const;
    };

    template<typename T, typename W>
    UndirectedGraph<T, W>::const_edge_iterator::const_edge_iterator()
    {
    }

    template<typename T, typename W>
    UndirectedGraph<T, W>::const_edge_iterator::~const_edge_iterator()
    {
    }

    template<typename T, typename W>
    UndirectedGraph<T, W>::const_edge_iterator::const_edge_iterator(const const_edge_iterator &rhs)
        : _it_ ( rhs._it_ )
        , _it2_ ( rhs._it2_ )
        , _last_it_ ( rhs._last_it_ )
        , _id_to_node_ptr_ ( rhs._id_to_node_ptr_ )
    {
    }
    
    template<typename T, typename W>
    typename UndirectedGraph<T, W>::const_edge_iterator& UndirectedGraph<T, W>::const_edge_iterator::operator=(const const_edge_iterator &rhs)
    {
        _it_ = rhs._it_;
        _it2_ = rhs._it2_;
        _last_it_ = rhs._last_it_;
        _id_to_node_ptr_ = rhs._id_to_node_ptr_;
        return *this;
    }

    template<typename T, typename W>
    UndirectedGraph<T, W>::const_edge_iterator::const_edge_iterator(const_edge_iterator &&rhs) noexcept
        : _it_ ( std::move(rhs._it_) )                          // Member-wise move phase.
        , _it2_ ( std::move(rhs._it2_) )
        , _last_it_ ( std::move(rhs._last_it_) )
        , _id_to_node_ptr_ ( std::move(rhs._id_to_node_ptr_) )
    {
        rhs._id_to_node_ptr_ = nullptr;                         // Reset phase.
    }
    
    template<typename T, typename W>
    typename UndirectedGraph<T, W>::const_edge_iterator& UndirectedGraph<T, W>::const_edge_iterator::operator=(const_edge_iterator &&rhs) noexcept
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

    template<typename T, typename W>
    UndirectedGraph<T, W>::const_edge_iterator::const_edge_iterator(const typename UndirectedGraph<T, W>::edge_iterator &rhs)
        : _it_ ( rhs._it_ )
        , _it2_ ( rhs._it2_ )
        , _last_it_ ( rhs._last_it_ )
        , _id_to_node_ptr_ ( rhs._id_to_node_ptr_ )
    {
    }

    template<typename T, typename W>
    UndirectedGraph<T, W>::const_edge_iterator::const_edge_iterator(typename UndirectedGraph<T, W>::edge_iterator &&rhs) noexcept
        : _it_ ( std::move(rhs._it_) )                          // Member-wise move phase.
        , _it2_ ( std::move(rhs._it2_) )
        , _last_it_ ( std::move(rhs._last_it_) )
        , _id_to_node_ptr_ ( std::move(rhs._id_to_node_ptr_) )
    {
        rhs._id_to_node_ptr_ = nullptr;                         // Reset phase.
    }

    // Private constructor. Only move version is sufficienct.
    template<typename T, typename W>
    UndirectedGraph<T, W>::const_edge_iterator::const_edge_iterator(const typename std::unordered_map<unsigned int, std::vector<Node<W>>>::const_iterator &rhs, const typename std::unordered_map<unsigned int, std::vector<Node<W>>>::const_iterator &rhs3, std::unordered_map<unsigned int, T> const* _id_to_node_, const typename std::vector<Node<W>>::const_iterator &rhs2)
        : _it_ ( std::move(rhs) )                       // Member-wise move phase.
        , _it2_ ( std::move(rhs2) )
        , _last_it_ ( std::move(rhs3) )
        , _id_to_node_ptr_ ( std::move(_id_to_node_) )
    {
        _id_to_node_ = nullptr;                         // Reset phase.
    }

    template<typename T, typename W>
    bool UndirectedGraph<T, W>::const_edge_iterator::operator==(const const_edge_iterator &rhs) const
    {
        return _it2_ == rhs._it2_;
    }

    template<typename T, typename W>
    bool UndirectedGraph<T, W>::const_edge_iterator::operator!=(const const_edge_iterator &rhs) const
    {
        return _it2_ != rhs._it2_;
    }

    template<typename T, typename W>
    typename UndirectedGraph<T, W>::const_edge_iterator& UndirectedGraph<T, W>::const_edge_iterator::operator++()
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
    typename UndirectedGraph<T, W>::const_edge_iterator UndirectedGraph<T, W>::const_edge_iterator::operator++(int)
    {
        const_edge_iterator old = *this;

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
    const std::pair<const T&, const T&> UndirectedGraph<T, W>::const_edge_iterator::operator*() const
    {
        return std::make_pair( _id_to_node_ptr_->at(_it_->first), _id_to_node_ptr_->at(_it2_->vertex) );
    }

    template<typename T, typename W>
    const std::pair<const T*, const T*> UndirectedGraph<T, W>::const_edge_iterator::operator->() const
    {
        return std::make_pair( &(_id_to_node_ptr_->at(_it_->first)), &(_id_to_node_ptr_->at(_it2_->vertex)) );
    }

    template<typename T, typename W>
    W UndirectedGraph<T, W>::const_edge_iterator::getWeight() const
    {
        return _it2_->weight;
    }
}

#endif