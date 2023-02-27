#ifndef UTILS_HPP
# define UTILS_HPP
typedef int (*test_func)(unsigned int);

int	timeTest(const char* testName, test_func func, unsigned int seed);
#endif