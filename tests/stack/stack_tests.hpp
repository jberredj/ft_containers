#ifndef STACK_TESTS_HPP
# define STACK_TESTS_HPP
#include <stack>
#include "stack.hpp"
#include "../namespace.hpp"

namespace ft {

	template <class T>
	class StackTest: public NAMESPACE::stack<T> {

	};
}

int stack_main(unsigned int seed);

#endif