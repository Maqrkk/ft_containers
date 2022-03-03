#ifndef REVERSEITERATOR_HPP
# define REVERSEITERATOR_HPP

# include "iterator_traits.hpp"		// For iterator tags

namespace ft
{
	template <class Iterator>
	class ReverseIterator
	{
		public:
			// Iterator traits
			typedef Iterator								iterator_type;
			typedef typename Iterator::iterator_category	iterator_category;
			typedef typename Iterator::value_type			value_type;
			typedef typename Iterator::difference_type		difference_type;
			typedef typename Iterator::pointer				pointer;
			typedef typename Iterator::reference			reference;
			typedef typename Iterator::iterator				base_normal;
			typedef typename Iterator::const_iterator		base_const;
			typedef ReverseIterator<base_normal>			iterator;
			typedef ReverseIterator<base_const>				const_iterator;

			// Default constructor
			ReverseIterator() : _base()
			{
			}
			// Parameterized constructor
			ReverseIterator(Iterator base) : _base(base)
			{
			}
			// Copy constructor
			ReverseIterator(ReverseIterator const &src) : _base(src._base)
			{
				*this = src;
			}
			// Destructor
			virtual ~ReverseIterator()
			{
			}
			// Assignment operator overload
			ReverseIterator		&operator=(ReverseIterator const &src)
			{
				this->_base = src._base;
				return *this;
			}

			// base
			iterator_type		base() const
			{
				return _base;
			}
			// * operator overload
			reference			operator*() const
			{
				Iterator	tmp = this->_base;
				return *--tmp;
			}
			// -> operator overload
			pointer				operator->()
			{
				return (&(operator*()));
			}
			// + operator overload
			ReverseIterator		operator+(difference_type n)
			{
				return iterator(this->_base - n);
			}
			// Prefix increment overload
			ReverseIterator		&operator++()
			{
				this->_base--;
				return *this;
			}
			// Postfix increment overload
			ReverseIterator		operator++(int)
			{
				ReverseIterator		tmp = *this;
				++(*this);
				return tmp;
			}
			// += operator overload
			ReverseIterator		operator+=(difference_type n)
			{
				this->_base -= n;
				return *this;
			}
			// - operator overload
			ReverseIterator		operator-(difference_type n)
			{
				return iterator(this->_base + n);
			}
			// Prefix decrement overload
			ReverseIterator		&operator--()
			{
				this->_base++;
				return *this;
			}
			// Postfix decrement overload
			ReverseIterator		operator--(int)
			{
				ReverseIterator		tmp = *this;
				--(*this);
				return tmp;
			}
			// -= operator overload
			ReverseIterator		operator-=(difference_type n)
			{
				this->_base += n;
				return *this;
			}
			// [] operator overload
			reference			operator[](difference_type n) const
			{
				return this->_base[-n-1];
			}
			// Const conversion function
			operator		const_iterator() const
			{
				return const_iterator(this->_base);
			}

		private:
			// Private variables
			Iterator	_base;
	};

	// == operator
	template <class Iterator1, class Iterator2>
	bool		operator==(const ReverseIterator<Iterator1> &lhs,
					const ReverseIterator<Iterator2> &rhs)
	{
		return (lhs.base() == rhs.base());
	}
	// != operator
	template <class Iterator1, class Iterator2>
	bool		operator!=(const ReverseIterator<Iterator1> &lhs,
					const ReverseIterator<Iterator2> &rhs)
	{
		return (lhs.base() != rhs.base());
	}
	// < operator
	template <class Iterator1, class Iterator2>
	bool		operator<(const ReverseIterator<Iterator1> &lhs,
					const ReverseIterator<Iterator2> &rhs)
	{
		return (lhs.base() > rhs.base());
	}
	// <= operator
	template <class Iterator1, class Iterator2>
	bool		operator<=(const ReverseIterator<Iterator1> &lhs,
					const ReverseIterator<Iterator2> &rhs)
	{
		return (lhs.base() >= rhs.base());
	}
	// > operator
	template <class Iterator1, class Iterator2>
	bool		operator>(const ReverseIterator<Iterator1> &lhs,
					const ReverseIterator<Iterator2> &rhs)
	{
		return (lhs.base() < rhs.base());
	}
	// >= operator
	template <class Iterator1, class Iterator2>
	bool		operator>=(const ReverseIterator<Iterator1> &lhs,
					const ReverseIterator<Iterator2> &rhs)
	{
		return (lhs.base() <= rhs.base());
	}
	// number + ReverseIterator
	template <class Iterator>
	ReverseIterator<Iterator>	operator+(typename ReverseIterator<Iterator>::difference_type n,
			ReverseIterator<Iterator> rit)
	{
		return rit + n;
	}
	// ReverseIterator - ReverseIterator
	template <class Iterator1, class Iterator2>
	typename ReverseIterator<Iterator1>::difference_type
		operator-(const ReverseIterator<Iterator1> &lhs,
					const ReverseIterator<Iterator2> &rhs)
	{
		return (rhs.base() - lhs.base());
	}
}

#endif
