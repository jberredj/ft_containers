#ifndef RANDOMVALUE_HPP
# define RANDOMVALUE_HPP
# include <cstdlib>

template <class T>
struct randomValue {
	static T		get(void)
	{
		return T();
	}

	static size_t	getIteration(void) {
		return static_cast<size_t>(rand()) % 9901 + 100;
	}
};
#endif