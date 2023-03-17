#include "stack_tests.hpp"
#include "../randomValue.hpp"
#include "../utils.hpp"
#include "../MyClass.hpp"
#include "../namespace.hpp"
#include <exception>
#include <cstdlib>
#include <list>
#include <set>
#include <vector>
#include <algorithm>
#include <limits>

template <typename T>
int testStackPushPop(unsigned int seed, ft::StackTest<T> &testStack)
{
	std::srand(seed);
	int errorCount = 0;
	std::vector<T> expectedValue;

	// Test: Push random values onto the stack and pop them off
	int numIterations = randomValue<T>::getIteration();
	for (int i = 0; i < numIterations; i++)
	{
		T value = randomValue<T>::get();
		expectedValue.insert(expectedValue.begin(), value);
		testStack.push(value);
	}
	for (int i = 0; i < numIterations; i++)
	{
		if (!testStack.empty())
		{
			T actualValue = testStack.top();
			testStack.pop();
			if (actualValue != expectedValue[i])
			{
				std::cerr << "Error: expected value " << expectedValue[i] << " but got value " << actualValue << std::endl;
				errorCount++;
			}
		}
		else
		{
			std::cerr << "Error: stack is empty but expected value " << expectedValue[i] << std::endl;
			errorCount++;
		}
	}

	return errorCount;
}

template <typename T>
int testStackCopyAndSwap(unsigned int seed, ft::StackTest<T> &testStack)
{
	std::srand(seed);
	int errorCount = 0;

	// Test: Copy and swap the stack and check that the new stack has the same values as the original
	int numIterations = randomValue<T>::getIteration();
	for (int i = 0; i < numIterations; i++)
	{
		T value = randomValue<T>::get();
		testStack.push(value);
	}
	ft::StackTest<T> newStack(testStack);
	if (newStack != testStack)
	{
		std::cerr << "Error: copied stack does not have the same values as the original stack" << std::endl;
		errorCount++;
	}
	newStack = ft::StackTest<T>();
	newStack = testStack;
	if (newStack != testStack)
	{
		std::cerr << "Error: swapped stack does not have the same values as the original stack" << std::endl;
		errorCount++;
	}

	return errorCount;
}

template <typename T>
int testStackComparison(unsigned int seed, ft::StackTest<T> &testStack)
{
	std::srand(seed);
	int errorCount = 0;

	// Test: Compare two stacks
	ft::StackTest<T> equalStack(testStack);
	ft::StackTest<T> differentStack;
	for (size_t i = 0; i < randomValue<T>::getIteration(); i++)
	{
		T value = randomValue<T>::get();
		differentStack.push(value);
	}
	if (!(testStack == equalStack))
	{
		std::cerr << "Error: stack and equal stack are not equal" << std::endl;
		errorCount++;
	}
	if (testStack != equalStack || testStack == differentStack)
	{
		// check that operator!= is the opposite of operator==
		std::cerr << "Error: stack and equal stack are not equal or stack and different stack are equal" << std::endl;
		errorCount++;
	}
	if (testStack != testStack && differentStack != differentStack)
	{
		std::cerr << "Error: stack or different stack is not equal to itself" << std::endl;
		errorCount++;
	}
	if (testStack == differentStack && differentStack == testStack)
	{
		// check that operator!= is the opposite of operator==
		std::cerr << "Error: stack and different stack are equal" << std::endl;
		errorCount++;
	}

	return errorCount;
}

template <typename T>
int testStackModifiers(unsigned int seed, ft::StackTest<T> &testStack)
{
	std::srand(seed);
	int errorCount = 0;

	// Test: Clear the stack and check that it is empty
	int numIterations = randomValue<T>::getIteration();
	for (int i = 0; i < numIterations; i++)
	{
		T value = randomValue<T>::get();
		testStack.push(value);
	}
	while (!testStack.empty())
	{
		testStack.pop();
	}
	if (!testStack.empty())
	{
		std::cerr << "Error: stack is not empty after clear" << std::endl;
		errorCount++;
	}

	return errorCount;
}

template <typename T>
int testStackPerformance(unsigned int seed, ft::StackTest<T> &testStack)
{
	std::srand(seed);
	int errorCount = 0;

	// Test: Push a large number of elements onto the stack and then pop them off
	int numIterations = 100000;
	for (int i = 0; i < numIterations; i++)
	{
		T value = randomValue<T>::get();
		testStack.push(value);
	}
	for (int i = 0; i < numIterations; i++)
	{
		if (!testStack.empty())
		{
			testStack.pop();
		}
		else
		{
			std::cerr << "Error: stack is empty but expected " << numIterations - i << " elements remaining" << std::endl;
			errorCount++;
		}
	}

	return errorCount;
}

template <class T>
static int testAllStack(unsigned int seed)
{
	ft::StackTest<T> testMap;
	int errorCount = 0;
	errorCount += timeTest<ft::StackTest, T>("testStackPushPop", testStackPushPop<T>, testMap, seed);
	errorCount += timeTest<ft::StackTest, T>("testStackCopyAndSwap", testStackCopyAndSwap<T>, testMap, seed);
	errorCount += timeTest<ft::StackTest, T>("testStackComparison", testStackComparison<T>, testMap, seed);
	errorCount += timeTest<ft::StackTest, T>("testStackModifiers", testStackModifiers<T>, testMap, seed);
	errorCount += timeTest<ft::StackTest, T>("testStackPerformance", testStackPerformance<T>, testMap, seed);
	std::cout << std::endl;
	return errorCount;
}

#ifdef STANDALONE
#include <cstdlib>
int main(int ac, char *av[])
{
	if (ac != 2)
	{
		std::cerr << "Usage: " << av[0] << " seed" << std::endl;
		return 1;
	}
	unsigned int seed = atoi(av[1]);
#else
int rbt_main(unsigned int seed)
{
#endif
	std::cout << "testAllStack<int>" << std::endl;
	int errorCount = testAllStack<int>(seed);
	std::cout << "testAll<char>" << std::endl;
	errorCount = testAllStack<char>(seed);
	std::cout << "testAll<std::string>" << std::endl;
	errorCount = testAllStack<std::string>(seed);
	std::cout << "testAll<MyClass>" << std::endl;
	errorCount = testAllStack<MyClass>(seed);
	return errorCount;
}