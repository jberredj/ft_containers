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
		return 1;
	} else {
		std::cout << "Test case testSize() passed" << std::endl;
		return 0;
	}
}
