#ifndef NODE_ITERATOR_H
#define NODE_ITERATOR_H

#include "UndirectedGraph.hpp"

namespace Graph
{
    template<typename T>
    class UndirectedGraph<T>::node_iterator
    {
        friend class UndirectedGraph<T>;

        private:
            typename std::unordered_map<unsigned int, std::vector<Node>>::iterator _it_;
            std::unordered_map<unsigned int, T> &_id_to_node_ptr_;
            node_iterator(const typename std::unordered_map<unsigned int, std::vector<Node>>::iterator &, std::unordered_map<unsigned int, T> &);

        public:
            /*
             * SPECIAL MEMBER FUNCTIONS
             */
            // Default constructor.
            node_iterator();
            // Destructor.
            ~node_iterator();

            // Copy constructor.
            node_iterator(const node_iterator &);
            // Copy assignment operator.
            node_iterator& operator=(const node_iterator &);

            // Move constructor.
            node_iterator(node_iterator &&) noexcept;
            // Move assignment operator.
            node_iterator& operator=(node_iterator &&) noexcept;


            /*
             * OVERLOADED OPERATORS
             */
            // Overloaded equality operator.
            bool operator==(const node_iterator &) const;
            // Overloaded inequality operator.
            bool operator!=(const node_iterator &) const;
            // Overloaded pre-increment operator.
            node_iterator& operator++();
            // Overloaded post-increment operator.
            node_iterator operator++(int);

            // Overloaded dereference operator.
            T& operator*() const;
            // Overloaded member selection operator.
            T* operator->() const;
    };

    template<typename T>
    UndirectedGraph<T>::node_iterator::node_iterator()
    {
    }

    template<typename T>
    UndirectedGraph<T>::node_iterator::~node_iterator()
    {
    }

    template<typename T>
    UndirectedGraph<T>::node_iterator::node_iterator(const node_iterator &rhs)
        : _it_ ( rhs._it_ )
        , _id_to_node_ptr_ ( rhs._id_to_node_ptr_ )
    {
    }

    template<typename T>
    typename UndirectedGraph<T>::node_iterator& UndirectedGraph<T>::node_iterator::operator=(const node_iterator &rhs)
    {
        _it_ = rhs._it_;
        _id_to_node_ptr_ = rhs._id_to_node_ptr_;
        return *this;
    }

    template<typename T>
    UndirectedGraph<T>::node_iterator::node_iterator(node_iterator &&rhs) noexcept
        : _it_ ( std::move(rhs._it_) )
        , _id_to_node_ptr_ ( rhs._id_to_node_ptr_ )
    {
    }

    template<typename T>
    typename UndirectedGraph<T>::node_iterator& UndirectedGraph<T>::node_iterator::operator=(node_iterator &&rhs) noexcept
    {
        _it_ = std::move(rhs._it_);
        _id_to_node_ptr_ = rhs._id_to_node_ptr_;
        return *this;
    }

    // Private constructor. Only move version is sufficienct.
    template<typename T>
    UndirectedGraph<T>::node_iterator::node_iterator(const typename std::unordered_map<unsigned int, std::vector<Node>>::iterator &rhs, std::unordered_map<unsigned int, T> &_id_to_node_)
        : _it_ ( std::move(rhs) )
        , _id_to_node_ptr_ ( _id_to_node_ )
    {
    }

    template<typename T>
    bool UndirectedGraph<T>::node_iterator::operator==(const node_iterator &rhs) const
    {
        return _it_ == rhs._it_;
    }

    template<typename T>
    bool UndirectedGraph<T>::node_iterator::operator!=(const node_iterator &rhs) const
    {
        return _it_ != rhs._it_;
    }

    template<typename T>
    typename UndirectedGraph<T>::node_iterator& UndirectedGraph<T>::node_iterator::operator++()
    {
        ++_it_;
        return *this;
    }

    template<typename T>
    typename UndirectedGraph<T>::node_iterator UndirectedGraph<T>::node_iterator::operator++(int)
    {
        node_iterator old = *this;
        ++_it_;
        return old;
    }

    template<typename T>
    T& UndirectedGraph<T>::node_iterator::operator*() const
    {
        return _id_to_node_ptr_.at(_it_->first);
    }

    template<typename T>
    T* UndirectedGraph<T>::node_iterator::operator->() const
    {
        return &(_id_to_node_ptr_.at(_it_->first));
    }
}

#endif