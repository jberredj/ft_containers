#include "vector_tests.hpp"
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
#include <memory>

template <class T, template <typename> class Alloc>
int testConstructorAndAssignment(unsigned int seed, NAMESPACE::vector<T, Alloc<T> > &testVector)
{
	(void)testVector;
	srand(seed);
	int errorCount = 0;

	// Test default constructor
	NAMESPACE::vector<T, Alloc<T> > defaultVector;
	if (defaultVector.size() != 0 || defaultVector.capacity() != 0)
	{
		std::cerr << "Error: default constructor failed" << std::endl;
		errorCount++;
	}

	// Test constructor with size argument
	size_t size = randomValue<size_t>::get() % 100;
	NAMESPACE::vector<T, Alloc<T> > sizeVector(size);
	if (sizeVector.size() != size || sizeVector.capacity() < size)
	{
		std::cerr << "Error: constructor with size argument failed" << std::endl;
		errorCount++;
	}

	// Test constructor with size and value arguments
	T value = randomValue<T>::get();
	NAMESPACE::vector<T, Alloc<T> > valueVector(size, value);
	if (valueVector.size() != size || valueVector.capacity() < size)
	{
		std::cerr << "Error: constructor with size and value arguments failed" << std::endl;
		errorCount++;
	}
	for (size_t i = 0; i < size; i++)
	{
		if (valueVector[i] != value)
		{
			std::cerr << "Error: constructor with size and value arguments failed to set values correctly" << std::endl;
			errorCount++;
			break;
		}
	}

	// Test copy constructor
	NAMESPACE::vector<T, Alloc<T> > copyVector(valueVector);
	if (copyVector.size() != size || copyVector.capacity() < size)
	{
		std::cerr << "Error: copy constructor failed" << std::endl;
		errorCount++;
	}
	for (size_t i = 0; i < size; i++)
	{
		if (copyVector[i] != valueVector[i])
		{
			std::cerr << "Error: copy constructor failed to copy values correctly" << std::endl;
			errorCount++;
			break;
		}
	}

	// Test constructor with range
	NAMESPACE::vector<T, Alloc<T> > rangeVector(valueVector.begin(), valueVector.end());
	if (rangeVector.size() != size || rangeVector.capacity() < size)
	{
		std::cerr << "Error: constructor with range failed" << std::endl;
		errorCount++;
	}
	for (size_t i = 0; i < size; i++)
	{
		if (rangeVector[i] != valueVector[i])
		{
			std::cerr << "Error: constructor with range failed to copy values correctly" << std::endl;
			errorCount++;
			break;
		}
	}

	// Test assignment operator
	NAMESPACE::vector<T, Alloc<T> > assignVector;
	assignVector = valueVector;
	if (assignVector.size() != size || assignVector.capacity() < size)
	{
		std::cerr << "Error: assignment operator failed" << std::endl;
		errorCount++;
	}
	for (size_t i = 0; i < size; i++)
	{
		if (assignVector[i] != valueVector[i])
		{
			std::cerr << "Error: assignment operator failed to copy values correctly" << std::endl;
			errorCount++;
			break;
		}
	}

	return errorCount;
}

template <class T, template <typename> class Alloc>
int testSize(unsigned int seed, NAMESPACE::vector<T, Alloc<T> > &testVector)
{
	srand(seed);
	int errorCount = 0;

	// Test: empty vector
	if (testVector.size() != 0)
	{
		std::cerr << "Error: size() is not zero for empty vector" << std::endl;
		errorCount++;
	}

	// Test: vector with random size
	size_t expectedSize = randomValue<T>::getIteration();
	for (size_t i = 0; i < expectedSize; i++)
	{
		testVector.push_back(randomValue<T>::get());
	}
	if (testVector.size() != expectedSize)
	{
		std::cerr << "Error: size() is incorrect after adding " << expectedSize << " elements" << std::endl;
		errorCount++;
	}

	// Test: clear vector
	testVector.clear();
	if (testVector.size() != 0)
	{
		std::cerr << "Error: size() is not zero after clearing vector" << std::endl;
		errorCount++;
	}

	// Test: resize vector
	expectedSize = randomValue<T>::getIteration();
	testVector.resize(expectedSize);
	if (testVector.size() != expectedSize)
	{
		std::cerr << "Error: size() is incorrect after resizing to " << expectedSize << std::endl;
		errorCount++;
	}

	return errorCount;
}

template <class T, template <typename> class Alloc>
int testMaxSize(unsigned int seed, NAMESPACE::vector<T, Alloc<T> > &testVector)
{
	srand(seed);
	int errorCount = 0;

	// Test: max_size()
	size_t maxSize = testVector.max_size();
	if (maxSize == 0)
	{
		std::cerr << "Error: max_size() returned 0" << std::endl;
		errorCount++;
	}

	return errorCount;
}

template <class T, template <typename> class Alloc>
int testResize(unsigned int seed, NAMESPACE::vector<T, Alloc<T> > &testVectorIGNORE)
{
	srand(seed);
	(void)testVectorIGNORE;
	int errorCount = 0;
	const size_t baseNumIt = randomValue<int>::getIteration();
	const size_t numIterations = std::max(baseNumIt, static_cast<size_t>(2));
	const T val = randomValue<T>::get();
	{
		NAMESPACE::vector<T, Alloc<T> > testVector;
		const size_t initialSize = testVector.size();

		testVector.assign(initialSize, T());

		// Test resizing to a smaller size
		for (size_t i = 0; i < numIterations; i++)
		{
			const size_t newSize = std::abs(randomValue<int>::get()) % (testVector.size() + 1);
			testVector.resize(newSize, val);
			if (testVector.size() != newSize)
			{
				std::cerr << "Error: resize() with smaller size did not set correct size" << std::endl;
				errorCount++;
			}
			for (typename NAMESPACE::vector<T, Alloc<T> >::size_type j = 0; j < newSize; j++)
			{
				if (testVector[j] != val)
				{
					std::cerr << "Error: resize() with smaller size did not set correct value at index " << j << std::endl;
					errorCount++;
				}
			}
		}
	}

	NAMESPACE::vector<T, Alloc<T> > testVector;
	const size_t initialSize = testVector.size();
	// Test resizing to a larger size
	for (size_t i = 0; i < numIterations; i++)
	{
		const size_t newSize = testVector.size() + randomValue<int>::get() % (numIterations - testVector.size());
		testVector.resize(newSize, val);
		if (testVector.size() != newSize)
		{
			std::cerr << "Error: resize() with larger size did not set correct size" << std::endl;
			errorCount++;
		}
		for (typename NAMESPACE::vector<T, Alloc<T> >::size_type j = 0; j < initialSize; j++)
		{
			if (testVector[j] != T())
			{
				std::cerr << "Error: resize() with larger size modified value at index " << j << std::endl;
				errorCount++;
			}
		}
		for (typename NAMESPACE::vector<T, Alloc<T> >::size_type j = initialSize; j < newSize; j++)
		{
			if (testVector[j] != val)
			{
				std::cerr << "Error: resize() with larger size did not set correct value at index " << j << std::endl;
				errorCount++;
			}
		}
	}

	return errorCount;
}

template <class T, template <typename> class Alloc>
int testCapacity(unsigned int seed, NAMESPACE::vector<T, Alloc<T> > &testVector)
{
	srand(seed);
	int errorCount = 0;
	size_t numIteration = randomValue<T>::getIteration();

	NAMESPACE::vector<T, Alloc<T> > emptyVector;
	// Test: capacity() for an empty vector
	if (emptyVector.capacity() != 0)
	{
		std::cerr << "Error: capacity() returned incorrect value for empty vector" << std::endl;
		errorCount++;
	}

	// Test: capacity() for a non-empty vector
	for (size_t i = 0; i < numIteration; i++)
	{
		T value = randomValue<T>::get();
		testVector.push_back(value);
		if (testVector.capacity() < testVector.size())
		{
			std::cerr << "Error: capacity() returned incorrect value for non-empty vector" << std::endl;
			errorCount++;
		}
	}

	// Test: reserve() with a smaller capacity
	NAMESPACE::vector<T, Alloc<T> > smallerVector;
	smallerVector.reserve(5);
	if (smallerVector.capacity() != 5)
	{
		std::cerr << "Error: reserve() did not set capacity to the specified value" << std::endl;
		errorCount++;
	}

	// Test: reserve() with a larger capacity
	testVector.clear();
	testVector.reserve(10);
	if (testVector.capacity() < 10)
	{
		std::cerr << "Error: reserve() did not set capacity to the specified value" << std::endl;
		errorCount++;
	}

	return errorCount;
}

template <class T, template <typename> class Alloc>
int testEmpty(unsigned int seed, NAMESPACE::vector<T, Alloc<T> > &testVector)
{
	srand(seed);
	testVector.push_back(T());
	int errorCount = 0;
	if (testVector.empty())
	{
		std::cerr << "Error: empty() returned true on a non-empty vector." << std::endl;
		errorCount++;
	}

	NAMESPACE::vector<T, Alloc<T> > emptyVector;
	if (!emptyVector.empty())
	{
		std::cerr << "Error: empty() returned false on an empty vector." << std::endl;
		errorCount++;
	}

	return errorCount;
}

template <class T, template <typename> class Alloc>
int testPushBack(unsigned int seed, NAMESPACE::vector<T, Alloc<T> > &testVector)
{
	srand(seed);
	int errorCount = 0;
	size_t numIteration = randomValue<T>::getIteration();

	testVector.clear();
	std::vector<T> expectedVector;
	for (size_t i = 0; i < numIteration; i++)
	{
		T value = randomValue<T>::get();
		expectedVector.push_back(value);
		testVector.push_back(value);
		if (testVector.size() != expectedVector.size() || testVector.back() != expectedVector.back())
		{
			std::cerr << "Error: push_back() failed to insert value " << value << std::endl;
			errorCount++;
		}
	}

	return errorCount;
}

template <class T, template <typename> class Alloc>
int testPopBack(unsigned int seed, NAMESPACE::vector<T, Alloc<T> > &testVector)
{
	srand(seed);
	int errorCount = 0;
	size_t numIteration = randomValue<T>::getIteration();
	testVector.clear();

	std::vector<T> expectedVector;
	for (size_t i = 0; i < numIteration; i++)
	{
		T value = randomValue<T>::get();
		expectedVector.push_back(value);
		testVector.push_back(value);
	}

	while (!testVector.empty())
	{
		expectedVector.pop_back();
		testVector.pop_back();
		if (testVector.size() != expectedVector.size() || (testVector.empty() && !expectedVector.empty()) ||
			(!testVector.empty() && testVector.back() != expectedVector.back()))
		{
			std::cerr << "Error: pop_back() failed to remove value " << expectedVector.back() << std::endl;
			errorCount++;
		}
	}

	return errorCount;
}

template <class T, template <typename> class Alloc>
int testFront(unsigned int seed, NAMESPACE::vector<T, Alloc<T> > &testVector)
{
	srand(seed);
	int errorCount = 0;

	if (testVector.empty())
	{
		testVector.push_back(T());
	}

	// Test: front() on non-empty vector
	size_t numIterations = randomValue<T>::getIteration();
	for (size_t i = 0; i < numIterations; i++)
	{
		T val = randomValue<T>::get();
		testVector.push_back(val);
		if (testVector.front() != testVector[0])
		{
			std::cerr << "Error: front() returned incorrect value" << std::endl;
			errorCount++;
		}
	}

	return errorCount;
}

template <class T, template <typename> class Alloc>
int testBack(unsigned int seed, NAMESPACE::vector<T, Alloc<T> > &testVector)
{
	srand(seed);
	int errorCount = 0;

	if (testVector.empty())
	{
		testVector.push_back(T());
	}

	// Test: back() on non-empty vector
	size_t numIterations = randomValue<T>::getIteration();
	for (size_t i = 0; i < numIterations; i++)
	{
		T val = randomValue<T>::get();
		testVector.push_back(val);
		if (testVector.back() != val)
		{
			std::cerr << "Error: back() returned incorrect value" << std::endl;
			errorCount++;
		}
	}

	return errorCount;
}

template <class T, template <typename> class Alloc>
int testInsert(unsigned int seed, NAMESPACE::vector<T, Alloc<T> > &testVector)
{
	srand(seed);
	int errorCount = 0;
	testVector.clear();

	// Test: Insert elements using insert() and check size and content
	size_t numIteration = randomValue<T>::getIteration();
	NAMESPACE::vector<T, Alloc<T> > refVector;
	for (size_t i = 0; i < numIteration; i++)
	{
		T value = randomValue<T>::get();
		size_t index = refVector.empty() ? 0 : (rand() % refVector.size());
		testVector.insert(testVector.begin() + index, value);
		refVector.insert(refVector.begin() + index, value);
		if (testVector.size() != refVector.size())
		{
			std::cerr << "Error: vector size after insert() does not match reference size (" << testVector.size() << " != " << refVector.size() << ")" << std::endl;
			errorCount++;
		}
		if (testVector != refVector)
		{
			std::cerr << "Error: vector content after insert() does not match reference content" << std::endl;
			errorCount++;
		}
	}

	// Test: Insert n elements using insert() and check size and content
	size_t numInsert = 1 + rand() % (refVector.size() / 2);
	size_t index = testVector.empty() ? 0 : (rand() % testVector.size());
	typename NAMESPACE::vector<T, Alloc<T> >::iterator it = testVector.begin() + index;
	typename NAMESPACE::vector<T, Alloc<T> >::iterator refIt = refVector.begin();
	size_t refInsertStart = refVector.empty() ? 0 : (randomValue<T>::getIteration() % refVector.size());
	size_t refInsertEnd = std::min(refInsertStart + numInsert, refVector.size());

	NAMESPACE::vector<T, Alloc<T> > tempRef(refIt + refInsertStart, refIt + refInsertEnd);
	testVector.insert(it, tempRef.begin(), tempRef.end());
	refVector.insert(refVector.begin() + index, tempRef.begin(), tempRef.end());

	if (testVector.size() != refVector.size())
	{
		std::cerr << "Error: vector size after insert() with count does not match reference size (" << testVector.size() << " != " << refVector.size() << ")" << std::endl;
		errorCount++;
	}
	if (testVector != refVector)
	{
		std::cerr << "Error: vector content after insert() with count does not match reference content" << std::endl;
		for (size_t i = 0; i < testVector.size(); ++i)
		{
			if (testVector[i] != refVector[i])
			{
				std::cerr << "Mismatch at index " << i << ": testVector[" << i << "] = " << testVector[i] << ", refVector[" << i << "] = " << refVector[i] << std::endl;
			}
		}
		errorCount++;
	}

	return errorCount;
}

template <class T, template <typename> class Alloc>
int testSwap(unsigned int seed, NAMESPACE::vector<T, Alloc<T> > &testVector)
{
	srand(seed);
	int errorCount = 0;

	const int numIterations = randomValue<int>::getIteration();

	for (int i = 0; i < numIterations; i++)
	{
		NAMESPACE::vector<T, Alloc<T> > otherVector(randomValue<int>::getIteration(), randomValue<T>::get());
		const size_t oldSize = testVector.size();
		const size_t otherSize = otherVector.size();

		NAMESPACE::vector<T, Alloc<T> > originalTestVector = testVector;	  // Save the original testVector
		NAMESPACE::vector<T, Alloc<T> > originalOtherVector = otherVector; // Save the original otherVector

		testVector.swap(otherVector);

		if (testVector.size() != otherSize || otherVector.size() != oldSize)
		{
			std::cerr << "Error: swap() did not properly swap the sizes of the vectors." << std::endl;
			errorCount++;
		}

		for (size_t j = 0; j < testVector.size(); j++)
		{
			if (testVector[j] != originalOtherVector[j])
			{
				std::cerr << "Error: swap() did not properly swap the elements of the vectors." << std::endl;
				errorCount++;
				break;
			}
		}

		for (size_t j = 0; j < otherVector.size(); j++)
		{
			if (otherVector[j] != originalTestVector[j])
			{
				std::cerr << "Error: swap() did not properly swap the elements of the vectors." << std::endl;
				errorCount++;
				break;
			}
		}
	}

	return errorCount;
}

template <class T, template <typename> class Alloc>
int testClear(unsigned int seed, NAMESPACE::vector<T, Alloc<T> > &testVector)
{
	srand(seed);
	int errorCount = 0;

	// Test: clear() on non-empty vector
	size_t numIterations = randomValue<size_t>::getIteration();
	for (size_t i = 0; i < numIterations; i++)
	{
		size_t sizeBeforeClear = testVector.size();
		if (sizeBeforeClear == 0)
		{
			continue; // Skip this test if the vector is empty
		}
		testVector.clear();
		if (!testVector.empty())
		{
			std::cerr << "Error: clear() did not empty the vector" << std::endl;
			errorCount++;
		}
		if (testVector.size() != 0)
		{
			std::cerr << "Error: clear() did not update the size of the vector" << std::endl;
			errorCount++;
		}
	}

	// Test: clear() on empty vector
	testVector.clear();
	if (!testVector.empty())
	{
		std::cerr << "Error: clear() did not empty the vector" << std::endl;
		errorCount++;
	}
	if (testVector.size() != 0)
	{
		std::cerr << "Error: clear() did not update the size of the vector" << std::endl;
		errorCount++;
	}

	return errorCount;
}

template <class T, template <typename> class Alloc>
int testIterator(unsigned int seed, NAMESPACE::vector<T, Alloc<T> > &testVector)
{
	srand(seed);
	int errorCount = 0;

	// Test: iterator on empty vector
	{
		typename NAMESPACE::vector<T, Alloc<T> >::iterator it = testVector.begin();
		if (it != testVector.end())
		{
			std::cerr << "Error: iterator on empty vector does not point to end()" << std::endl;
			errorCount++;
		}
	}

	// Test: forward iteration
	{
		std::vector<T> expected(testVector.begin(), testVector.end());
		typename std::vector<T>::iterator it = expected.begin();
		for (typename NAMESPACE::vector<T, Alloc<T> >::iterator vit = testVector.begin(); vit != testVector.end(); ++vit)
		{
			if (*it != *vit)
			{
				std::cerr << "Error: forward iteration returned incorrect value (" << *vit << " instead of " << *it << ")" << std::endl;
				errorCount++;
			}
			++it;
		}
	}

	// Test: reverse iteration
	{
		std::vector<T> expected(testVector.rbegin(), testVector.rend());
		typename std::vector<T>::iterator it = expected.begin();
		for (typename NAMESPACE::vector<T, Alloc<T> >::reverse_iterator vit = testVector.rbegin(); vit != testVector.rend(); ++vit)
		{
			if (*it != *vit)
			{
				std::cerr << "Error: reverse iteration returned incorrect value (" << *vit << " instead of " << *it << ")" << std::endl;
				errorCount++;
			}
			++it;
		}
	}

	// Test: const iterator on empty vector
	{
		typename NAMESPACE::vector<T, Alloc<T> >::const_iterator it = testVector.begin();
		if (it != testVector.end())
		{
			std::cerr << "Error: const iterator on empty vector does not point to end()" << std::endl;
			errorCount++;
		}
	}

	// Test: const forward iteration
	{
		std::vector<T> expected(testVector.begin(), testVector.end());
		typename std::vector<T>::iterator it = expected.begin();
		for (typename NAMESPACE::vector<T, Alloc<T> >::const_iterator vit = testVector.begin(); vit != testVector.end(); ++vit)
		{
			if (*it != *vit)
			{
				std::cerr << "Error: const forward iteration returned incorrect value (" << *vit << " instead of " << *it << ")" << std::endl;
				errorCount++;
			}
			++it;
		}
	}

	// Test: const reverse iteration
	{
		std::vector<T> expected(testVector.rbegin(), testVector.rend());
		typename std::vector<T>::iterator it = expected.begin();
		for (typename NAMESPACE::vector<T, Alloc<T> >::const_reverse_iterator vit = testVector.rbegin(); vit != testVector.rend(); ++vit)
		{
			if (*it != *vit)
			{
				std::cerr << "Error: const reverse iteration returned incorrect value (" << *vit << " instead of " << *it << ")" << std::endl;
				errorCount++;
			}
			++it;
		}
	}

	return errorCount;
}

template <class T, template <typename> class Alloc>
int testIteratorArithmetic(unsigned int seed, NAMESPACE::vector<T, Alloc<T> > &testVector)
{
	srand(seed);
	int errorCount = 0;

	// Test: Increment and decrement iterators
	typename NAMESPACE::vector<T, Alloc<T> >::iterator it = testVector.begin();
	for (size_t i = 0; i < testVector.size(); i++)
	{
		if (it != testVector.begin() + i)
		{
			std::cerr << "Error: Iterator addition and/or subtraction is incorrect" << std::endl;
			errorCount++;
			break;
		}
		it++;
	}
	for (size_t i = testVector.size(); i > 0; i--)
	{
		if (it != testVector.begin() + i)
		{
			std::cerr << "Error: Iterator addition and/or subtraction is incorrect" << std::endl;
			errorCount++;
			break;
		}
		it--;
	}

	// Test: Iterator addition and subtraction
	it = testVector.begin();
	for (typename NAMESPACE::vector<T, Alloc<T> >::iterator::difference_type i = 0; i < static_cast<typename NAMESPACE::vector<T, Alloc<T> >::iterator::difference_type>(testVector.size()); i++)
	{
		if (it + i != testVector.begin() + i)
		{
			std::cerr << "Error: Iterator addition is incorrect" << std::endl;
			errorCount++;
			break;
		}
		if (testVector.begin() + i - it != i)
		{
			std::cerr << "Error: Iterator subtraction is incorrect" << std::endl;
			errorCount++;
			break;
		}
	}
	if (testVector.end() - testVector.begin() != static_cast<typename NAMESPACE::vector<T, Alloc<T> >::iterator::difference_type>(testVector.size()))
	{
		std::cerr << "Error: Iterator subtraction between begin() and end() is incorrect" << std::endl;
		errorCount++;
	}

	return errorCount;
}

template <class T, template <typename> class Alloc>
int testIteratorComparison(unsigned int seed, NAMESPACE::vector<T, Alloc<T> > &testVector)
{
	srand(seed);
	int errorCount = 0;
	typedef typename NAMESPACE::vector<T, Alloc<T> >::iterator iterator;

	// Test: comparison of two iterators obtained using different methods
	int numIterations = randomValue<T>::getIteration();
	for (int i = 0; i < numIterations; i++)
	{
		// Check if the testVector is not empty
		if (!testVector.empty())
		{
			// Generate a random index
			int index = rand() % testVector.size();

			// Obtain an iterator to the element using different methods
			iterator iter1 = testVector.begin() + index;
			iterator iter2 = testVector.end() - (testVector.size() - index);

			// Compare the two iterators and check if they are equal
			if (iter1 != iter2)
			{
				std::cerr << "Error: iterators obtained using different methods are not equal" << std::endl;
				errorCount++;
			}
		}
	}

	// Test: comparison of iterators to different containers
	numIterations = randomValue<T>::getIteration();
	for (int i = 0; i < numIterations; i++)
	{
		// Create two vectors with random elements
		NAMESPACE::vector<T, Alloc<T> > vec1(randomValue<T>::getIteration(), randomValue<T>::get());
		NAMESPACE::vector<T, Alloc<T> > vec2(randomValue<T>::getIteration(), randomValue<T>::get());

		// Obtain iterators to the beginning of each vector
		iterator iter1 = vec1.begin();
		iterator iter2 = vec2.begin();

		// Compare the two iterators and check if they are not equal
		if (iter1 == iter2)
		{
			std::cerr << "Error: iterators to different vectors are equal" << std::endl;
			errorCount++;
		}
	}

	return errorCount;
}

template <class T, template <typename> class Alloc>
int testIteratorDereference(unsigned int seed, NAMESPACE::vector<T, Alloc<T> > &testVector)
{
	(void)seed;
	int errorCount = 0;

	// Create and fill the vector with random values
	size_t numIterations = randomValue<int>::getIteration();
	for (size_t i = 0; i < numIterations; i++)
	{
		testVector.push_back(randomValue<T>::get());
	}

	// Test dereferencing of iterators
	typename NAMESPACE::vector<T, Alloc<T> >::iterator it = testVector.begin();
	for (size_t i = 0; i < numIterations; i++, it++)
	{
		if (*it != testVector[i])
		{
			std::cerr << "Error: dereferencing iterator did not return expected value at index " << i << std::endl;
			errorCount++;
		}
	}

	return errorCount;
}

template <class T, template <typename> class Alloc>
int testRelationalOperators(unsigned int seed, NAMESPACE::vector<T, Alloc<T> > &testVector)
{
	(void)seed;
	int errorCount = 0;

	// Test: equality operator
	NAMESPACE::vector<T, Alloc<T> > testVectorCopy = testVector;
	if (!(testVector == testVectorCopy))
	{
		std::cerr << "Error: Equality operator returned false for equal vectors" << std::endl;
		errorCount++;
	}

	// Test: inequality operator
	testVectorCopy.push_back(randomValue<T>::get());
	if (!(testVector != testVectorCopy))
	{
		std::cerr << "Error: Inequality operator returned false for different vectors" << std::endl;
		errorCount++;
	}

	// Test: less-than operator
	if (testVector.size() > 0)
	{
		NAMESPACE::vector<T, Alloc<T> > smallerVector = testVector;
		smallerVector.pop_back();
		if (!(smallerVector < testVector))
		{
			std::cerr << "Error: Less-than operator returned false for smaller vector" << std::endl;
			errorCount++;
		}
	}

	// Test: greater-than operator
	if (testVector.size() > 0)
	{
		NAMESPACE::vector<T, Alloc<T> > largerVector = testVector;
		largerVector.push_back(randomValue<T>::get());
		if (!(largerVector > testVector))
		{
			std::cerr << "Error: Greater-than operator returned false for larger vector" << std::endl;
			errorCount++;
		}
	}

	// Test: less-than-or-equal-to operator
	if (testVector.size() > 0)
	{
		NAMESPACE::vector<T, Alloc<T> > smallerVector = testVector;
		smallerVector.pop_back();
		if (!(smallerVector <= testVector))
		{
			std::cerr << "Error: Less-than-or-equal-to operator returned false for smaller vector" << std::endl;
			errorCount++;
		}
	}

	// Test: greater-than-or-equal-to operator
	if (testVector.size() > 0)
	{
		NAMESPACE::vector<T, Alloc<T> > largerVector = testVector;
		largerVector.push_back(randomValue<T>::get());
		if (!(largerVector >= testVector))
		{
			std::cerr << "Error: Greater-than-or-equal-to operator returned false for larger vector" << std::endl;
			errorCount++;
		}
	}

	return errorCount;
}

template <class T, template <typename> class Alloc>
int testPerformance(unsigned int seed, NAMESPACE::vector<T, Alloc<T> > &testVectorIGNORE)
{
	(void)seed;
	(void)testVectorIGNORE;
	NAMESPACE::vector<T, Alloc<T> > testVector;
	int numIterations = 10000000;	   // Number of iterations to perform
	int numWarmupIterations = 1000000; // Number of iterations to perform before starting the timing
	int numInsertIterations = 10000;   // Number of iterations to perform for testing insert performance
	int numEraseIterations = 10000;	   // Number of iterations to perform for testing erase performance

	// Warm-up phase
	for (int i = 0; i < numWarmupIterations; i++)
	{
		testVector.push_back(randomValue<T>::get());
	}
	testVector.clear();

	// Test: push_back() performance
	clock_t push_back_start = clock();
	for (int i = 0; i < numIterations; i++)
	{
		testVector.push_back(randomValue<T>::get());
	}
	clock_t push_back_end = clock();
	double push_back_duration = (double)(push_back_end - push_back_start) / CLOCKS_PER_SEC;

	std::cout << "push_back(): " << push_back_duration << " s" << std::endl;

	// Test: insert() performance
	clock_t insert_start = clock();
	for (int i = 0; i < numInsertIterations; i++)
	{
		typename NAMESPACE::vector<T, Alloc<T> >::iterator it = testVector.begin() + (std::rand() % testVector.size());
		testVector.insert(it, randomValue<T>::get());
	}
	clock_t insert_end = clock();
	double insert_duration = (double)(insert_end - insert_start) / CLOCKS_PER_SEC;

	std::cout << "insert(): " << insert_duration << " s" << std::endl;

	// Test: erase() performance
	clock_t erase_start = clock();
	for (int i = 0; i < numEraseIterations; i++)
	{
		typename NAMESPACE::vector<T, Alloc<T> >::iterator it = testVector.begin() + (std::rand() % testVector.size());
		testVector.erase(it);
	}
	clock_t erase_end = clock();
	double erase_duration = (double)(erase_end - erase_start) / CLOCKS_PER_SEC;

	std::cout << "erase(): " << erase_duration << " s" << std::endl;

	return 0;
}

template <class T>
static int testAllStack(unsigned int seed)
{
	NAMESPACE::vector<T> testMap;
	int errorCount = 0;
	errorCount += timeTest<NAMESPACE::vector, T, std::allocator>("testConstructorAndAssignment", testConstructorAndAssignment<T, std::allocator>, testMap, seed);
	errorCount += timeTest<NAMESPACE::vector, T, std::allocator>("testSize", testSize<T, std::allocator>, testMap, seed);
	errorCount += timeTest<NAMESPACE::vector, T, std::allocator>("testMaxSize", testMaxSize<T, std::allocator>, testMap, seed);
	errorCount += timeTest<NAMESPACE::vector, T, std::allocator>("testResize", testResize<T, std::allocator>, testMap, seed);
	errorCount += timeTest<NAMESPACE::vector, T, std::allocator>("testCapacity", testCapacity<T, std::allocator>, testMap, seed);
	errorCount += timeTest<NAMESPACE::vector, T, std::allocator>("testEmpty", testEmpty<T, std::allocator>, testMap, seed);
	errorCount += timeTest<NAMESPACE::vector, T, std::allocator>("testPushBack", testPushBack<T, std::allocator>, testMap, seed);
	errorCount += timeTest<NAMESPACE::vector, T, std::allocator>("testPopBack", testPopBack<T, std::allocator>, testMap, seed);
	errorCount += timeTest<NAMESPACE::vector, T, std::allocator>("testFront", testFront<T, std::allocator>, testMap, seed);
	errorCount += timeTest<NAMESPACE::vector, T, std::allocator>("testBack", testBack<T, std::allocator>, testMap, seed);
	errorCount += timeTest<NAMESPACE::vector, T, std::allocator>("testInsert", testInsert<T, std::allocator>, testMap, seed);
	errorCount += timeTest<NAMESPACE::vector, T, std::allocator>("testSwap", testSwap<T, std::allocator>, testMap, seed);
	errorCount += timeTest<NAMESPACE::vector, T, std::allocator>("testClear", testClear<T, std::allocator>, testMap, seed);
	errorCount += timeTest<NAMESPACE::vector, T, std::allocator>("testIterator", testIterator<T, std::allocator>, testMap, seed);
	errorCount += timeTest<NAMESPACE::vector, T, std::allocator>("testIteratorArithmetic", testIteratorArithmetic<T, std::allocator>, testMap, seed);
	errorCount += timeTest<NAMESPACE::vector, T, std::allocator>("testIteratorComparison", testIteratorComparison<T, std::allocator>, testMap, seed);
	errorCount += timeTest<NAMESPACE::vector, T, std::allocator>("testIteratorDereference", testIteratorDereference<T, std::allocator>, testMap, seed);
	errorCount += timeTest<NAMESPACE::vector, T, std::allocator>("testRelationalOperators", testRelationalOperators<T, std::allocator>, testMap, seed);
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
int vector_main(unsigned int seed)
{
#endif
	std::cout << "testAllVector<int>" << std::endl;
	int errorCount = testAllStack<int>(seed);
	std::cout << "testAllVector<char>" << std::endl;
	errorCount = testAllStack<char>(seed);
	std::cout << "Warning, this test might be really slow" << std::endl;
	std::cout << "testAllVector<std::string>" << std::endl;
	errorCount = testAllStack<std::string>(seed);
	std::cout << "testAllVector<MyClass>" << std::endl;
	errorCount = testAllStack<MyClass>(seed);
	return errorCount;
}