#include <iostream>
#include <chrono>
#include <stack>

#define USING_STD
#ifdef USING_STD
# define NAMESPACE std
#else
# define NAMESPACE ft
#endif

typedef int (*test_func)(unsigned int);

int timeTest(const char* testName, test_func func, unsigned int seed) {
  std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();

  int result = (*func)(seed);

  std::chrono::time_point<std::chrono::high_resolution_clock> stop = std::chrono::high_resolution_clock::now();
  std::chrono::microseconds duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

  if (result == 0) {
	std::cout << testName << " passed in " << duration.count() << " microseconds" << std::endl;
  } else {
	std::cerr << testName << " failed with error code " << result << std::endl;
  }

  return result;
}

int testSize(unsigned int seed) {
	NAMESPACE::stack<int> s;
	if (s.size() != 0) {
		std::cerr << "testSize() failed: size() function should return 0" << std::endl;
		return 1;
	} else {
		std::cout << "testSize() passed" << std::endl;
		return 0;
	}
}

int testPush(unsigned int seed) {
	NAMESPACE::stack<int> s;
	srand(seed);
	int numInputs = rand() % 9901 + 100;
	int lastVal;
	for (int i = 0; i < numInputs; i++) {
		int val = rand();
		s.push(val);
		lastVal = val;
	}
	if (s.size() != numInputs || s.top() != lastVal) {
		std::cerr << "testPush() failed: size() function should return " << numInputs << " and top() function should return the last value pushed" << std::endl;
		return 1;
	} else {
		std::cout << "testPush() passed" << std::endl;
		return 0;
	}
}

int testPop(unsigned int seed) {
	NAMESPACE::stack<int> s;
	srand(seed);
	int numInputs = rand() % 9901 + 100;
	int lastVal;
	for (int i = 0; i < numInputs; i++) {
		int val = rand();
		s.push(val);
		lastVal = val;
	}
	s.pop();
	if (s.size() != numInputs - 1 || s.top() != lastVal) {
		std::cerr << "testPop() failed: size() function should return " << numInputs - 1 << " and top() function should return the second-to-last value pushed after pop()" << std::endl;
		return 1;
	} else {
		std::cout << "testPop() passed" << std::endl;
		return 0;
	}
}
