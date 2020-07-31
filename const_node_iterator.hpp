#ifndef CONST_NODE_ITERATOR_H
#define CONST_NODE_ITERATOR_H

#include "node_iterator.hpp"

namespace graph
{
    template<typename T, typename W>
    class undirected_graph<T, W>::const_node_iterator
    {
        friend class undirected_graph<T, W>;

        private:
            typename std::unordered_map<unsigned int, std::vector<Node<W>>>::const_iterator _it_;
            std::unordered_map<unsigned int, T> const* _id_to_node_ptr_;        // Pointer to a constant map.

            const_node_iterator(const typename std::unordered_map<unsigned int, std::vector<Node<W>>>::const_iterator &, std::unordered_map<unsigned int, T> const*);

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
            const_node_iterator(const typename undirected_graph<T, W>::node_iterator &);
            // Move constructor with node_iterator.
            const_node_iterator(typename undirected_graph<T, W>::node_iterator &&) noexcept;
            
            
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

    template<typename T, typename W>
    undirected_graph<T, W>::const_node_iterator::const_node_iterator()
    {
    }

    template<typename T, typename W>
    undirected_graph<T, W>::const_node_iterator::~const_node_iterator()
    {
    }

    template<typename T, typename W>
    undirected_graph<T, W>::const_node_iterator::const_node_iterator(const const_node_iterator &rhs)
        : _it_ ( rhs._it_ )
        , _id_to_node_ptr_ ( rhs._id_to_node_ptr_ )
    {
    }

    template<typename T, typename W>
    typename undirected_graph<T, W>::const_node_iterator& undirected_graph<T, W>::const_node_iterator::operator=(const const_node_iterator &rhs)
    {
        _it_ = rhs._it_;
        _id_to_node_ptr_ = rhs._id_to_node_ptr_;
        return *this;
    }
    
    template<typename T, typename W>
    undirected_graph<T, W>::const_node_iterator::const_node_iterator(const_node_iterator &&rhs) noexcept
        : _it_ ( std::move(rhs._it_) )                          // Member-wise move phase.
        , _id_to_node_ptr_ ( std::move(rhs._id_to_node_ptr_) )
    {
        rhs._id_to_node_ptr_ = nullptr;                         // Reset phase.
    }

    template<typename T, typename W>
    typename undirected_graph<T, W>::const_node_iterator& undirected_graph<T, W>::const_node_iterator::operator=(const_node_iterator &&rhs) noexcept
    {
        // Clean-up phase: Need not delete _id_to_node_ptr_ before moving, because it represents only a relationship(not ownership).
        
        // Member-wise move phase.
        _it_ = std::move(rhs._it_);
        _id_to_node_ptr_ = std::move(rhs._id_to_node_ptr_);
        
        // Reset phase.
        rhs._id_to_node_ptr_ = nullptr;
        return *this;
    }

    template<typename T, typename W>
    undirected_graph<T, W>::const_node_iterator::const_node_iterator(const typename undirected_graph<T, W>::node_iterator &rhs)
        : _it_ ( rhs._it_ )
        , _id_to_node_ptr_ ( rhs._id_to_node_ptr_ )
    {
    }

    template<typename T, typename W>
    undirected_graph<T, W>::const_node_iterator::const_node_iterator(typename undirected_graph<T, W>::node_iterator &&rhs) noexcept
        : _it_ ( std::move(rhs._it_) )
        , _id_to_node_ptr_ ( std::move(rhs._id_to_node_ptr_) )
    {
        rhs._id_to_node_ptr_ = nullptr;
    }

    // Private constructor. Only move version is sufficienct.
    template<typename T, typename W>
    undirected_graph<T, W>::const_node_iterator::const_node_iterator(const typename std::unordered_map<unsigned int, std::vector<Node<W>>>::const_iterator &rhs, std::unordered_map<unsigned int, T> const* _id_to_node_)
        : _it_ ( std::move(rhs) )                       // Member-wise move phase.
        , _id_to_node_ptr_ ( std::move(_id_to_node_) )
    {
        _id_to_node_ = nullptr;                         // Reset phase.
    }

    template<typename T, typename W>
    bool undirected_graph<T, W>::const_node_iterator::operator==(const const_node_iterator &rhs) const
    {
        return _it_ == rhs._it_;
    }
    
    template<typename T, typename W>
    bool undirected_graph<T, W>::const_node_iterator::operator!=(const const_node_iterator &rhs) const
    {
        return _it_ != rhs._it_;
    }

    template<typename T, typename W>
    typename undirected_graph<T, W>::const_node_iterator& undirected_graph<T, W>::const_node_iterator::operator++()
    {
        ++_it_;
        return *this;
    }

    template<typename T, typename W>
    typename undirected_graph<T, W>::const_node_iterator undirected_graph<T, W>::const_node_iterator::operator++(int)
    {
        const_node_iterator old = *this;
        ++_it_;
        return old;
    }

    template<typename T, typename W>
    const T& undirected_graph<T, W>::const_node_iterator::operator*() const
    {
        return _id_to_node_ptr_->at(_it_->first);
    }

    template<typename T, typename W>
    const T* undirected_graph<T, W>::const_node_iterator::operator->() const
    {
        return &(_id_to_node_ptr_->at(_it_->first));
    }
}

#endif