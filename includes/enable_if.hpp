#ifndef ENABLE_IF_HPP
# define ENABLE_IF_HP

namespace ft {
	// once again cppreference carries https://en.cppreference.com/w/cpp/types/enable_if
	template <bool, typename T = void>
	struct enable_if {};

	template <typename T>
	struct enable_if<true, T>  { typedef T type; };
};
#endif