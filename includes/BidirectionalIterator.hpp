#ifndef BIDIRECTIONALITERATOR_HPP
# define BIDIRECTIONALITERATOR_HPP

# include "Iterator.hpp"			// Extending base Iterator
# include "iterator_traits.hpp"		// For bidirectional_iterator_tag

namespace ft
{
	template <class T, class Pointer = T*, class Reference = T&,
			 class Category = ft::bidirectional_iterator_tag>
	class BidirectionalIterator : public Iterator<Category, T, Pointer, Reference>
	{
		public:
			// Iterator traits
			typedef Iterator<Category, T, Pointer, Reference>		base_iterator;
			typedef T												value_type;
			typedef typename base_iterator::difference_type			difference_type;
			typedef typename base_iterator::pointer					pointer;
			typedef typename base_iterator::reference				reference;
			typedef typename base_iterator::iterator_category		iterator_category;
			typedef BidirectionalIterator							iterator;

			// Default constructor
			BidirectionalIterator() : base_iterator()
			{
			}
			// Parameterized constructor
			BidirectionalIterator(pointer ptr) : base_iterator(ptr)
			{
			}
			// Copy constructor
			BidirectionalIterator(BidirectionalIterator const &src)
			{
				*this = src;
			}
			// Destructor
			virtual ~BidirectionalIterator()
			{
			}
			// Assignment operator overload
			BidirectionalIterator	&operator=(BidirectionalIterator const &src)
			{
				base_iterator::operator=(src);
				return *this;
			}
			// * operator
			reference				operator*() const
			{
				return *this->_ptr;
			}
			// -> operator
			pointer					operator->()
			{
				return this->_ptr;
			}
			// Prefix increment
			iterator				&operator++()
			{
				this->_ptr++;
				return *this;
			}
			// Postfix increment
			iterator				operator++(int)
			{
				iterator	tmp = *this;
				++(*this);
				return tmp;
			}
			// Prefix decrement
			iterator				&operator--()
			{
				this->_ptr--;
				return *this;
			}
			// Postfix decrement
			iterator				operator--(int)
			{
				iterator	tmp = *this;
				--(*this);
				return tmp;
			}
			// Friend function declarations
			template <class T1, class Cat>
			friend bool				operator==(const BidirectionalIterator<T1, T1*, T1&, Cat> &a,
												const BidirectionalIterator<T1, T1*, T1&, Cat> &b);
			template <class T1, class Cat>
			friend bool				operator!=(const BidirectionalIterator<T1, T1*, T1&, Cat> &a,
												const BidirectionalIterator<T1, T1*, T1&, Cat> &b);

	};
	// Equality operator
	template <class T, class Category>
	bool		operator==(const BidirectionalIterator<T, T*, T&, Category> &a,
							const BidirectionalIterator<T, T*, T&, Category> &b)
	{
		return (a._ptr == b._ptr);
	}
	// Inequality operator
	template <class T, class Category>
	bool		operator!=(const BidirectionalIterator<T, T*, T&, Category> &a,
							const BidirectionalIterator<T, T*, T&, Category> &b)
	{
		return (a._ptr != b._ptr);
	}
}

#endif
