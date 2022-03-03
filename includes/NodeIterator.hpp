#ifndef NODEITERATOR_HPP
# define NODEITERATOR_HPP

# include "BidirectionalIterator.hpp"		// Extending BidirectionalIterator

namespace ft
{
	template <class Node, class T, class Pointer = T*, class Reference = T&>
	class NodeIterator : public BidirectionalIterator<Node>
	{
		public:
			// Iterator traits
			typedef BidirectionalIterator<Node>					base_iterator;
			typedef T											value_type;
			typedef Node										node_type;
			typedef typename base_iterator::difference_type		difference_type;
			typedef Pointer										pointer;
			typedef Reference									reference;
			typedef typename base_iterator::iterator_category	iterator_category;
			typedef NodeIterator<Node, T>						iterator;
			typedef NodeIterator<Node, const T>					const_iterator;

			// Default constructor
			NodeIterator() : base_iterator()
			{
			}
			// Parameterized constructor
			NodeIterator(Node *ptr) : base_iterator(ptr)
			{
			}
			// Copy constructor
			NodeIterator(NodeIterator const &src)
			{
				*this = src;
			}
			// Destructor
			virtual ~NodeIterator()
			{
			}
			// Assignment operator overload
			NodeIterator		&operator=(NodeIterator const &src)
			{
				base_iterator::operator=(src);
				return *this;
			}
			// * operator
			reference			operator*() const
			{
				return this->_ptr->data;
			}
			// -> operator
			pointer				operator->()
			{
				return &(this->_ptr->data);
			}
			// Prefix increment
			iterator			&operator++()
			{
				this->_ptr = this->_ptr->nextNode();
				return *this;
			}
			// Postfix increment
			iterator			operator++(int)
			{
				iterator	tmp(*this);
				++(*this);
				return tmp;
			}
			// Prefix decrement
			iterator			&operator--()
			{
				this->_ptr = this->_ptr->prevNode();
				return *this;
			}
			// Postfix decrement
			iterator			operator--(int)
			{
				iterator	tmp(*this);
				--(*this);
				return tmp;
			}
			// Implicit conversion function to const version
			operator	NodeIterator<const Node, const T>() const
			{
				return NodeIterator<const Node, const T>(this->_ptr);
			}

			// Friend function declarations
			template <class Node1, class Node2, class T1, class T2>
			friend bool		operator==(NodeIterator<Node1, T1> &a,
								NodeIterator<Node2, T2> &b);
			template <class Node1, class Node2, class T1, class T2>
			friend bool		operator!=(NodeIterator<Node1, T1> &a,
								NodeIterator<Node2, T2> &b);
	};

	// == operator
	template <class Node1, class Node2, class T, class U>
	bool		operator==(NodeIterator<Node1, T> &a, NodeIterator<Node2, U> &b)
	{
		return (a._ptr == b._ptr);
	}
	// != operator
	template <class Node1, class Node2, class T, class U>
	bool		operator!=(NodeIterator<Node1, T> &a, NodeIterator<Node2, U> &b)
	{
		return (a._ptr != b._ptr);
	}
}

#endif
