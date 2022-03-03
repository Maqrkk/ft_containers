#ifndef MAP_HPP
# define MAP_HPP

# include <cstddef>					// size_t, ptrdiff_t
# include <memory>					// allocator
# include "NodeIterator.hpp"		// NodeIterator class
# include "ReverseIterator.hpp"		// ReverseIterator class
# include "pair.hpp"				// pair class
# include "utils.hpp"				// less predicate, lexicographical_compare

namespace ft
{
	template <class Key,
			 class T,
			 class Compare = less<Key>,
			 class Alloc = std::allocator<ft::pair<const Key, T> > >
	class map
	{
		// Forward declaration of Node
		private:
			class Node;

		//////////////////
		// MEMBER TYPES //
		//////////////////
		public:
			typedef Key														key_type;
			typedef T														mapped_type;
			typedef ft::pair<const key_type, mapped_type>					value_type;
			typedef Compare													key_compare;
			typedef Alloc													allocator_type;
			typedef typename allocator_type::reference						reference;
			typedef typename allocator_type::const_reference				const_reference;
			typedef typename allocator_type::pointer						pointer;
			typedef typename allocator_type::const_pointer					const_pointer;
			typedef NodeIterator<Node, value_type>							iterator;
			typedef NodeIterator<Node, const value_type>					const_iterator;
			typedef ReverseIterator<iterator>								reverse_iterator;
			typedef ReverseIterator<const_iterator>							const_reverse_iterator;
			typedef std::ptrdiff_t											difference_type;
			typedef std::size_t												size_type;
			typedef typename allocator_type::template rebind<Node>::other	NodeAlloc;

		////////////////
		// VALUE_COMP //
		////////////////
		public:
			class value_compare
			{
				protected:
					Compare		comp;

				public:
					value_compare(Compare c) : comp(c)
					{
					}
					typedef bool		result_type;
					typedef value_type	first_argument_type;
					typedef value_type	second_argument_type;

					bool		operator() (const value_type &x, const value_type &y) const
					{
						return comp(x.first, y.first);
					}
			};

		//////////
		// NODE //
		//////////
		private:
			class Node
			{
				public:
					// Default constructor
					Node() : data(value_type()), height(0), left(0), right(0), parent(0), leftMost(0), rightMost(0)
					{
					}
					// Parameterized constructor
					Node(value_type const &val)
						: data(val), height(1), left(0), right(0), parent(0), leftMost(0), rightMost(0)
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
					Node		&operator=(Node const &src)
					{
						this->height = src.height;
						this->left = src.left;
						this->right = src.right;
						this->parent = src.parent;
						this->leftMost = src.leftMost;
						this->rightMost = src.rightMost;
						return *this;
					}
					// Function to return the next node.
					Node		*nextNode() const
					{
						Node		*returnNode;

						// If we are the rightMost, return 0
						if (this == this->rightMost)
							return 0;
						// If we are the leftMost, find the lowest value in the map.
						// If we have a right subtree, find its lowest value in the subtree.
						if (this == this->leftMost || this->right)
						{
							if (this == this->leftMost)
							{
								// leftMost and rightMost use their 'right' pointer to
								// represent the root of the tree.
								returnNode = this->right;
								if (returnNode == 0)
									return this->rightMost;
							}
							else
								returnNode = this->right;
							while (returnNode->left)
								returnNode = returnNode->left;
							return returnNode;
						}
						// If we do not have a right child, traverse up the tree until
						// we've gone up from a left leaf. If at any point we encounter
						// a parent of 0, return rightMost.
						returnNode = const_cast<Node *>(this);
						while (returnNode->parent)
						{
							if (returnNode->isOnLeft())
								return returnNode->parent;
							returnNode = returnNode->parent;
						}
						return this->rightMost;
					}
					// Function to return the previous node.
					Node		*prevNode() const
					{
						Node		*returnNode;

						// If we are the leftMost, return 0
						if (this == this->leftMost)
							return 0;
						// If we are the rightMost, find the highest value in the map.
						// If we have a right subtree, find its highest value in the subtree.
						if (this == this->rightMost || this->left)
						{
							if (this == this->rightMost)
							{
								// leftMost and rightMost use their 'right' pointer to
								// represent the root of the tree.
								returnNode = this->right;
								if (returnNode == 0)
									return this->leftMost;
							}
							else
								returnNode = this->left;
							while (returnNode->right)
								returnNode = returnNode->right;
							return returnNode;
						}
						// If we do not have a left child, traverse up the tree until
						// we've gone up from a right leaf. If at any point we encounter
						// a parent of 0, return leftMost.
						returnNode = const_cast<Node *>(this);
						while (returnNode->parent)
						{
							if (!returnNode->isOnLeft())
								return returnNode->parent;
							returnNode = returnNode->parent;
						}
						return returnNode;
					}

					// Public helper functions
					bool		isOnLeft()
					{
						if (this->parent)
							return this == this->parent->left;
						return false;
					}
					// Update the height of this node in the tree.
					void		updateHeight()
					{
						int		left;
						int		right;
						int		highest;

						left = this->_getLeftHeight();
						right = this->_getRightHeight();
						highest = (left < right) ? right : left;
						this->height = 1 + highest;
					}
					// Get the balance of this node.
					int			getBalance()
					{
						return (this->_getLeftHeight() - this->_getRightHeight());
					}
					// This function will set the leftMost and rightMost pointers
					// for itself, and any children it has.
					void		updateSentinelLinks(Node *newLeft, Node *newRight)
					{
						this->leftMost = newLeft;
						this->rightMost = newRight;
						if (this->left)
							this->left->updateSentinelLinks(newLeft, newRight);
						if (this->right)
							this->right->updateSentinelLinks(newLeft, newRight);
					}

					// Public variables
					value_type		data;
					int				height;
					Node			*left;
					Node			*right;
					Node			*parent;
					Node			*leftMost;
					Node			*rightMost;

				private:
					// Private helper functions
					// Get the height of the left subtree.
					int			_getLeftHeight()
					{
						if (this->left == 0)
							return 0;
						return this->left->height;
					}
					// Get the height of the right subtree.
					int			_getRightHeight()
					{
						if (this->right == 0)
							return 0;
						return this->right->height;
					}
			};
		//////////////////////
		// MEMBER FUNCTIONS //
		//////////////////////
		public:
			//////////////////
			// CONSTRUCTORS //
			//////////////////
			// Default constructor
			explicit map(const key_compare &comp = key_compare(),
					const allocator_type &alloc = allocator_type())
				: _allocator(alloc), _compare(comp),
					_valueCompare(value_compare(comp)), _root(0), _size(0)
			{
				this->_initSentinelNodes();
			}
			// Range constructor
			template <class InputIterator>
			map(InputIterator first, InputIterator last,
					const key_compare &comp = key_compare(),
					const allocator_type &alloc = allocator_type(),
					typename ft::iterator_traits<InputIterator>::type* = 0)
				: _allocator(alloc), _compare(comp),
					_valueCompare(value_compare(comp)), _root(0), _size(0)
			{
				this->_initSentinelNodes();
				this->insert(first, last);
			}
			// Copy constructor
			map(const map &x)
				: _allocator(x._allocator), _compare(x._compare),
					_valueCompare(x._valueCompare), _root(0), _size(0)
			{
				this->_initSentinelNodes();
				*this = x;
				this->_updateSentinelNodes();
			}
			////////////////
			// DESTRUCTOR //
			////////////////
			virtual ~map()
			{
				this->_destroyElements();
			}

			/////////////////////////
			// ASSIGNMENT OVERLOAD //
			/////////////////////////
			map		&operator=(const map &x)
			{
				this->_destroyElements();
				this->_compare = x._compare;
				Node	*orig = x._lowest.nextNode();
				for (size_t i = 0; i < x.size(); i++)
				{
					this->_root = this->_insert(this->_root, orig->data, 0);
					orig = orig->nextNode();
				}

				return *this;
			}

			///////////////
			// ITERATORS //
			///////////////
			// Begin
			iterator				begin()
			{
				return iterator(this->_lowest.nextNode());
			}
			// Begin (const)
			const_iterator			begin() const
			{
				return const_iterator(this->_lowest.nextNode());
			}
			// End
			iterator				end()
			{
				return iterator(&this->_highest);
			}
			// End (const)
			const_iterator			end() const
			{
				return const_iterator(const_cast<Node *>(&this->_highest));
			}
			// Reverse begin
			reverse_iterator		rbegin()
			{
				return reverse_iterator(&this->_highest);
			}
			// Reverse begin (const)
			const_reverse_iterator	rbegin() const
			{
				return const_reverse_iterator(const_cast<Node *>(&this->_highest));
			}
			// Reverse end
			reverse_iterator		rend()
			{
				return reverse_iterator(this->_lowest.nextNode());
			}
			// Reverse end (const)
			const_reverse_iterator	rend() const
			{
				return const_reverse_iterator(this->_lowest.nextNode());
			}

			//////////////
			// CAPACITY //
			//////////////
			// Empty
			bool		empty() const
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
			// Operator []
			mapped_type		&operator[](const key_type &k)
			{
				ft::pair<Key, T>	p;
				Node				*node;

				node = this->_findNode(k);
				if (!node)
				{
					p.first = k;
					p.second = mapped_type();
					this->_root = this->_insert(this->_root, p, 0);
					this->_updateSentinelNodes();
					node = this->_findNode(k);
				}
				return node->data.second;
			}

			///////////////
			// MODIFIERS //
			///////////////
			// Insert (Single element)
			pair<iterator, bool>	insert(const value_type &val)
			{
				Node		*node;
				bool		added;

				node = this->_findNode(val.first);
				added = (node == 0);
				if (!node)
				{
					this->_root = this->_insert(this->_root, val, 0);
					this->_updateSentinelNodes();
					node = this->_findNode(val.first);
				}
				return ft::pair<iterator, bool>(iterator(node), added);
			}
			// Insert (With hint)
			iterator				insert(iterator position, const value_type &val)
			{
				Node		*node;

				(void)position;
				node = this->_findNode(val.first);
				if (!node)
				{
					this->_root = this->_insert(this->_root, val, 0);
					this->_updateSentinelNodes();
					node = this->_findNode(val.first);
				}
				return iterator(node);
			}
			// Insert (Range)
			template <class InputIterator>
			void					insert(InputIterator first, InputIterator last,
					typename ft::iterator_traits<InputIterator>::iterator_category* = 0)
			{
				Node	*node;

				while (first != last)
				{
					node = this->_findNode(first->first);
					if (!node)
					{
						this->_root = this->_insert(this->_root, *first, 0);
						this->_updateSentinelNodes();
					}
					first++;
				}
			}
			// Erase (By iterator)
			void					erase(iterator position)
			{
				this->_root = this->_remove(this->_root, *position);
				this->_updateSentinelNodes();
			}
			// Erase (By key)
			size_type				erase(const key_type &k)
			{
				Node	*node;

				node = this->_findNode(k);
				if (!node)
					return 0;
				this->_root = this->_remove(this->_root, node->data);
				this->_updateSentinelNodes();
				return 1;
			}
			// Erase (Iterator range)
			void					erase(iterator first, iterator last)
			{
				iterator	tmp;
				while (first != last)
				{
					tmp = first;
					first++;
					this->erase(tmp);
				}
			}
			// Swap
			void					swap(map &x)
			{
				ft::swap(this->_root, x._root);
				ft::swap(this->_size, x._size);
				this->_root->updateSentinelLinks(&this->_lowest, &this->_highest);
				x._root->updateSentinelLinks(&x._lowest, &x._highest);
				this->_updateSentinelNodes();
				x._updateSentinelNodes();
			}
			// Clear
			void					clear()
			{
				this->_destroyElements();
			}

			///////////////
			// OBSERVERS //
			///////////////
			// Key comp
			key_compare		key_comp() const
			{
				return this->_compare;
			}
			// Value comp
			value_compare	value_comp() const
			{
				return this->_valueCompare;
			}

			////////////////
			// OPERATIONS //
			////////////////
			// Find
			iterator		find(const key_type &k)
			{
				Node	*node;

				node = this->_findNode(k);
				if (node)
					return iterator(node);
				return iterator(&this->_highest);
			}
			// Find (const)
			const_iterator	find(const key_type &k) const
			{
				Node	*node;

				node = this->_findNode(k);
				if (node)
					return const_iterator(node);
				return const_iterator(&this->_highest);
			}
			// Count
			size_type		count(const key_type &k) const
			{
				Node	*node;

				node = this->_findNode(k);
				if (node)
					return 1;
				return 0;
			}
			// Lower bound
			iterator		lower_bound(const key_type &k)
			{
				Node		*node;

				node = this->_lowest.nextNode();
				while (node != &this->_highest && this->_compare(node->data.first, k))
					node = node->nextNode();
				return iterator(node);
			}
			// Lower bound (const)
			const_iterator	lower_bound(const key_type &k) const
			{
				Node		*node;

				node = this->_lowest.nextNode();
				while (node != &this->_highest && this->_compare(node->data.first, k))
					node = node->nextNode();
				return const_iterator(node);
			}
			// Upper bound
			iterator		upper_bound(const key_type &k)
			{
				Node		*node;

				node = this->_lowest.nextNode();
				while (node != &this->_highest &&
						(this->_compare(node->data.first, k) || node->data.first == k))
					node = node->nextNode();
				return iterator(node);
			}
			// Upper bound (const)
			const_iterator	upper_bound(const key_type &k) const
			{
				Node		*node;

				node = this->_lowest.nextNode();
				while (node != &this->_highest &&
						(this->_compare(node->data.first, k) || node->data.first == k))
					node = node->nextNode();
				return const_iterator(node);
			}
			// Equal range
			ft::pair<iterator, iterator>				equal_range(const key_type &k)
			{
				ft::pair<iterator, iterator>	ret;

				ret.first = this->lower_bound(k);
				ret.second = this->upper_bound(k);
				return ret;
			}
			// Equal range (const)
			ft::pair<const_iterator, const_iterator>	equal_range(const key_type &k) const
			{
				ft::pair<const_iterator, const_iterator>	ret;

				ret.first = this->lower_bound(k);
				ret.second = this->upper_bound(k);
				return ret;
			}

			///////////////
			// ALLOCATOR //
			///////////////
			allocator_type		get_allocator() const
			{
				return this->_allocator;
			}

		///////////////////////
		// PRIVATE VARIABLES //
		///////////////////////
		private:
			NodeAlloc		_allocator;		// The internal allocator.
			key_compare		_compare;		// The function object that compares keys.
			value_compare	_valueCompare;	// The function object that.. also compares keys.
			Node			*_root;			// A pointer to the root of the tree.
			Node			_lowest;		// A sentinel node to use for iterators (rend)
			Node			_highest;		// A sentinel node to use for iterators (end)
			size_type		_size;			// The size of the list.

		//////////////////////////////
		// PRIVATE MEMBER FUNCTIONS //
		//////////////////////////////
		private:
			// This function initializes the two sentinel nodes.
			void			_initSentinelNodes()
			{
				this->_lowest.leftMost = &this->_lowest;
				this->_lowest.rightMost = &this->_highest;
				this->_highest.leftMost = &this->_lowest;
				this->_highest.rightMost = &this->_highest;
			}
			// This function updates the leftmost and rightmost leaves, that are used
			// for sentinels, for iterators.
			void			_updateSentinelNodes()
			{
				this->_lowest.right = this->_root;
				this->_highest.right = this->_root;
			}
			// This function destroys all map nodes.
			void			_destroyElements()
			{
				this->_recursiveDestroy(this->_root);
				this->_root = 0;
			}
			// This function recursively destroys and deallocates a node and its children.
			void			_recursiveDestroy(Node *node)
			{
				if (!node)
					return ;
				this->_recursiveDestroy(node->left);
				this->_recursiveDestroy(node->right);
				this->_destroyNode(node);
			}
			// This function uses the allocator to destruct and deallocate a Node.
			void			_destroyNode(Node *node)
			{
				this->_allocator.destroy(node);
				this->_allocator.deallocate(node, 1);
				this->_size--;
			}
			// This function uses the allocator to allocate and construct a new Node.
			Node			*_createNode(const value_type &val, Node *parent)
			{
				Node	*node;

				node = this->_allocator.allocate(1);
				this->_allocator.construct(node, val);
				node->parent = parent;
				node->leftMost = &this->_lowest;
				node->rightMost = &this->_highest;
				this->_size++;
				return node;
			}
			// This function will perform a left rotation at a certain node.
			void		_leftRotate(Node *node)
			{
				Node	*parent = node->parent;
				bool	nodeIsLeft = node->isOnLeft();
				Node	*rightChild = node->right;
				Node	*rightLeftChild = rightChild->left;

				// Move the rightLeftChild to be the right child of the node.
				node->right = rightLeftChild;
				if (rightLeftChild)
					rightLeftChild->parent = node;

				// Move the node to be the left child of its original right child.
				rightChild->left = node;
				node->parent = rightChild;

				// Update the new parent node's parent.
				rightChild->parent = parent;
				if (parent)
				{
					if (nodeIsLeft)
						parent->left = rightChild;
					else
						parent->right = rightChild;
				}

				// Update the heights.
				node->updateHeight();
				rightChild->updateHeight();
			}
			// This function will perform a right rotation at a certain node.
			void		_rightRotate(Node *node)
			{
				Node	*parent = node->parent;
				bool	nodeIsLeft = node->isOnLeft();
				Node	*leftChild = node->left;
				Node	*leftRightChild = leftChild->right;

				// Move the leftRightChild to be the left child of the node.
				node->left = leftRightChild;
				if (leftRightChild)
					leftRightChild->parent = node;

				// Move the node to be the right child of its original left child.
				leftChild->right = node;
				node->parent = leftChild;

				// Update the new parent node's parent.
				leftChild->parent = parent;
				if (parent)
				{
					if (nodeIsLeft)
						parent->left = leftChild;
					else
						parent->right = leftChild;
				}

				// Update the heights.
				node->updateHeight();
				leftChild->updateHeight();
			}
			// This function will insert a new Node into the map.
			Node			*_insert(Node *node, const value_type &val, Node *parent)
			{
				int			balance;

				// Base case, if node is NULL we add a node here.
				if (node == 0)
					return this->_createNode(val, parent);

				// Find the spot to insert this node.
				if (this->_compare(val.first, node->data.first))
					node->left = this->_insert(node->left, val, node);
				else if (val.first != node->data.first)
					node->right = this->_insert(node->right, val, node);
				else
					return node;

				// Update the height (this will happen recursively from bottom to top).
				node->updateHeight();

				// Rebalance if necessary.
				balance = node->getBalance();
				if (balance > 1 && this->_compare(val.first, node->left->data.first))
				{
					// Left left case.
					this->_rightRotate(node);
					return node->parent;
				}
				else if (balance > 1)
				{
					// Left right case
					this->_leftRotate(node->left);
					this->_rightRotate(node);
					return node->parent;
				}
				else if (balance < -1 && this->_compare(val.first, node->right->data.first))
				{
					// Right left case
					this->_rightRotate(node->right);
					this->_leftRotate(node);
					return node->parent;
				}
				else if (balance < -1)
				{
					// Right right case
					this->_leftRotate(node);
					return node->parent;
				}
				return node;
			}
			// This function will remove a Node from the map.
			Node			*_remove(Node *node, const value_type &val)
			{
				int			balance;

				// Base case, if we arrive at 0 we haven't found the node to delete.
				if (node == 0)
					return 0;

				// Find the node to delete.
				if (this->_compare(val.first, node->data.first))
					node->left = this->_remove(node->left, val);
				else if (val.first != node->data.first)
					node->right = this->_remove(node->right, val);
				else
				{
					// We've found the node to delete.
					// Decide what to do based on the number of child nodes.
					if (node->left == 0 && node->right == 0)
					{
						// No children, delete the node.
						// Update the parent.
						if (node->parent)
						{
							if (node->isOnLeft())
								node->parent->left = 0;
							else
								node->parent->right = 0;
						}
						this->_destroyNode(node);
						node = 0;
					}
					else if (node->left == 0 || node->right == 0)
					{
						// One child. Remove the node and put the child in its place.
						Node	*child = (node->left == 0) ? node->right : node->left;

						// Update the parent.
						child->parent = node->parent;
						if (node->parent)
						{
							if (node->isOnLeft())
								node->parent->left = child;
							else
								node->parent->right = child;
						}
						this->_destroyNode(node);
						node = child;
					}
					else
					{
						// Two children
						// Find this node's replacement. It will be the lowest value
						// in the right subtree.
						Node	*replacement = node->right;
						while (replacement->left)
							replacement = replacement->left;

						// Copy the replacement's key to this node.
						this->_swapNodes(node, replacement);

						// Continue the deletion recursively with the new key.
						replacement->right = this->_remove(replacement->right, node->data);
						node = replacement;
					}
				}

				// If this was a leaf, return.
				if (node == 0)
					return 0;

				// Update the height.
				node->updateHeight();

				// See if we need to rebalance.
				balance = node->getBalance();
				if (balance > 1 && node->left->getBalance() >= 0)
				{
					this->_rightRotate(node);
					return node->parent;
				}
				else if (balance > 1)
				{
					this->_leftRotate(node->left);
					this->_rightRotate(node);
					return node->parent;
				}
				else if (balance < -1 && node->right->getBalance() > 0)
				{
					this->_rightRotate(node->right);
					this->_leftRotate(node);
					return node->parent;
				}
				else if (balance < -1)
				{
					this->_leftRotate(node);
					return node->parent;
				}

				// Return the node.
				return node;
			}
			// This function will try to find a node with the key given.
			Node			*_findNode(const key_type &k) const
			{
				Node		*node;

				node = this->_root;
				while (node)
				{
					if (k == node->data.first)
						return node;
					if (this->_compare(k, node->data.first))
						node = node->left;
					else
						node = node->right;
				}
				return node;
			}
			// This function will swap two nodes (for deletion purposes)
			void		_swapNodes(Node *n1, Node *n2)
			{
				// Swap the parents
				if (n1->parent)
				{
					if (n1->isOnLeft())
						n1->parent->left = n2;
					else
						n1->parent->right = n2;
				}
				if (n2->isOnLeft())
					n2->parent->left = n1;
				else
					n2->parent->right = n1;
				ft::swap(n1->parent, n2->parent);

				// Swap the left children.
				if (n1->left)
					n1->left->parent = n2;
				if (n2->left)
					n2->left->parent = n1;
				ft::swap(n1->left, n2->left);

				// Swap the right children.
				if (n1->right)
					n1->right->parent = n2;
				if (n2->right)
					n2->right->parent = n1;
				ft::swap(n1->right, n2->right);

				// Swap the heights of the nodes.
				ft::swap(n1->height, n2->height);
			}
	};

	//////////////////////////
	// RELATIONAL OPERATORS //
	//////////////////////////
	// == operator
	template <class Key, class T, class Compare, class Alloc>
	bool		operator==(const map<Key, T, Compare, Alloc> &lhs,
							const map<Key, T, Compare, Alloc> &rhs)
	{
		typename map<Key, T, Compare, Alloc>::const_iterator	lhsit, rhsit;

		if (lhs.size() != rhs.size())
			return false;
		lhsit = lhs.begin();
		rhsit = rhs.begin();
		while (lhsit != lhs.end())
		{
			if ((lhsit->first != rhsit->first) || (lhsit->second != rhsit->second))
				return false;
			lhsit++;
			rhsit++;
		}
		return true;
	}
	// != operator
	template <class Key, class T, class Compare, class Alloc>
	bool		operator!=(const map<Key, T, Compare, Alloc> &lhs,
							const map<Key, T, Compare, Alloc> &rhs)
	{
		return !(lhs == rhs);
	}
	// < operator
	template <class Key, class T, class Compare, class Alloc>
	bool		operator<(const map<Key, T, Compare, Alloc> &lhs,
							const map<Key, T, Compare, Alloc> &rhs)
	{
		return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	// <= operator
	template <class Key, class T, class Compare, class Alloc>
	bool		operator<=(const map<Key, T, Compare, Alloc> &lhs,
							const map<Key, T, Compare, Alloc> &rhs)
	{
		return !(rhs < lhs);
	}
	// > operator
	template <class Key, class T, class Compare, class Alloc>
	bool		operator>(const map<Key, T, Compare, Alloc> &lhs,
							const map<Key, T, Compare, Alloc> &rhs)
	{
		return (rhs < lhs);
	}
	// >= operator
	template <class Key, class T, class Compare, class Alloc>
	bool		operator>=(const map<Key, T, Compare, Alloc> &lhs,
							const map<Key, T, Compare, Alloc> &rhs)
	{
		return !(lhs < rhs);
	}
	// Swap
	template <class Key, class T, class Compare, class Alloc>
	void		swap(map<Key, T, Compare, Alloc> &lhs,
					map<Key, T, Compare, Alloc> &rhs)
	{
		lhs.swap(rhs);
	}
}

#endif
