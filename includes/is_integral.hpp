#ifndef IS_INTEGRAL_HPP
# define IS_INTEGRAL_HPP

# include <cstdint>				// Type declarations for integral types

namespace ft
{
	// Base struct that will be used. It returns false.
	template <class T>
	struct is_integral
	{
		typedef bool		value_type;
		static const bool	value = false;
	};
	// Specializations that are all actual integrals, these return true.
	template <>
	struct is_integral<bool>
	{
		static const bool	value = true;
	};
	template <>
	struct is_integral<char>
	{
		static const bool	value = true;
	};
	template <>
	struct is_integral<char16_t>
	{
		static const bool	value = true;
	};
	template <>
	struct is_integral<char32_t>
	{
		static const bool	value = true;
	};
	template <>
	struct is_integral<wchar_t>
	{
		static const bool	value = true;
	};
	template <>
	struct is_integral<signed char>
	{
		static const bool	value = true;
	};
	template <>
	struct is_integral<short int>
	{
		static const bool	value = true;
	};
	template <>
	struct is_integral<int>
	{
		static const bool	value = true;
	};
	template <>
	struct is_integral<long int>
	{
		static const bool	value = true;
	};
	template <>
	struct is_integral<unsigned char>
	{
		static const bool	value = true;
	};
	template <>
	struct is_integral<unsigned short int>
	{
		static const bool	value = true;
	};
	template <>
	struct is_integral<unsigned int>
	{
		static const bool	value = true;
	};
	template <>
	struct is_integral<unsigned long int>
	{
		static const bool	value = true;
	};
}

#endif
