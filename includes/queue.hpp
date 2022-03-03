#ifndef QUEUE_HPP
# define QUEUE_HPP

# include <deque>			// deque is the default container

namespace ft
{
	template <class T, class Container = std::deque<T> >
	class queue
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
			explicit queue(const container_type &ctnr = container_type()) :
				c(ctnr)
			{
				return ;
			}
			// Copy constructor
			queue(queue const &x) :
				c(x.c)
			{
				return ;
			}
			////////////////
			// DESTRUCTOR //
			////////////////
			virtual ~queue()
			{
				return ;
			}
			/////////////////////////
			// ASSIGNMENT OVERLOAD //
			/////////////////////////
			queue			&operator=(const queue &other)
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
			// Front
			reference			front()
			{
				return this->c.front();
			}
			// Front (const)
			const_reference		front() const
			{
				return this->c.front();
			}
			// Back
			reference			back()
			{
				return this->c.back();
			}
			// Back (const)
			const_reference		back() const
			{
				return this->c.back();
			}

			///////////////
			// MODIFIERS //
			///////////////
			// Push
			void		push(const value_type &val)
			{
				this->c.push_back(val);
			}
			// Pop
			void		pop()
			{
				this->c.pop_front();
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
			friend bool		operator==(const queue<T1, Container1> &lhs,
									const queue<T1, Container1> &rhs);
			template <class T1, class Container1>
			friend bool		operator!=(const queue<T1, Container1> &lhs,
									const queue<T1, Container1> &rhs);
			template <class T1, class Container1>
			friend bool		operator<(const queue<T1, Container1> &lhs,
									const queue<T1, Container1> &rhs);
			template <class T1, class Container1>
			friend bool		operator<=(const queue<T1, Container1> &lhs,
									const queue<T1, Container1> &rhs);
			template <class T1, class Container1>
			friend bool		operator>(const queue<T1, Container1> &lhs,
									const queue<T1, Container1> &rhs);
			template <class T1, class Container1>
			friend bool		operator>=(const queue<T1, Container1> &lhs,
									const queue<T1, Container1> &rhs);
	};

	//////////////////////////
	// RELATIONAL OPERATORS //
	//////////////////////////
	template <class T, class Container>
	bool	operator==(const queue<T, Container> &lhs, const queue<T, Container> &rhs)
	{
		return (lhs.c == rhs.c);
	}
	template <class T, class Container>
	bool	operator!=(const queue<T, Container> &lhs, const queue<T, Container> &rhs)
	{
		return (lhs.c != rhs.c);
	}
	template <class T, class Container>
	bool	operator<(const queue<T, Container> &lhs, const queue<T, Container> &rhs)
	{
		return (lhs.c < rhs.c);
	}
	template <class T, class Container>
	bool	operator<=(const queue<T, Container> &lhs, const queue<T, Container> &rhs)
	{
		return (lhs.c <= rhs.c);
	}
	template <class T, class Container>
	bool	operator>(const queue<T, Container> &lhs, const queue<T, Container> &rhs)
	{
		return (lhs.c > rhs.c);
	}
	template <class T, class Container>
	bool	operator>=(const queue<T, Container> &lhs, const queue<T, Container> &rhs)
	{
		return (lhs.c >= rhs.c);
	}
}

#endif
