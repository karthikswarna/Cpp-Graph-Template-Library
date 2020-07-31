#ifndef NODE_ITERATOR_H
#define NODE_ITERATOR_H

#include "undirected_graph.hpp"

namespace graph
{
    template<typename T, typename W>
    class undirected_graph<T, W>::node_iterator
    {
        friend class undirected_graph<T, W>;

        private:
            typename std::unordered_map<unsigned int, std::vector<Node<W>>>::iterator _it_;
            std::unordered_map<unsigned int, T> *_id_to_node_ptr_;
            std::unordered_map<T, unsigned int> *_node_to_id_ptr_;

            node_iterator(const typename std::unordered_map<unsigned int, std::vector<Node<W>>>::iterator &, std::unordered_map<unsigned int, T> *, std::unordered_map<T, unsigned int> *);

        public:
            /*
             *  SPECIAL MEMBER FUNCTIONS
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
             *  OVERLOADED OPERATORS
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
            const T& operator*() const;
            // Overloaded member selection operator.
            const T* operator->() const;


            /*
             *  MEMBER FUNCTIONS
             */
            // Function to change the value of the node.
            void setNode(T);
    };

    template<typename T, typename W>
    undirected_graph<T, W>::node_iterator::node_iterator()
    {
    }

    template<typename T, typename W>
    undirected_graph<T, W>::node_iterator::~node_iterator()
    {
    }

    template<typename T, typename W>
    undirected_graph<T, W>::node_iterator::node_iterator(const node_iterator &rhs)
        : _it_ ( rhs._it_ )
        , _id_to_node_ptr_ ( rhs._id_to_node_ptr_ )
        , _node_to_id_ptr_ ( rhs._node_to_id_ptr_ )
    {
    }

    template<typename T, typename W>
    typename undirected_graph<T, W>::node_iterator& undirected_graph<T, W>::node_iterator::operator=(const node_iterator &rhs)
    {
        _it_ = rhs._it_;
        _id_to_node_ptr_ = rhs._id_to_node_ptr_;
        _node_to_id_ptr_ = rhs._node_to_id_ptr_;
        return *this;
    }

    template<typename T, typename W>
    undirected_graph<T, W>::node_iterator::node_iterator(node_iterator &&rhs) noexcept
        : _it_ ( std::move(rhs._it_) )                          // Member-wise move phase.
        , _id_to_node_ptr_ ( std::move(rhs._id_to_node_ptr_) )
        , _node_to_id_ptr_ ( std::move(rhs._node_to_id_ptr_) )
    {
        rhs._id_to_node_ptr_ = nullptr;                         // Reset phase.
        rhs._node_to_id_ptr_ = nullptr;
    }

    template<typename T, typename W>
    typename undirected_graph<T, W>::node_iterator& undirected_graph<T, W>::node_iterator::operator=(node_iterator &&rhs) noexcept
    {
        // Clean-up phase: Need not delete _id_to_node_ptr_ before moving, because it represents only a relationship(not ownership).
        
        // Member-wise move phase.
        _it_ = std::move(rhs._it_);
        _id_to_node_ptr_ = std::move(rhs._id_to_node_ptr_);
        _node_to_id_ptr_ = std::move(rhs._node_to_id_ptr_);
        
        // Reset phase.
        rhs._id_to_node_ptr_ = nullptr;
        rhs._node_to_id_ptr_ = nullptr;

        return *this;
    }

    // Private constructor. Only move version is sufficienct.
    template<typename T, typename W>
    undirected_graph<T, W>::node_iterator::node_iterator(const typename std::unordered_map<unsigned int, std::vector<Node<W>>>::iterator &rhs, std::unordered_map<unsigned int, T> *_id_to_node_, std::unordered_map<T, unsigned int> *_node_to_id_)
        : _it_ ( std::move(rhs) )                               // Member-wise move phase.
        , _id_to_node_ptr_ ( std::move(_id_to_node_) )
        , _node_to_id_ptr_ ( std::move(_node_to_id_) )
    {
        _id_to_node_ = nullptr;                         // Reset phase.
        _node_to_id_ = nullptr;
    }

    template<typename T, typename W>
    bool undirected_graph<T, W>::node_iterator::operator==(const node_iterator &rhs) const
    {
        return _it_ == rhs._it_;
    }

    template<typename T, typename W>
    bool undirected_graph<T, W>::node_iterator::operator!=(const node_iterator &rhs) const
    {
        return _it_ != rhs._it_;
    }

    template<typename T, typename W>
    typename undirected_graph<T, W>::node_iterator& undirected_graph<T, W>::node_iterator::operator++()
    {
        ++_it_;
        return *this;
    }

    template<typename T, typename W>
    typename undirected_graph<T, W>::node_iterator undirected_graph<T, W>::node_iterator::operator++(int)
    {
        node_iterator old = *this;
        ++_it_;
        return old;
    }

    template<typename T, typename W>
    const T& undirected_graph<T, W>::node_iterator::operator*() const
    {
        return _id_to_node_ptr_->at(_it_->first);
    }

    template<typename T, typename W>
    const T* undirected_graph<T, W>::node_iterator::operator->() const
    {
        return &(_id_to_node_ptr_->at(_it_->first));
    }

    template<typename T, typename W>
    void undirected_graph<T, W>::node_iterator::setNode(T node)
    {
        // Rename this node only if another node with same name doesn't exist.
        if(_node_to_id_ptr_->find(node) == _node_to_id_ptr_->end())
        {
            unsigned int id = _it_->first;
            _node_to_id_ptr_->erase(_id_to_node_ptr_->at(id));  // Removing the old entry in _node_to_id_.
            _node_to_id_ptr_->insert({node, id});               // Adding the new entry in _node_to_id_.
            _id_to_node_ptr_->at(id) = node;                    // Changing the node value in _id_to_node_.
        }
    }
}

#endif