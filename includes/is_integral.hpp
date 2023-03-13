#ifndef IS_INTEGRAL_HPP
#define IS_INTEGRAL_HPP
#include <uchar.h>

namespace ft
{
	template <class T, T v>
	struct integral_constant
	{
		static const T value = v;
		typedef T value_type;
		typedef integral_constant<T, v> type;
		operator T() { return v; }
	};

	template <class T>
	struct is_integral : public integral_constant<bool, false>
	{
		static const bool value = false;
		operator bool() { return value; }
	};

	template <>
	struct is_integral<bool> : public integral_constant<bool, true>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<char> : public integral_constant<bool, true>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<unsigned char> : public integral_constant<bool, true>
	{
		static const bool value = true;
	};

	// template <>
	// struct is_integral<char16_t> : public integral_constant<bool, true>
	// {
	// 	static const bool value = true;
	// };

	template <>
	struct is_integral<char32_t> : public integral_constant<bool, true> // it is apparently equivalent to char16_t, unsigned short, unsigned int
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<wchar_t> : public integral_constant<bool, true>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<short> : public integral_constant<bool, true>
	{
		static const bool value = true;
	};

	// template <>
	// struct is_integral<unsigned short> : public integral_constant<bool, true>
	// {
	// 	static const bool value = true;
	// };

	template <>
	struct is_integral<int> : public integral_constant<bool, true>
	{
		static const bool value = true;
	};

	// template <>
	// struct is_integral<unsigned int> : public integral_constant<bool, true>
	// {
	// 	static const bool value = true;
	// };

	template <>
	struct is_integral<long> : public integral_constant<bool, true>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<unsigned long> : public integral_constant<bool, true>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<long long> : public integral_constant<bool, true>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<unsigned long long> : public integral_constant<bool, true>
	{
		static const bool value = true;
	};
}

#endif