#include "utils.hpp"
#include <ctime>
#include <iostream>

int timeTest(const char* testName, test_func func, unsigned int seed) {
  std::clock_t start_time = std::clock();
  int result = 0;
  try {
    result = (*func)(seed);
  }
  catch (...) {
    std::cerr << testName << " failed and thrown an exception " << std::endl;
    return -1;
  }
  std::clock_t end_time = std::clock();

  double duration = (end_time - start_time) / (double)CLOCKS_PER_SEC * 1000;
  if (result == 0) 
	  std::cout << testName << " passed in " << duration << " milliseconds" << std::endl;
  else 
	  std::cerr << testName << " failed with error code " << result << std::endl;
  return result;
}