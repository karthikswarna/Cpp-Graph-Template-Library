#ifndef CONST_NODE_ITERATOR_H
#define CONST_NODE_ITERATOR_H

#include "node_iterator.hpp"

namespace Graph
{
    template<typename T>
    class UndirectedGraph<T>::const_node_iterator
    {
        friend class UndirectedGraph<T>;

        private:
            std::unordered_map<unsigned int, std::vector<unsigned int>>::const_iterator _it_;
            const std::unordered_map<unsigned int, T> &_id_to_node_ptr_;

            const_node_iterator(const std::unordered_map<unsigned int, std::vector<unsigned int>>::const_iterator &, const std::unordered_map<unsigned int, T> &);

        public:
            /*
             * SPECIAL MEMBER FUNCTIONS
             */
            // Default constructor.
            const_node_iterator();
            // Destructor.
            ~const_node_iterator();

            // Copy Constructor.
            const_node_iterator(const const_node_iterator &);
            // Copy assignment operator.
            const_node_iterator& operator=(const const_node_iterator &);

            // Move constructor.
            const_node_iterator(const_node_iterator &&) noexcept;
            // Move assignment operator.
            const_node_iterator& operator=(const_node_iterator &&) noexcept;


            /*
             * ADDITIONAL CONSTRUCTORS
             */
            // Copy constructor with node_iterator.
            const_node_iterator(const typename UndirectedGraph<T>::node_iterator &);
            // Move constructor with node_iterator.
            const_node_iterator(typename UndirectedGraph<T>::node_iterator &&) noexcept;
            
            
            /*
             * OVERLOADED OPERATORS
             */
            // Overloaded equality operator.
            bool operator==(const const_node_iterator &) const;
            // Overloaded inequality operator.
            bool operator!=(const const_node_iterator &) const;
            // Overloaded pre-increment operator.
            const_node_iterator& operator++();
            // Overloaded post-increment operator.
            const_node_iterator operator++(int);

            // Overloaded dereference operator.
            const T& operator*() const;
            // Overloaded member selection operator.
            const T* operator->() const;
    };

    template<typename T>
    UndirectedGraph<T>::const_node_iterator::const_node_iterator()
    {
    }

    template<typename T>
    UndirectedGraph<T>::const_node_iterator::~const_node_iterator()
    {
    }

    template<typename T>
    UndirectedGraph<T>::const_node_iterator::const_node_iterator(const const_node_iterator &rhs)
        : _it_ ( rhs._it_ )
        , _id_to_node_ptr_ ( rhs._id_to_node_ptr_ )
    {
    }

    template<typename T>
    typename UndirectedGraph<T>::const_node_iterator& UndirectedGraph<T>::const_node_iterator::operator=(const const_node_iterator &rhs)
    {
        _it_ = rhs._it_;
        _id_to_node_ptr_ = rhs._id_to_node_ptr_;
        return *this;
    }
    
    template<typename T>
    UndirectedGraph<T>::const_node_iterator::const_node_iterator(const_node_iterator &&rhs) noexcept
        : _it_ ( std::move(rhs._it_) )
        , _id_to_node_ptr_ ( rhs._id_to_node_ptr_ )
    {
    }

    template<typename T>
    typename UndirectedGraph<T>::const_node_iterator& UndirectedGraph<T>::const_node_iterator::operator=(const_node_iterator &&rhs) noexcept
    {
        _it_ = std::move(rhs._it_);
        _id_to_node_ptr_ = rhs._id_to_node_ptr_;
        return *this;
    }

    template<typename T>
    UndirectedGraph<T>::const_node_iterator::const_node_iterator(const typename UndirectedGraph<T>::node_iterator &rhs)
        : _it_ ( rhs._it_ )
        , _id_to_node_ptr_ ( rhs._id_to_node_ptr_ )
    {
    }

    template<typename T>
    UndirectedGraph<T>::const_node_iterator::const_node_iterator(typename UndirectedGraph<T>::node_iterator &&rhs) noexcept
        : _it_ ( std::move(rhs._it_) )
        , _id_to_node_ptr_ ( rhs._id_to_node_ptr_ )
    {
    }

    // Private constructor. Only move version is sufficienct.
    template<typename T>
    UndirectedGraph<T>::const_node_iterator::const_node_iterator(const std::unordered_map<unsigned int, std::vector<unsigned int>>::const_iterator &rhs, const std::unordered_map<unsigned int, T> &_id_to_node_)
        : _it_ ( std::move(rhs) )
        , _id_to_node_ptr_ ( _id_to_node_ )
    {
    }

    template<typename T>
    bool UndirectedGraph<T>::const_node_iterator::operator==(const const_node_iterator &rhs) const
    {
        return _it_ == rhs._it_;
    }
    
    template<typename T>
    bool UndirectedGraph<T>::const_node_iterator::operator!=(const const_node_iterator &rhs) const
    {
        return _it_ != rhs._it_;
    }

    template<typename T>
    typename UndirectedGraph<T>::const_node_iterator& UndirectedGraph<T>::const_node_iterator::operator++()
    {
        ++_it_;
        return *this;
    }

    template<typename T>
    typename UndirectedGraph<T>::const_node_iterator UndirectedGraph<T>::const_node_iterator::operator++(int)
    {
        const_node_iterator old = *this;
        ++_it_;
        return old;
    }

    template<typename T>
    const T& UndirectedGraph<T>::const_node_iterator::operator*() const
    {
        return _id_to_node_ptr_.at(_it_->first);
    }

    template<typename T>
    const T* UndirectedGraph<T>::const_node_iterator::operator->() const
    {
        return &(_id_to_node_ptr_.at(_it_->first));
    }
}

#endif