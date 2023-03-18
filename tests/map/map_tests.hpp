#ifndef MAP_TESTS_HPP
# define MAP_TESTS_HPP
#include <map>
#include "map.hpp"
#include "pair.hpp"
#include "../namespace.hpp"

namespace ft {

	// This class is needed to keep Test function syntax easy.
	// GCC and Clang do not seem to like that I pass a class template expecting 3 arguments to my one argument tests 
	// functions templates. Even if two of them have default values.
	// This hack allows the use of the default values of Compare and Allocator, 
	// without making compilers losing their shit...
	template <class Key, class Value>
	class MapTest: public NAMESPACE::map<Key, Value> {

	};
}

int map_main(unsigned int seed);
#endif