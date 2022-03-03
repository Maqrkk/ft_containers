#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"			// vector is the default container

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{
		//////////////////
		// MEMBER TYPES //
		//////////////////
		public:
			typedef T										value_type;
			typedef Container								container_type;
			typedef typename Container::size_type			size_type;
			typedef typename Container::reference			reference;
			typedef typename Container::const_reference		const_reference;

		//////////////////////
		// MEMBER FUNCTIONS //
		//////////////////////
		public:
			//////////////////
			// CONSTRUCTORS //
			//////////////////
			// Default constructor
			explicit stack(const container_type &ctnr = container_type()) :
				c(ctnr)
			{
				return ;
			}
			// Copy constructor
			stack(stack const &x) :
				c(x.c)
			{
				return ;
			}
			////////////////
			// DESTRUCTOR //
			////////////////
			virtual ~stack()
			{
				return ;
			}
			/////////////////////////
			// ASSIGNMENT OVERLOAD //
			/////////////////////////
			stack		&operator=(const stack &other)
			{
				this->c = other.c;
			}

			//////////////
			// CAPACITY //
			//////////////
			// Empty
			bool		empty() const
			{
				return this->c.empty();
			}
			// Size
			size_type	size() const
			{
				return this->c.size();
			}

			////////////////////
			// ELEMENT ACCESS //
			////////////////////
			// Top
			reference			top()
			{
				return this->c.back();
			}
			// Top (const)
			const_reference		top() const
			{
				return this->c.back();
			}

			///////////////
			// MODIFIERS //
			///////////////
			// Push
			void				push(const value_type &val)
			{
				this->c.push_back(val);
			}
			// Pop
			void				pop()
			{
				this->c.pop_back();
			}

		/////////////////////////
		// PROTECTED VARIABLES //
		/////////////////////////
		protected:
			container_type		c;

		/////////////////////////////////////////////
		// RELATIONAL OPERATOR FRIEND DECLARATIONS //
		/////////////////////////////////////////////
		public:
			template <class T1, class Container1>
			friend bool		operator==(const stack<T1, Container1> &lhs,
									const stack<T1, Container1> &rhs);
			template <class T1, class Container1>
			friend bool		operator!=(const stack<T1, Container1> &lhs,
									const stack<T1, Container1> &rhs);
			template <class T1, class Container1>
			friend bool		operator<(const stack<T1, Container1> &lhs,
									const stack<T1, Container1> &rhs);
			template <class T1, class Container1>
			friend bool		operator<=(const stack<T1, Container1> &lhs,
									const stack<T1, Container1> &rhs);
			template <class T1, class Container1>
			friend bool		operator>(const stack<T1, Container1> &lhs,
									const stack<T1, Container1> &rhs);
			template <class T1, class Container1>
			friend bool		operator>=(const stack<T1, Container1> &lhs,
									const stack<T1, Container1> &rhs);
	};

	//////////////////////////
	// RELATIONAL OPERATORS //
	//////////////////////////
	template <class T, class Container>
	bool	operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return (lhs.c == rhs.c);
	}
	template <class T, class Container>
	bool	operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return (lhs.c != rhs.c);
	}
	template <class T, class Container>
	bool	operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return (lhs.c < rhs.c);
	}
	template <class T, class Container>
	bool	operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return (lhs.c <= rhs.c);
	}
	template <class T, class Container>
	bool	operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return (lhs.c > rhs.c);
	}
	template <class T, class Container>
	bool	operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return (lhs.c >= rhs.c);
	}
}

#endif
