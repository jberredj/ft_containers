#ifndef RBT_TESTS_HPP
# define RBT_TESTS_HPP
#include "_rbt.hpp"

namespace ft {
	template <class T>
	class countAlloc: public std::allocator<T> {

	};
	// This class is needed to keep Test function syntax easy.
	// GCC and Clang do not seem to like that I pass a class template expecting 3 arguments to my one argument tests 
	// functions templates. Even if two of them have default values.
	// This hack allows the use of the default values of Compare and Allocator, 
	// without making compilers losing their shit...
	template <class T>
	class RBTTest: public RBT<T> {

	};
}
#endif