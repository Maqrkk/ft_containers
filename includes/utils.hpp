#ifndef UTILS_HPP
# define UTILS_HPP

namespace ft
{
	// Lexicographical compare, for use in relational operators on containers.
	template <class InputIterator1, class InputIterator2>
	bool		lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
					InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return false;
			else if (*first1 < *first2)
				return true;
			first1++;
			first2++;
		}
		return (first2 != last2);
	}

	// Equal will be used as default for unique-type functions.
	template <typename T>
	bool		equal(T first, T second)
	{
		return (first == second);
	}

	// Less will be used as a predicate for merge/sort in list, and
	// default Compare function for map.
	template <class T>
	struct less
	{
		bool operator() (const T &x, const T &y) const
		{
			return (x < y);
		}
	};

	// Generic swap function
	template <class T>
	void		swap(T &first, T &second)
	{
		T		tmp;

		tmp = first;
		first = second;
		second = tmp;
	}
}

#endif
