#ifndef RANDOMACCESSITERATOR_HPP
# define RANDOMACCESSITERATOR_HPP

# include "BidirectionalIterator.hpp"		// Extending BidirectionalIterator
# include "iterator_traits.hpp"				// random_access_iterator_tag

namespace ft
{
	template <class T, class Pointer, class Reference,
			 class Category = ft::random_access_iterator_tag>
	class RandomAccessIterator : public BidirectionalIterator<T, T*, T&, Category>
	{
		public:
			// Iterator traits
			typedef BidirectionalIterator<T, T*, T&, Category>					base_iterator;
			typedef T															value_type;
			typedef typename base_iterator::difference_type						difference_type;
			typedef typename base_iterator::pointer								pointer;
			typedef typename base_iterator::reference							reference;
			typedef typename base_iterator::iterator_category					iterator_category;
			typedef RandomAccessIterator<T, T*, T&>								iterator;
			typedef RandomAccessIterator<T, const T*, const T&>					const_iterator;

			// Default constructor
			RandomAccessIterator() : base_iterator()
			{
			}
			// Parameterized constructor
			RandomAccessIterator(pointer ptr) : base_iterator(ptr)
			{
			}
			// Copy constructor
			RandomAccessIterator(RandomAccessIterator const &src)
			{
				*this = src;
			}
			// Destructor
			virtual ~RandomAccessIterator()
			{
			}
			// Assignment operator overload
			RandomAccessIterator	&operator=(RandomAccessIterator const &src)
			{
				base_iterator::operator=(src);
				return *this;
			}
			// + operator
			RandomAccessIterator	operator+(difference_type n)
			{
				return iterator(this->_ptr + n);
			}
			// - operator (iterator - number)
			RandomAccessIterator	operator-(difference_type n)
			{
				iterator	tmp = iterator(this->_ptr - n);
				return tmp;
			}
			// - operator (iterator - iterator)
			difference_type	operator-(RandomAccessIterator const &it) const
			{
				return (this->_ptr - it._ptr);
			}
			// += operator
			RandomAccessIterator	operator+=(difference_type n)
			{
				this->_ptr += n;
				return *this;
			}
			// -= operator
			RandomAccessIterator	operator-=(difference_type n)
			{
				this->_ptr -= n;
				return *this;
			}
			// [] operator
			reference				operator[](difference_type n) const
			{
				return *(this->_ptr + n);
			}

			// Friend function declarations
			template <class T1, class T2, class T3>
			friend bool		operator==(RandomAccessIterator<T1, T2*, T2&> &a,
								RandomAccessIterator<T1, T3*, T3&> &b);
			template <class T1, class T2, class T3>
			friend bool		operator!=(RandomAccessIterator<T1, T2*, T2&> &a,
								RandomAccessIterator<T1, T3*, T3&> &b);
			template <class T1, class T2, class T3>
			friend bool		operator<(RandomAccessIterator<T1, T2*, T2&> &a,
								RandomAccessIterator<T1, T3*, T3&> &b);
			template <class T1,class T2, class T3>
			friend bool		operator>(RandomAccessIterator<T1, T2*, T2&> &a,
								RandomAccessIterator<T1, T3*, T3&> &b);
			template <class T1, class T2, class T3>
			friend bool		operator<=(RandomAccessIterator<T1, T2*, T2&> &a,
								RandomAccessIterator<T1, T3*, T3&> &b);
			template <class T1, class T2, class T3>
			friend bool		operator>=(RandomAccessIterator<T1, T2*, T2&> &a,
								RandomAccessIterator<T1, T3*, T3&> &b);

			// Implicit conversion function to const version
			operator	const_iterator() const
			{
				return const_iterator(this->_ptr);
			}
			operator	iterator() const
			{
				return iterator(this->_ptr);
			}
	};

	// == operator
	template <class T, class U, class V>
	bool		operator==(RandomAccessIterator<T, U*, U&> &a, RandomAccessIterator<T, V*, V&> &b)
	{
		return (a._ptr == b._ptr);
	}
	// != operator
	template <class T, class U, class V>
	bool		operator!=(RandomAccessIterator<T, U*, U&> &a, RandomAccessIterator<T, V*, V&> &b)
	{
		return (a._ptr != b._ptr);
	}
	// < operator
	template <class T, class U, class V>
	bool		operator<(RandomAccessIterator<T, U*, U&> &a, RandomAccessIterator<T, V*, V&> &b)
	{
		return (a._ptr < b._ptr);
	}
	// > operator
	template <class T, class U, class V>
	bool		operator>(RandomAccessIterator<T, U*, U&> &a, RandomAccessIterator<T, V*, V&> &b)
	{
		return (a._ptr > b._ptr);
	}
	// <= operator overload
	template <class T, class U, class V>
	bool		operator<=(RandomAccessIterator<T, U*, U&> &a, RandomAccessIterator<T, V*, V&> &b)
	{
		return (a._ptr <= b._ptr);
	}
	// >= operator overload
	template <class T, class U, class V>
	bool		operator>=(RandomAccessIterator<T, U*, U&> &a, RandomAccessIterator<T, V*, V&> &b)
	{
		return (a._ptr >= b._ptr);
	}
	// Overload for number + RandomAccessIterator
	template <class T>
	RandomAccessIterator<T, T*, T&>	operator+(typename RandomAccessIterator<T, T*, T&>::difference_type n,
			RandomAccessIterator<T, T*, T&> it)
	{
		return it + n;
	}
}
#endif
