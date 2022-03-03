#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <cstddef>						// size_t, ptrdiff_t
#include <memory>						// allocator
#include <stdexcept>					// out_of_range exception
#include "RandomAccessIterator.hpp"		// RandomAccessIterator class
#include "ReverseIterator.hpp"			// ReverseIterator class
#include "iterator_traits.hpp"			// Iterator traits
#include "utils.hpp"					// Swap, lexicographical_compare

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class vector
	{
		//////////////////
		// MEMBER TYPES //
		//////////////////
		public:
			typedef T											value_type;
			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef RandomAccessIterator<T, T*, T&>				iterator;
			typedef RandomAccessIterator<T, const T*, const T&>	const_iterator;
			typedef ReverseIterator<iterator>					reverse_iterator;
			typedef ReverseIterator<const_iterator>				const_reverse_iterator;
			typedef std::ptrdiff_t								difference_type;
			typedef std::size_t									size_type;

		//////////////////////
		// MEMBER FUNCTIONS //
		//////////////////////
		public:
			//////////////////
			// CONSTRUCTORS //
			//////////////////
			// Default constructor
			explicit vector(const allocator_type &alloc = allocator_type())
				: _allocator(alloc), _elements(0), _size(0), _capacity(0)
			{
			}
			// Fill constructor
			explicit vector(size_type n, const value_type &val = value_type(),
					const allocator_type &alloc = allocator_type())
				: _allocator(alloc), _elements(0), _size(0), _capacity(0)
			{
				this->assign(n, val);
			}
			// Range constructor
			template <class InputIterator>
			vector(InputIterator first, InputIterator last,
					const allocator_type &alloc = allocator_type(),
					typename ft::iterator_traits<InputIterator>::iterator_category* = 0)
				: _allocator(alloc), _elements(0), _size(0), _capacity(0)
			{
				this->assign(first, last);
			}
			// Copy constructor
			vector(const vector &x)
				: _allocator(x._allocator), _elements(0), _size(0), _capacity(0)
			{
				this->_increaseCapacity(x.size(), true);
				*this = x;
			}
			////////////////
			// DESTRUCTOR //
			////////////////
			virtual ~vector()
			{
				this->_destroyElements(true);
			}

			/////////////////////////
			// ASSIGNMENT OVERLOAD //
			/////////////////////////
			vector	&operator=(const vector &x)
			{
				this->_destroyElements(this->_elements == NULL);
				this->_increaseCapacity(x.size(), true);
				for (size_t i = 0; i < x.size(); i++)
					this->push_back(x[i]);
				return *this;
			}

			///////////////
			// ITERATORS //
			///////////////
			// Begin
			iterator					begin()
			{
				return iterator(this->_elements);
			}
			// Begin (const)
			const_iterator				begin() const
			{
				return const_iterator(this->_elements);
			}
			// End
			iterator					end()
			{
				return iterator(&this->_elements[this->_size]);
			}
			// End (const)
			const_iterator				end() const
			{
				return const_iterator(&this->_elements[this->_size]);
			}
			// Reverse begin
			reverse_iterator			rbegin()
			{
				return reverse_iterator(&this->_elements[this->_size]);
			}
			// Reverse begin (const)
			const_reverse_iterator		rbegin() const
			{
				return const_reverse_iterator(&this->_elements[this->_size]);
			}
			// Reverse end
			reverse_iterator			rend()
			{
				return reverse_iterator(this->_elements);
			}
			// Reverse end (const)
			const_reverse_iterator		rend() const
			{
				return const_reverse_iterator(this->_elements);
			}
			
			//////////////
			// CAPACITY //
			//////////////
			// Size
			size_type		size() const
			{
				return this->_size;
			}
			// Max size
			size_type		max_size() const
			{
				return this->_allocator.max_size();
			}
			// Resize
			void			resize(size_type n, value_type val = value_type())
			{
				if (n < this->_size)
				{
					for (size_type i = this->_size; i > n; i--)
						this->_destroyElement(i);
				}
				else if (n > this->_size)
				{
					this->_increaseCapacity(n);
					for (size_type i = this->_size; i < n; i++)
						this->_addNewValue(i, val);
				}
			}
			// Capacity
			size_type		capacity() const
			{
				return this->_capacity;
			}
			// Empty
			bool			empty() const
			{
				return (this->_size == 0);
			}
			// Reserve
			void			reserve(size_type n)
			{
				this->_increaseCapacity(n, true);
			}

			////////////////////
			// ELEMENT ACCESS //
			////////////////////
			// Operator [] overload
			reference			operator[](size_type n)
			{
				return this->_elements[n];
			}
			// Operator [] overload (const)
			const_reference		operator[](size_type n) const
			{
				return this->_elements[n];
			}
			// At
			reference			at(size_type n)
			{
				if (n >= this->_size)
					throw std::out_of_range("vector");
				return this->_elements[n];
			}
			// At (const)
			const_reference		at(size_type n) const
			{
				if (n >= this->_size)
					throw std::out_of_range("vector");
				return this->_elements[n];
			}
			// Front
			reference			front()
			{
				return this->_elements[0];
			}
			// Front (const)
			const_reference		front() const
			{
				return this->_elements[0];
			}
			// Back
			reference			back()
			{
				return this->_elements[this->_size - 1];
			}
			// Back (const)
			const_reference		back() const
			{
				return this->_elements[this->_size - 1];
			}

			///////////////
			// MODIFIERS //
			///////////////
			// Assign (range)
			template <class InputIterator>
			void		assign(InputIterator first, InputIterator last,
					typename ft::iterator_traits<InputIterator>::iterator_category* = 0)
			{
				difference_type n = ft::distance(first, last);
				this->_destroyElements();
				this->_increaseCapacity(n, true);
				for (int i = 0 ; first != last; first++, i++)
					this->_addNewValue(i, *first);
			}
			// Assign (fill)
			void		assign(size_type n, const value_type &val)
			{
				this->_destroyElements();
				this->_increaseCapacity(n, true);
				for (size_type i = 0; i < n; i++)
					this->_addNewValue(i, val);
			}
			// Push back
			void		push_back(const value_type &val)
			{
				this->_increaseCapacity(this->_size + 1);
				this->_addNewValue(this->_size, val);
			}
			// Pop back
			void		pop_back()
			{
				this->_destroyElement(this->_size - 1);
			}
			// Insert (single element)
			iterator	insert(iterator position, const value_type &val)
			{
				difference_type		pos = ft::distance(this->begin(), position);

				this->_increaseCapacity(this->_size + 1);
				this->_moveElementsForward(pos, 1);
				this->_addNewValue(pos, val);
				return iterator(&this->_elements[pos]);
			}
			// Insert (fill)
			void		insert(iterator position, size_type n, const value_type &val)
			{
				difference_type		pos = ft::distance(this->begin(), position);

				this->_increaseCapacity(this->_size + n);
				this->_moveElementsForward(pos, n);
				for (size_type i = pos; i < pos + n; i++)
					this->_addNewValue(i, val);
			}
			// Insert (range)
			template <class InputIterator>
			void		insert(iterator position, InputIterator first, InputIterator last,
					typename ft::iterator_traits<InputIterator>::iterator_category* = 0)
			{
				difference_type		pos = ft::distance(this->begin(), position);
				difference_type		amount = ft::distance(first, last);

				this->_increaseCapacity(this->_size + amount);
				this->_moveElementsForward(pos, amount);
				for (size_type i = 0; first != last; first++, i++)
					this->_addNewValue(pos + i, *first);
			}
			// Erase (single element)
			iterator	erase(iterator position)
			{
				difference_type		pos = ft::distance(this->begin(), position);
				size_t				amountToMove = 1;
				size_t				elements = this->_size - pos;

				this->_destroyElement(pos);
				this->_moveElementsBackward(pos + amountToMove, elements, amountToMove);
				return position;
			}
			// Erase (range)
			iterator	erase(iterator first, iterator last)
			{
				iterator			begin = this->begin();
				difference_type		pos = ft::distance(begin, first);
				difference_type		amountToMove = ft::distance(first, last);
				difference_type		elements = ft::distance(last, this->end());
				iterator			ret = first;
				size_t				i = 0;

				while (first != last)
				{
					this->_destroyElement(pos + i);
					i++;
					first++;
				}
				this->_moveElementsBackward(pos + amountToMove, elements, amountToMove);
				return ret;
			}
			// Swap
			void		swap(vector &x)
			{
				ft::swap(this->_elements, x._elements);
				ft::swap(this->_size, x._size);
				ft::swap(this->_capacity, x._capacity);
			}
			// Clear
			void		clear()
			{
				this->_destroyElements();
			}
			///////////////
			// ALLOCATOR //
			///////////////
			// Get allocator
			allocator_type	get_allocator() const
			{
				return this->_allocator;
			}

		///////////////////////
		// PRIVATE VARIABLES //
		///////////////////////
		private:
			allocator_type	_allocator;
			T				*_elements;
			size_type		_size;
			size_type		_capacity;

		//////////////////////////////
		// PRIVATE MEMBER FUNCTIONS //
		//////////////////////////////
		private:
			// This function constructs and initializes a new element.
			void	_addNewValue(size_type index, const value_type &val)
			{
				this->_allocator.construct(&this->_elements[index], val);
				this->_size++;
			}
			// This function destroys all elements, but does not reset
			// the capacity. It deallocates if true is passed.
			void	_destroyElements(bool deallocate = false)
			{
				if (this->_elements == NULL)
					return ;
				size_t		amount;
				amount = this->_size;
				for (size_type i = 0; i < amount; i++)
					this->_destroyElement(i);
				if (deallocate)
					this->_allocator.deallocate(this->_elements, this->_capacity);
			}
			// This function destructs a single element, given the index,
			// using the allocator, but does not deallocate.
			void	_destroyElement(size_type index)
			{
				this->_allocator.destroy(&this->_elements[index]);
				this->_size--;
			}
			// This function will increase the allocated space for this vector.
			void	_increaseCapacity(size_type newCapacity, bool exact = false)
			{
				pointer		tmp;
				size_type	tmpSize;

				if (newCapacity <= this->_capacity)
					return ;
				if (!exact)
				{
					if (newCapacity != 1 && !(newCapacity >= this->_capacity * 2))
						newCapacity = this->_capacity * 2;
				}
				tmp = this->_allocator.allocate(newCapacity);
				if (this->_size != 0)
				{
					tmpSize = this->_size;
					for (size_type i = 0; i < this->_size; i++)
						this->_allocator.construct(&tmp[i], this->_elements[i]);
					this->_destroyElements(true);
					this->_size = tmpSize;
				}
				else
					this->_destroyElements(true);
				this->_elements = tmp;
				this->_capacity = newCapacity;
			}
			// This function will move elements in the array, starting at index
			// startIndex, forward by a specified amount of spaces.
			void	_moveElementsForward(size_type startIndex, size_type amount)
			{
				for (size_type i = this->_size - 1; i > startIndex - 1; i--)
				{
					this->_addNewValue(i + amount, this->_elements[i]);
					this->_destroyElement(i);
				}
			}
			// This function will move elements in the array, starting at index
			// startIndex, backward by a specified amount of spaces.
			void	_moveElementsBackward(size_type startIndex, size_type elements, size_type amountToMove)
			{
				for (size_type i = startIndex; i < startIndex + elements; i++)
				{
					this->_addNewValue(i - amountToMove, this->_elements[i]);
					this->_destroyElement(i);
				}
			}
	};

	//////////////////////////
	// RELATIONAL OPERATORS //
	//////////////////////////
	// == operator
	template <class T, class Alloc>
	bool		operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		for (typename vector<T>::size_type i = 0; i < lhs.size(); i++)
			if (lhs[i] != rhs[i])
				return false;
		return true;
	}
	// != operator
	template <class T, class Alloc>
	bool		operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return !(lhs == rhs);
	}
	// < operator
	template <class T, class Alloc>
	bool		operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	// <= operator
	template <class T, class Alloc>
	bool		operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return !(rhs < lhs);
	}
	// > operator
	template <class T, class Alloc>
	bool		operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (rhs < lhs);
	}
	// >= operator
	template <class T, class Alloc>
	bool		operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return !(lhs < rhs);
	}
	// Swap
	template <class T, class Alloc>
	void		swap(vector<T, Alloc> &x, vector<T, Alloc> &y)
	{
		x.swap(y);
	}
}

#endif
