#ifndef UTILS_HPP
# define UTILS_HPP
# include <ctime>
# include <iostream>
// typedef int (*test_func)(unsigned int);

// int	timeTest(const char* testName, test_func func, unsigned int seed);

template <template <typename> class Cntr, class T>
int	timeTest(const char* testName, int (*f)(unsigned int, Cntr<T>&), Cntr<T>& cntr, unsigned int seed) {
  std::clock_t start_time = std::clock();
  int result = 0;
  try {
    result = (*f)(seed, cntr);
  }
  catch (const std::exception &e) {
    std::cerr << testName << " failed and thrown an exception: " << e.what() << std::endl;
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

template <template <class, class> class Cntr, class Key, class Value>
int	timeTest(const char* testName, int (*f)(unsigned int, Cntr<Key, Value>&), Cntr<Key, Value>& cntr, unsigned int seed) {
  std::clock_t start_time = std::clock();
  int result = 0;
  try {
    result = (*f)(seed, cntr);
  }
  catch (const std::exception &e) {
    std::cerr << testName << " failed and thrown an exception: " << e.what() << std::endl;
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

#endif