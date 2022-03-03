#ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP

# include <cstddef>				// prtdiff_t
# include "enable_if.hpp"		// enable_if

namespace ft
{
	// Iterator tags
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	// is_iterator
	template <class T>
	struct is_iterator
	{
		private:
			typedef char	true_type;
			typedef int		false_type;

			template <class U>
				static true_type	test(typename U::iterator_category* = 0);
			template <class U>
				static false_type	test(...);

		public:
			static const bool		result = (sizeof(true_type) == sizeof(test<T>(0)));
	};

	// Iterator traits
	template <class Iterator, typename = typename ft::enable_if<is_iterator<Iterator>::result, Iterator>::type*>
	struct iterator_traits
	{
		typedef typename Iterator::iterator_category		iterator_category;
		typedef typename Iterator::value_type				value_type;
		typedef typename Iterator::difference_type			difference_type;
		typedef typename Iterator::pointer					pointer;
		typedef typename Iterator::reference				reference;
	};
	template <class T>
	struct iterator_traits<T*>
	{
		typedef random_access_iterator_tag				iterator_category;
		typedef	T										value_type;
		typedef std::ptrdiff_t							difference_type;
		typedef T*										pointer;
		typedef T&										reference;
	};
	template <class T>
	struct iterator_traits<const T*>
	{
		typedef random_access_iterator_tag				iterator_category;
		typedef T										value_type;
		typedef std::ptrdiff_t							difference_type;
		typedef const T*								pointer;
		typedef const T&								reference;
	};
}

#endif
