#ifndef CONST_EDGE_ITERATOR_H
#define CONST_EDGE_ITERATOR_H

#include "edge_iterator.hpp"

namespace Graph
{
    template<typename T>
    class UndirectedGraph<T>::const_edge_iterator
    {
        friend class UndirectedGraph<T>;

        private:
            std::unordered_map<unsigned int, std::vector<unsigned int>>::iterator _it_;
            std::vector<unsigned int>::iterator _it2_;
            const std::unordered_map<unsigned int, T> &_id_to_node_ptr_;
            const std::unordered_map<unsigned int, std::vector<unsigned int>>::iterator _last_it_;

            const_edge_iterator(const std::unordered_map<unsigned int, std::vector<unsigned int>>::iterator &,    // Gives iterator to the adjacency list(current iterator).
                                const std::unordered_map<unsigned int, std::vector<unsigned int>>::iterator &,    // Gives iterator to the last non-empty mapping in the container(used in bound checking, this is constant for a Graph if not new edges are added).
                                const std::unordered_map<unsigned int, T> &,                                            // Reference to the _id_to_node_ in the Graph.
                                const std::vector<unsigned int>::iterator & = V.begin());                         // Gives iterator to the vector in the current mapping.

        public:
            /*
             * SPECIAL MEMBER FUNCTIONS
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
             * ADDITIONAL CONSTRUCTORS
             */
            // Copy constructor with edge_iterator.
            const_edge_iterator(const typename UndirectedGraph<T>::edge_iterator &);
            // Move constructor with edge_iterator.
            const_edge_iterator(typename UndirectedGraph<T>::edge_iterator &&) noexcept;


            /*
             * OVERLOADED OPERATORS
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
    };

    template<typename T>
    UndirectedGraph<T>::const_edge_iterator::const_edge_iterator()
    {
    }

    template<typename T>
    UndirectedGraph<T>::const_edge_iterator::~const_edge_iterator()
    {
    }

    template<typename T>
    UndirectedGraph<T>::const_edge_iterator::const_edge_iterator(const const_edge_iterator &rhs)
        : _it_ ( rhs._it_ )
        , _it2_ ( rhs._it2_ )
        , _last_it_ ( rhs._last_it_ )
        , _id_to_node_ptr_ ( rhs._id_to_node_ptr_ )
    {
    }
    
    template<typename T>
    typename UndirectedGraph<T>::const_edge_iterator& UndirectedGraph<T>::const_edge_iterator::operator=(const const_edge_iterator &rhs)
    {
        _it_ = rhs._it_;
        _it2_ = rhs._it2_;
        _last_it_ = rhs._last_it_;
        _id_to_node_ptr_ = rhs._id_to_node_ptr_;
        return *this;
    }

    template<typename T>
    UndirectedGraph<T>::const_edge_iterator::const_edge_iterator(const_edge_iterator &&rhs) noexcept
        : _it_ ( std::move(rhs._it_) )
        , _it2_ ( std::move(rhs._it2_) )
        , _last_it_ ( std::move(rhs._last_it_) )
        , _id_to_node_ptr_ ( rhs._id_to_node_ptr_ )
    {
    }
    
    template<typename T>
    typename UndirectedGraph<T>::const_edge_iterator& UndirectedGraph<T>::const_edge_iterator::operator=(const_edge_iterator &&rhs) noexcept
    {
        _it_ = std::move(rhs._it_);
        _it2_ = std::move(rhs._it2_);
        _last_it_ = std::move(rhs._last_it_);
        _id_to_node_ptr_ = rhs._id_to_node_ptr_;
        return *this;
    }

    template<typename T>
    UndirectedGraph<T>::const_edge_iterator::const_edge_iterator(const typename UndirectedGraph<T>::edge_iterator &rhs)
        : _it_ ( rhs._it_ )
        , _it2_ ( rhs._it2_ )
        , _last_it_ ( rhs._last_it_ )
        , _id_to_node_ptr_ ( rhs._id_to_node_ptr_ )
    {
    }

    template<typename T>
    UndirectedGraph<T>::const_edge_iterator::const_edge_iterator(typename UndirectedGraph<T>::edge_iterator &&rhs) noexcept
        : _it_ ( std::move(rhs._it_) )
        , _it2_ ( std::move(rhs._it2_) )
        , _last_it_ ( std::move(rhs._last_it_) )
        , _id_to_node_ptr_ ( rhs._id_to_node_ptr_ )
    {
    }

    // Private constructor. Only move version is sufficienct.
    template<typename T>
    UndirectedGraph<T>::const_edge_iterator::const_edge_iterator(const std::unordered_map<unsigned int, std::vector<unsigned int>>::iterator &rhs, const std::unordered_map<unsigned int, std::vector<unsigned int>>::iterator &rhs3, const std::unordered_map<unsigned int, T> &_id_to_node_, const std::vector<unsigned int>::iterator &rhs2)
        : _it_ ( std::move(rhs) )
        , _it2_ ( std::move(rhs2) )
        , _last_it_ ( std::move(rhs3) )
        , _id_to_node_ptr_ ( _id_to_node_ )
    {
    }

    template<typename T>
    bool UndirectedGraph<T>::const_edge_iterator::operator==(const const_edge_iterator &rhs) const
    {
        return _it2_ == rhs._it2_;
    }

    template<typename T>
    bool UndirectedGraph<T>::const_edge_iterator::operator!=(const const_edge_iterator &rhs) const
    {
        return _it2_ != rhs._it2_;
    }

    template<typename T>
    typename UndirectedGraph<T>::const_edge_iterator& UndirectedGraph<T>::const_edge_iterator::operator++()
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

    template<typename T>
    typename UndirectedGraph<T>::const_edge_iterator UndirectedGraph<T>::const_edge_iterator::operator++(int)
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

    template<typename T>
    const std::pair<const T&, const T&> UndirectedGraph<T>::const_edge_iterator::operator*() const
    {
        return std::pair<T&, T&>( _id_to_node_ptr_.at(_it_->first), _id_to_node_ptr_.at(*_it2_) );
    }

    template<typename T>
    const std::pair<const T*, const T*> UndirectedGraph<T>::const_edge_iterator::operator->() const
    {
        return std::pair<T&, T&>( &(_id_to_node_ptr_.at(_it_->first)), &(_id_to_node_ptr_.at(*_it2_)) );
    }
}

#endif