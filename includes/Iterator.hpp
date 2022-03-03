#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <cstddef>					// ptrdiff_t
# include "iterator_traits.hpp"		// iterator_traits

namespace ft
{
	template <class Category, class T, class Pointer = T*, class Reference = T&,
			 class Distance = std::ptrdiff_t>
	class Iterator
	{
		public:
			// Iterator traits
			typedef T				value_type;
			typedef Distance		difference_type;
			typedef Pointer			pointer;
			typedef Reference		reference;
			typedef Category		iterator_category;

			// Default constructor
			Iterator() : _ptr(0)
			{
			}
			// Parameterized constructor
			Iterator(pointer ptr) : _ptr(ptr)
			{
			}
			// Copy constructor
			Iterator(Iterator const &src)
			{
				*this = src;
			}
			// Destructor
			virtual ~Iterator()
			{
			}
			// Assignment operator overload
			Iterator	&operator=(Iterator const &src)
			{
				this->_ptr = src._ptr;
				return *this;
			}

		protected:
			pointer		_ptr;
	};

	template <class Iterator>
	typename iterator_traits<Iterator>::difference_type
		do_distance(Iterator first, Iterator last, ft::input_iterator_tag)
	{
		typename iterator_traits<Iterator>::difference_type		dist;

		dist = 0;
		while (first != last)
		{
			first++;
			dist++;
		}
		return dist;
	}
	template <class Iterator>
	typename iterator_traits<Iterator>::difference_type
		do_distance(Iterator first, Iterator last, ft::random_access_iterator_tag)
	{
		return (last - first);
	}
	template <class InputIterator>
	typename iterator_traits<InputIterator>::difference_type
		distance(InputIterator first, InputIterator last)
	{
		return do_distance(first, last, typename iterator_traits<InputIterator>::iterator_category());
	}
}

#endif
