#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft
{
	template <class T1, class T2>
	struct pair
	{
		//////////////////
		// MEMBER TYPES //
		//////////////////
		public:
			typedef T1			first_type;
			typedef T2			second_type;

		//////////////////////
		// MEMBER FUNCTIONS //
		//////////////////////
		public:
			//////////////////
			// CONSTRUCTORS //
			//////////////////
			// Default constructor
			pair() :
				first(T1()), second(T2())
			{
			}
			// Copy constructor
			template <class U, class V>
			pair (const pair<U, V> &pr) :
				first(pr.first), second(pr.second)
			{
			}
			// Initialization constructor
			pair (const first_type &a, const second_type &b) :
				first(a), second(b)
			{
			}
			// Destructor
			~pair()
			{
			}
			// Assignment overload
			pair		&operator=(const pair &pr)
			{
				this->first = pr.first;
				this->second = pr.second;
				return *this;
			}
		///////////////////////
		// PUBLIC VARIABLES //
		///////////////////////
		public:
			first_type		first;
			second_type		second;
	};

	//////////////////////////
	// RELATIONAL OPERATORS //
	//////////////////////////
	// == operator
	template <class T1, class T2>
	bool	operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}
	// != operator
	template <class T1, class T2>
	bool	operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return !(lhs == rhs);
	}
	// < operator
	template <class T1, class T2>
	bool	operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return (lhs.first < rhs.first || (!(rhs.first < lhs.first) &&
					lhs.second < rhs.second));
	}
	// <= operator
	template <class T1, class T2>
	bool	operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return !(rhs < lhs);
	}
	// > operator
	template <class T1, class T2>
	bool	operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return (rhs < lhs);
	}
	// >= operator
	template <class T1, class T2>
	bool	operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return !(lhs < rhs);
	}

	template <class T1, class T2>
	ft::pair<T1, T2>	make_pair(T1 x, T2 y)
	{
		return (ft::pair<T1, T2>(x, y));
	}
}

#endif
