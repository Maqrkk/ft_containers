#ifndef LIST_HPP
# define LIST_HPP

# include <cstddef>						// size_t, ptrdiff_t
# include <memory>						// allocator
# include "NodeIterator.hpp"			// NodeIterator class
# include "ReverseIterator.hpp"			// ReverseIterator class
# include "iterator_traits.hpp"			// Iterator traits
# include "utils.hpp"					// lexicographical_compare, less and equal predicates

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class list
	{
		// Forward declaration of Node
		private:
			class Node;

		//////////////////
		// MEMBER TYPES //
		//////////////////
		public:
			typedef T															value_type;
			typedef Alloc														allocator_type;
			typedef typename allocator_type::reference							reference;
			typedef typename allocator_type::const_reference					const_reference;
			typedef typename allocator_type::pointer							pointer;
			typedef typename allocator_type::const_pointer						const_pointer;
			typedef NodeIterator<Node, T>										iterator;
			typedef NodeIterator<const Node, const T>							const_iterator;
			typedef ReverseIterator<iterator>									reverse_iterator;
			typedef ReverseIterator<const_iterator>								const_reverse_iterator;
			typedef std::ptrdiff_t												difference_type;
			typedef std::size_t													size_type;
			typedef typename allocator_type::template rebind<Node>::other		NodeAlloc;

		//////////////
		// LISTNODE //
		//////////////
		private:
			class Node
			{
				public:
					// Default constructor
					Node()
					{
					}
					// Parameterized constructor
					Node(value_type const &val)
						: data(val), next(0), prev(0)
					{
					}
					// Copy constructor
					Node(Node const &src)
					{
						*this = src;
					}
					// Destructor
					virtual ~Node()
					{
					}
					// Assignment operator overload
					Node	&operator=(Node const &src)
					{
						this->data = src.data;
						this->next = src.next;
						this->prev = src.prev;
					}
					// Function to return the next pointer
					Node	*nextNode() const
					{
						return this->next;
					}
					// Function to return the prev pointer
					Node	*prevNode() const
					{
						return this->prev;
					}

					// Public variables
					value_type	data;
					Node	*next;
					Node	*prev;
			};

		//////////////////////
		// MEMBER FUNCTIONS //
		//////////////////////
		public:
			//////////////////
			// CONSTRUCTORS //
			//////////////////
			// Default constructor
			explicit list(const allocator_type &alloc = allocator_type())
			{
				this->_setUpSentinelNode();
				this->_allocator = alloc;
				this->_size = 0;
			}
			// Fill constructor
			explicit list(size_type n, const value_type &val = value_type(),
					const allocator_type &alloc = allocator_type())
			{
				this->_setUpSentinelNode();
				this->_allocator = alloc;
				this->_size = 0;
				this->assign(n, val);
			}
			// Range constructor
			template <class InputIterator>
			list(InputIterator first, InputIterator last,
					const allocator_type &alloc = allocator_type(),
					typename ft::iterator_traits<InputIterator>::type* = 0)
			{
				this->_setUpSentinelNode();
				this->_allocator = alloc;
				this->_size = 0;
				this->assign(first, last);
			}
			// Copy constructor
			list(const list &x)
			{
				this->_setUpSentinelNode();
				this->_allocator = x._allocator;
				this->_size = 0;
				*this = x;
			}
			////////////////
			// DESTRUCTOR //
			////////////////
			virtual ~list()
			{
				this->_destroyElements();
			}

			/////////////////////////
			// ASSIGNMENT OVERLOAD //
			/////////////////////////
			list	&operator=(const list &x)
			{
				this->_destroyElements();
				Node	*orig = x._sentinel.next;
				for (size_t i = 0; i < x.size(); i++)
				{
					this->push_back(orig->data);
					orig = orig->next;
				}
				return *this;
			}

			///////////////
			// ITERATORS //
			///////////////
			// Begin
			iterator				begin()
			{
				return iterator(this->_sentinel.next);
			}
			// Begin (const)
			const_iterator			begin() const
			{
				return const_iterator(this->_sentinel.next);
			}
			// End
			iterator				end()
			{
				return iterator(&this->_sentinel);
			}
			// End (const)
			const_iterator			end() const
			{
				return const_iterator(&this->_sentinel);
			}
			// Reverse begin
			reverse_iterator		rbegin()
			{
				return reverse_iterator(&this->_sentinel);
			}
			// Reverse begin (const)
			const_reverse_iterator	rbegin() const
			{
				return const_reverse_iterator(&this->_sentinel);
			}
			// Reverse end
			reverse_iterator		rend()
			{
				return reverse_iterator(this->_sentinel.next);
			}
			// Reverse end (const)
			const_reverse_iterator	rend() const
			{
				return const_reverse_iterator(this->_sentinel.next);
			}

			//////////////
			// CAPACITY //
			//////////////
			// Empty
			bool 		empty() const
			{
				return (this->_size == 0);
			}
			// Size
			size_type	size() const
			{
				return this->_size;
			}
			// Max size
			size_type	max_size() const
			{
				return this->_allocator.max_size();
			}

			////////////////////
			// ELEMENT ACCESS //
			////////////////////
			// Front
			reference		front()
			{
				return this->_sentinel.next->data;
			}
			// Front (const)
			const_reference	front() const
			{
				return this->_sentinel.next->data;
			}
			// Back
			reference		back()
			{
				return this->_sentinel.prev->data;
			}
			// Back (const)
			const_reference	back() const
			{
				return this->_sentinel.prev->data;
			}

			///////////////
			// MODIFIERS //
			///////////////
			// Assign (range)
			template <class InputIterator>
			void		assign(InputIterator first, InputIterator last,
					typename ft::iterator_traits<InputIterator>::type* = 0)
			{
				size_t		prevSize = this->_size;
				size_t		amount = ft::distance(first, last);

				for (size_t i = 0; i < amount; i++)
				{
					this->push_back(*first);
					first++;
				}
				for (size_t i = 0; i < prevSize; i++)
				{
					this->pop_front();
				}
			}
			// Assign (fill)
			void		assign(size_type n, const value_type &val)
			{
				this->_destroyElements();
				for (size_t i = 0; i < n; i++)
					this->push_back(val);
			}
			// Push front
			void		push_front(const value_type &val)
			{
				this->_makeNode(val, &this->_sentinel);
			}
			// Pop front
			void		pop_front()
			{
				this->_removeNode(this->_sentinel.next);
			}
			// Push back
			void		push_back(const value_type &val)
			{
				this->_makeNode(val, this->_sentinel.prev);
			}
			// Pop back
			void		pop_back()
			{
				this->_removeNode(this->_sentinel.prev);
			}

			// Insert (Single element)
			iterator	insert(iterator position, const value_type &val)
			{
				Node	*location;

				location = this->_findNode(position);
				this->_makeNode(val, location->prev);
				position--;
				return position;
			}
			// Insert (Fill)
			void		insert(iterator position, size_type n, const value_type &val)
			{
				Node	*location;

				location = this->_findNode(position);
				for (size_type i = 0; i < n; i++)
					this->_makeNode(val, location->prev);
			}
			// Insert (range)
			template <class InputIterator>
			void		insert(iterator position, InputIterator first, InputIterator last,
					typename ft::iterator_traits<InputIterator>::type* = 0)
			{
				Node	*location;

				location = this->_findNode(position);
				while (first != last)
				{
					this->_makeNode(*first, location->prev);
					first++;
				}
			}
			// Erase (Single element)
			iterator	erase(iterator position)
			{
				Node	*location;

				location = this->_findNode(position);
				position++;
				this->_removeNode(location);
				return position;
			}
			// Erase (Range)
			iterator	erase(iterator first, iterator last)
			{
				Node	*location;
				Node	*tmp;
				size_t		amount;

				location = this->_findNode(first);
				amount = ft::distance(first, last);
				for (size_t i = 0; i < amount; i++)
				{
					tmp = location;
					location = location->next;
					this->_removeNode(tmp);
				}
				return last;
			}
			// Swap
			void		swap(list &x)
			{
				list<T>		tmp;

				tmp.splice(tmp.begin(), *this);
				this->splice(this->begin(), x);
				x.splice(x.begin(), tmp);
			}
			// Resize
			void		resize(size_type n, value_type val = value_type())
			{
				size_type		amount;
				(void)val;
				if (n < this->_size)
				{
					amount = this->_size - n;
					for (size_type i = 0; i < amount; i++)
						this->_removeNode(this->_sentinel.prev);
				}
				else if (n > this->_size)
				{
					amount = n - this->_size;
					for (size_type i = 0; i < amount; i++)
						this->push_back(val);
				}
			}
			// Clear
			void		clear()
			{
				this->_destroyElements();
			}

			////////////////
			// OPERATIONS //
			////////////////
			// Splice (Entire list)
			void		splice(iterator position, list &x)
			{
				this->splice(position, x, x.begin(), x.end());
			}
			// Splice (Single element)
			void		splice(iterator position, list &x, iterator i)
			{
				Node	*location;
				Node	*node;

				location = this->_findNode(position);
				node = x._findNode(i);
				x._removeFromList(node);
				this->_insertNodeInList(node, location->prev);
			}
			// Splice (Element range)
			void		splice(iterator position, list &x, iterator first, iterator last)
			{
				iterator	tmp;
				while (first != last)
				{
					tmp = first;
					first++;
					splice(position, x, tmp);
				}
			}
			// Remove
			void		remove(const value_type &val)
			{
				Node	*curr;
				Node	*tmp;

				curr = this->_sentinel.next;
				while (curr != &this->_sentinel)
				{
					tmp = curr;
					curr = curr->next;
					if (tmp->data == val)
						this->_removeNode(tmp);
				}
			}
			// Remove if
			template <class Predicate>
			void		remove_if(Predicate pred)
			{
				Node	*curr;
				Node	*tmp;

				curr = this->_sentinel.next;
				while (curr != &this->_sentinel)
				{
					tmp = curr;
					curr = curr->next;
					if (pred(tmp->data))
						this->_removeNode(tmp);
				}
			}
			// Unique (No parameters)
			void		unique()
			{
				this->unique(&ft::equal<T>);
			}
			// Unique (Comparison function)
			template <class BinaryPredicate>
			void		unique(BinaryPredicate binary_pred)
			{
				Node	*curr;
				Node	*prev;
				Node	*tmp;

				if (this->_size < 2)
					return ;
				curr = this->_sentinel.next->next;
				while (curr != &this->_sentinel)
				{
					tmp = curr;
					prev = curr->prev;
					curr = curr->next;
					if (binary_pred(prev->data, tmp->data))
						this->_removeNode(tmp);
				}
			}
			// Merge (No parameters)
			void		merge(list &x)
			{
				this->merge(x, ft::less<T>());
			}
			// Merge (Comparison function)
			template <class Compare>
			void		merge(list &x, Compare comp)
			{
				Node	*curr;
				Node	*node;

				if (this == &x)
					return ;
				curr = this->_sentinel.next;
				while (curr != &this->_sentinel && x.size() != 0)
				{
					node = x._sentinel.next;
					if (comp(node->data, curr->data))
					{
						x._removeFromList(node);
						this->_insertNodeInList(node, curr->prev);
						continue ;
					}
					curr = curr->next;
				}
				if (x.size() != 0)
					this->splice(this->end(), x);
			}
			// Sort (No parameters)
			void		sort()
			{
				this->sort(ft::less<T>());
			}
			// Sort (Comparison function)
			template <class Compare>
			void		sort(Compare comp)
			{
				list<T>		tmp;
				size_t		pos;
				iterator	it;

				if (this->_size < 2)
					return ;
				pos = this->_size / 2;
				it = this->begin();
				for (size_t i = 0; i < pos; i++)
					it++;
				tmp.splice(tmp.begin(), *this, it, this->end());
				tmp.sort(comp);
				this->sort(comp);
				this->merge(tmp, comp);
			}
			// Reverse
			void		reverse()
			{
				list<T>				tmp;

				while (this->_size > 0)
					tmp.splice(tmp.end(), *this, --(this->end()));
				this->splice(this->begin(), tmp);
			}
			///////////////
			// OBSERVERS //
			///////////////
			// Get allocator
			allocator_type	get_allocator() const
			{
				return this->_allocator;
			}

		///////////////////////
		// PRIVATE VARIABLES //
		///////////////////////
		private:
			NodeAlloc	_allocator;
			Node		_sentinel;
			size_type	_size;

		//////////////////////////////
		// PRIVATE MEMBER FUNCTIONS //
		//////////////////////////////
		private:
			// This function sets up the sentinel node.
			void		_setUpSentinelNode()
			{
				this->_sentinel.next = &this->_sentinel;
				this->_sentinel.prev = &this->_sentinel;
				this->_sentinel.data = T();
			}
			// This function creates a new node and inserts it in between two existing
			// nodes in the list.
			void		_makeNode(const value_type &val, Node *prev)
			{
				Node	*node;

				node = this->_createNode(val);
				this->_insertNodeInList(node, prev);
			}
			// This function allocates space for a node, constructs it and 
			Node	*_createNode(const value_type &val)
			{
				Node	*node;

				node = this->_allocator.allocate(1);
				this->_allocator.construct(node, val);
				return node;
			}
			// This function inserts a node in between two others in a list
			void		_insertNodeInList(Node *node, Node *prev)
			{
				Node	*next;

				next = prev->next;
				node->prev = prev;
				prev->next = node;
				node->next = next;
				next->prev = node;
				this->_size += 1;
			}
			// This function removes a node, and links the next and prev pointers
			// of the surrounding links together.
			void		_removeNode(Node *node)
			{
				this->_removeFromList(node);
				this->_destroyNode(node);
			}
			// This function takes a node, and links its surrounding nodes together,
			// removing the link from the list but not deallocating it. It also updates
			// the head and tail if necessary.
			void		_removeFromList(Node *node)
			{
				Node	*prev;
				Node	*next;

				prev = node->prev;
				next = node->next;
				prev->next = next;
				next->prev = prev;
				this->_size -= 1;
			}
			// This function will return the node that an iterator is pointing to.
			Node	*_findNode(iterator position)
			{
				iterator	start;
				Node	*location;
				size_t		pos;

				location = this->_sentinel.next;
				start = this->begin();
				pos = ft::distance(start, position);
				for (size_t i = 0; i < pos; i++)
					location = location->next;
				return location;
			}
			// This function destroys all elements, and relinks the sentinel
			// to itself, in case it needs to be reused.
			void		_destroyElements()
			{
				Node	*curr = this->_sentinel.next;
				Node	*tmp;
				for (size_type i = 0; i < this->_size; i++)
				{
					tmp = curr->next;
					this->_destroyNode(curr);
					curr = tmp;
				}
				this->_size = 0;
				this->_sentinel.next = &this->_sentinel;
				this->_sentinel.prev = &this->_sentinel;
			}
			// This function destroys a single node, using the containers
			// allocator.
			void		_destroyNode(Node *node)
			{
				this->_allocator.destroy(node);
				this->_allocator.deallocate(node, 1);
			}
	};

	//////////////////////////
	// RELATIONAL OPERATORS //
	//////////////////////////
	// == operator
	template <class T, class Alloc>
	bool		operator==(const list<T, Alloc> &lhs, const list<T, Alloc> &rhs)
	{
		typename ft::list<T>::const_iterator		lhsit = lhs.begin();
		typename ft::list<T>::const_iterator		rhsit = rhs.begin();
		if (lhs.size() != rhs.size())
			return false;
		while (lhsit != lhs.end())
		{
			if (*lhsit != *rhsit)
				return false;
			lhsit++;
			rhsit++;
		}
		return true;
	}
	// != operator
	template <class T, class Alloc>
	bool		operator!=(const list<T, Alloc> &lhs, const list<T, Alloc> &rhs)
	{
		return !(lhs == rhs);
	}
	// < operator
	template <class T, class Alloc>
	bool		operator<(const list<T, Alloc> &lhs, const list<T, Alloc> &rhs)
	{
		return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	// <= operator
	template <class T, class Alloc>
	bool		operator<=(const list<T, Alloc> &lhs, const list<T, Alloc> &rhs)
	{
		return !(rhs < lhs);
	}
	// > operator
	template <class T, class Alloc>
	bool		operator>(const list<T, Alloc> &lhs, const list<T, Alloc> &rhs)
	{
		return (rhs < lhs);
	}
	// >= operator
	template <class T, class Alloc>
	bool		operator>=(const list<T, Alloc> &lhs, const list<T, Alloc> &rhs)
	{
		return !(lhs < rhs);
	}
	// Swap
	template <class T, class Alloc>
	void		swap(list<T, Alloc> &x, list<T, Alloc> &y)
	{
		x.swap(y);
	}
}

#endif
