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
