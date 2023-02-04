#include <iostream>
#include <stack>
#include <cstdlib>
#include <ctime>

#define USING_STD
#ifdef USING_STD
# define NAMESPACE std
#else
# define NAMESPACE ft
#endif
#ifndef INNERCONTAINER
# define INNERCONTAINER std::deque
#endif

typedef int (*test_func)(unsigned int);

int timeTest(const char* testName, test_func func, unsigned int seed) {
  std::clock_t start_time = std::clock();
  int result = (*func)(seed);
  std::clock_t end_time = std::clock();

  double duration = (end_time - start_time) / (double)CLOCKS_PER_SEC * 1000;
  if (result == 0) 
	std::cout << testName << " passed in " << duration << " milliseconds" << std::endl;
  else 
	std::cerr << testName << " failed with error code " << result << std::endl;
  return result;
}

int testSize(unsigned int seed) {
	(void)seed;
	NAMESPACE::stack<int, INNERCONTAINER<int> > s;
	if (s.size() != 0) {
		std::cerr << "testSize() failed: size() function should return 0" << std::endl;
		return 1;
	}
	std::cout << "testSize() passed" << std::endl;
	return 0;
}

int testPush(unsigned int seed) {
	NAMESPACE::stack<int, INNERCONTAINER<int> > s;
	srand(seed);
	unsigned int numInputs = rand() % 9901 + 100;
	int lastVal;
	for (unsigned int i = 0; i < numInputs; i++) {
		int val = rand();
		s.push(val);
		lastVal = val;
	}

	if (s.size() != numInputs || s.top() != lastVal) {
		std::cerr << "testPush() failed: size() function should return " << numInputs << " and top() function should return the last value pushed" << std::endl;
		return 1;
	} 
	std::cout << "testPush() passed" << std::endl;
	return 0;
}

int testPop(unsigned int seed) {
	NAMESPACE::stack<int, INNERCONTAINER<int> > s;
	std::stack<int, INNERCONTAINER<int> > control;
	srand(seed);
	int numInputs = rand() % 9901 + 100;
	int val = 0;
	for (int i = 0; i < numInputs; i++) {
		val = rand();
		s.push(val);
		control.push(val);
	}

	control.pop();
	int errorCount = 0;
	for (int i = 0; i < numInputs; i++) {
		s.pop();
		if (i < numInputs - 1 && s.top() != control.top()) {
			std::cerr << "Error: Expected popped value " << control.top() << ", but got " << s.top() << std::endl;
			errorCount++;
		}
		control.pop();
	}
	return errorCount;
}

int testEmpty(unsigned int seed) {
	(void)seed;
	NAMESPACE::stack<int, INNERCONTAINER<int> > s;
	if (!s.empty()) {
		std::cerr << "testEmpty() failed: empty() function should return true" << std::endl;
		return 1;
	}
	std::cout << "testEmpty() 1 passed" << std::endl;

	s.push(10);
	if (s.empty()) {
		std::cerr << "testEmpty() failed: empty() function should return false after push()" << std::endl;
		return 1;
	}
	std::cout << "testEmpty() 2 passed" << std::endl;

	s.pop();
	if (!s.empty()) {
		std::cerr << "testEmpty() failed: empty() function should return true after pop()" << std::endl;
		return 1;
	}
	std::cout << "testEmpty() 3 passed" << std::endl;
	return 0;
}

int testAll(unsigned int seed) {
	int errorCount = 0;
	errorCount += timeTest("testSize", testSize, seed);
	errorCount += timeTest("testPush", testPush, seed);
	errorCount += timeTest("testPop", testPop, seed);
	errorCount += timeTest("testEmpty", testEmpty, seed);
	if (errorCount == 0) 
		std::cout << "All tests passed" << std::endl;
	else
		std::cerr << "Total number of test failures: " << errorCount << std::endl;
	return errorCount;
}

int main(int ac, char* av[]) {
	if (ac != 2) {
		std::cerr << "Usage: " << av[0] << " seed" << std::endl;
		return 1;
	}
	unsigned int seed = atoi(av[1]);
	int errorCount = testAll(seed);
	return errorCount;
}