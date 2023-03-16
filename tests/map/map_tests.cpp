#include "map_tests.hpp"
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

template <class Key, class Value>
int testMapInsert(unsigned int seed, ft::MapTest<Key, Value> &testMap)
{
	std::srand(seed);
	int errorCount = 0;
	int numIterations = randomValue<Key>::getIteration();

	// Test: Insert multiple key-value pairs and check that the map contains them
	std::set<Key> keys;
	for (int i = 0; i < numIterations; i++)
	{
		Key key = randomValue<Key>::get();
		Value value = randomValue<Value>::get();
		testMap.insert(NAMESPACE::pair<Key, Value>(key, value));
		keys.insert(key);
	}
	if (testMap.size() != keys.size())
	{
		std::cerr << "Error: map size is incorrect after inserting multiple key-value pairs" << std::endl;
		errorCount++;
	}
	for (typename std::set<Key>::iterator it = keys.begin(); it != keys.end(); ++it)
	{
		if (testMap.find(*it) == testMap.end())
		{
			std::cerr << "Error: map does not contain key " << *it << " after insertion" << std::endl;
			errorCount++;
		}
	}

	return errorCount;
}

template <class Key, class Value>
int testMapEraseByKey(unsigned int seed, ft::MapTest<Key, Value> &testMap)
{
	std::srand(seed);
	int errorCount = 0;

	// Test: Erase elements from the middle of the map using erase() and check that the map size is correct
	size_t numIterations = randomValue<Key>::getIteration();
	std::vector<Key> keysToRemove;
	std::set<Key> uniqueKeys;

	// Insert keys from the map into the uniqueKeys set
	for (typename ft::MapTest<Key, Value>::iterator it = testMap.begin(); it != testMap.end(); ++it)
	{
		uniqueKeys.insert(it->first);
	}

	// Generate random unique keys for removal based on the map content
	while (keysToRemove.size() < numIterations && !uniqueKeys.empty()) {
		size_t idx = std::rand() % uniqueKeys.size();
		typename std::set<Key>::iterator it = uniqueKeys.begin();
		std::advance(it, idx);
		keysToRemove.push_back(*it);
		uniqueKeys.erase(it);
	}

	for (size_t i = 0; i < keysToRemove.size(); i++)
	{
		testMap.erase(keysToRemove[i]);
	}

	if (testMap.size() != (uniqueKeys.size()))
	{
		std::cerr << "Error: map size is incorrect after erasing elements from the middle" << std::endl;
		errorCount++;
	}

	return errorCount;
}


template <class Key, class Value>
int testMapEraseByIterator(unsigned int seed, ft::MapTest<Key, Value> &testMap)
{
	std::srand(seed);
	int errorCount = 0;
	int numIterations = randomValue<Key>::getIteration(); // Get number of iterations for this test

	// Insert key-value pairs into the map
	for (int i = 0; i < numIterations; i++)
	{
		Key key = randomValue<Key>::get();
		Value value = randomValue<Value>::get();
		testMap.insert(NAMESPACE::pair<Key, Value>(key, value));
	}

	// Erase key-value pairs from the map
	for (typename ft::MapTest<Key, Value>::iterator iter = testMap.begin(); iter != testMap.end();)
	{
		testMap.erase(iter);
		iter = testMap.begin();
	}

	// Test: Size of map after erasing key-value pairs
	if (testMap.size() != 0)
	{
		std::cerr << "Error: Size of map after erasing all key-value pairs is not 0" << std::endl;
		return 1;
	}

	return errorCount;
}

template <class Key, class Value>
int testMapFind(unsigned int seed, ft::MapTest<Key, Value> &testMap)
{
	std::srand(seed);
	int errorCount = 0;
	int numIterations = randomValue<Key>::getIteration(); // Get number of iterations for this test

	// Insert key-value pairs into the map
	std::set<Key> keys;
	for (int i = 0; i < numIterations; i++)
	{
		Key key = randomValue<Key>::get();
		Value value = randomValue<Value>::get();
		testMap.insert(NAMESPACE::pair<Key, Value>(key, value));
	}

	// Test: Finding key-value pairs in the map
	for (typename ft::MapTest<Key, Value>::iterator iter = testMap.begin(); iter != testMap.end(); iter++)
	{
		typename ft::MapTest<Key, Value>::iterator foundIter = testMap.find(iter->first);
		if (foundIter == testMap.end())
		{
			std::cerr << "Error: Key-value pair not found in map: key = " << iter->first << std::endl;
			errorCount++;
		}
	}

	// Test: Finding non-existent key-value pairs in the map
	for (int i = 0; i < numIterations; i++)
	{
		Key key;
		do {
			key = randomValue<Key>::get();
		} while (testMap.find(key) != testMap.end());

		typename ft::MapTest<Key, Value>::iterator foundIter = testMap.find(key);
		if (foundIter != testMap.end())
		{
			std::cerr << "Error: Non-existent key-value pair found in map: key = " << key << std::endl;
			errorCount++;
		}
	}

	return errorCount;
}



template <class Key, class Value>
int testMapCopyConstructor(unsigned int seed, ft::MapTest<Key, Value> &testMap)
{
	std::srand(seed);
	int errorCount = 0;
	int numIterations = randomValue<Key>::getIteration(); // Get number of iterations for this test

	// Insert key-value pairs into the map
	for (int i = 0; i < numIterations; i++)
	{
		Key key = randomValue<Key>::get();
		Value value = randomValue<Value>::get();
		testMap.insert(NAMESPACE::pair<Key, Value>(key, value));
	}

	// Create copy of map using copy constructor
	ft::MapTest<Key, Value> copyMap(testMap);

	// Test: Size of copy map
	if (copyMap.size() != testMap.size())
	{
		std::cerr << "Error: Size of copy map does not match original map" << std::endl;
		return 1;
	}

	// Test: Values of copy map
	for (typename ft::MapTest<Key, Value>::iterator iter = copyMap.begin(); iter != copyMap.end(); iter++)
	{
		if (iter->second != testMap[iter->first])
		{
			std::cerr << "Error: Value of copy map does not match original map for key " << iter->first << std::endl;
			errorCount++;
		}
	}

	return errorCount;
}

template <class Key, class Value>
int testMapCopyAssignmentOperator(unsigned int seed, ft::MapTest<Key, Value> &testMap)
{
	std::srand(seed);
	int errorCount = 0;
	int numIterations = randomValue<Key>::getIteration(); // Get number of iterations for this test

	// Insert key-value pairs into the map
	for (int i = 0; i < numIterations; i++)
	{
		Key key = randomValue<Key>::get();
		Value value = randomValue<Value>::get();
		testMap.insert(NAMESPACE::pair<Key, Value>(key, value));
	}

	// Create copy of map using copy constructor
	ft::MapTest<Key, Value> copyMap;
	copyMap = testMap;

	// Test: Size of copy map
	if (copyMap.size() != testMap.size())
	{
		std::cerr << "Error: Size of copy map does not match original map" << std::endl;
		return 1;
	}

	// Test: Values of copy map
	for (typename ft::MapTest<Key, Value>::iterator iter = copyMap.begin(); iter != copyMap.end(); iter++)
	{
		if (iter->second != testMap[iter->first])
		{
			std::cerr << "Error: Value of copy map does not match original map for key " << iter->first << std::endl;
			errorCount++;
		}
	}

	return errorCount;
}

template <class Key, class Value>
int testMapIterator(unsigned int seed, ft::MapTest<Key, Value> &testMap)
{
	std::srand(seed);
	int errorCount = 0;
	size_t numIterations = randomValue<Key>::getIteration(); // Get number of iterations for this test

	// Insert key-value pairs into the map
	for (size_t i = 0; i < numIterations; i++)
	{
		Key key = randomValue<Key>::get();
		Value value = randomValue<Value>::get();
		testMap.insert(NAMESPACE::pair<Key, Value>(key, value));
	}

	// Test: Iterator behavior
	size_t count = 0;
	typename ft::MapTest<Key, Value>::iterator iter;
	for (iter = testMap.begin(); iter != testMap.end(); iter++)
	{
		if (count == 0 && iter != testMap.begin())
		{
			std::cerr << "Error: First iterator position not equal to begin()" << std::endl;
			errorCount++;
		}
		if (count == testMap.size() - 1 && iter != --testMap.end())
		{
			std::cerr << "Error: Last iterator position not equal to end() - 1" << std::endl;
			errorCount++;
		}
		count++;
	}

	return errorCount;
}

template <class Key, class Value>
int testMapLowerBound(unsigned int seed, ft::MapTest<Key, Value>& testMap) {
    std::srand(seed);
    int errorCount = 0;
    int numIterations = randomValue<Key>::getIteration(); // Get number of iterations for this test

    // Insert key-value pairs into the map
    for (int i = 0; i < numIterations; i++) {
        Key key = randomValue<Key>::get();
        Value value = randomValue<Value>::get();
        testMap.insert(NAMESPACE::pair<Key, Value>(key, value));
    }

    // Test: lower_bound() function
    for (typename ft::MapTest<Key, Value>::iterator iter = testMap.begin(); iter != testMap.end(); iter++) {
        typename ft::MapTest<Key, Value>::iterator lowerIter = testMap.lower_bound(iter->first);
        if (lowerIter == testMap.end() || lowerIter->first < iter->first) {
            std::cerr << "Error: lower_bound() returned incorrect iterator for key " << iter->first << std::endl;
            errorCount++;
        }
    }

    // Test: lower_bound() for non-existent key
    for (int i = 0; i < numIterations; i++) {
        Key key;
        do {
            key = randomValue<Key>::get();
        } while (testMap.find(key) != testMap.end());

        typename ft::MapTest<Key, Value>::iterator lowerIter = testMap.lower_bound(key);
        if (lowerIter != testMap.end() && lowerIter->first == key) {
            std::cerr << "Error: lower_bound() returned incorrect iterator for non-existent key " << key << std::endl;
            errorCount++;
        }
    }

    return errorCount;
}


template <class Key, class Value>
int testMapEqualRange(unsigned int seed, ft::MapTest<Key, Value> &testMap)
{
	std::srand(seed);
	int errorCount = 0;
	int numIterations = randomValue<Key>::getIteration(); // Get number of iterations for this test

	// Insert key-value pairs into the map
	for (int i = 0; i < numIterations; i++)
	{
		Key key = randomValue<Key>::get();
		Value value = randomValue<Value>::get();
		testMap.insert(NAMESPACE::pair<Key, Value>(key, value));
	}

	// Test: equal_range() function
	for (typename ft::MapTest<Key, Value>::iterator iter = testMap.begin(); iter != testMap.end(); iter++)
	{
		NAMESPACE::pair<typename ft::MapTest<Key, Value>::iterator, typename ft::MapTest<Key, Value>::iterator> range = testMap.equal_range(iter->first);
		if (range.first == testMap.end() || range.first->first != iter->first)
		{
			std::cerr << "Error: equal_range() returned incorrect iterators for key " << std::endl;
			errorCount++;
		}
		else
		{
			typename ft::MapTest<Key, Value>::iterator nextIter = range.first;
			++nextIter;
			if (nextIter != range.second && nextIter->first == iter->first)
			{
				std::cerr << "Error: equal_range() returned incorrect iterators for key " << std::endl;
				errorCount++;
			}
		}
	}

	// Test: equal_range() for non-existent key
	for (int i = 0; i < numIterations; i++)
	{
		Key key = randomValue<Key>::get();
		for (; testMap.find(key) != testMap.end(); key = randomValue<Key>::get())
		{
		};
		NAMESPACE::pair<typename ft::MapTest<Key, Value>::iterator, typename ft::MapTest<Key, Value>::iterator> range = testMap.equal_range(key);
		if (range.first != range.second)
		{
			std::cerr << "Error: equal_range() returned incorrect iterators for non-existent key " << key << std::endl;
			errorCount++;
		}
	}

	return errorCount;
}

template <class Key, class Value>
int testMapUpperBound(unsigned int seed, ft::MapTest<Key, Value> &testMap)
{
	std::srand(seed);
	int errorCount = 0;
	int numIterations = randomValue<Key>::getIteration(); // Get number of iterations for this test

	// Insert key-value pairs into the map
	for (int i = 0; i < numIterations; i++)
	{
		Key key = randomValue<Key>::get();
		Value value = randomValue<Value>::get();
		testMap.insert(NAMESPACE::pair<Key, Value>(key, value));
	}

	// Test: upper_bound() function
	for (typename ft::MapTest<Key, Value>::iterator iter = testMap.begin(); iter != testMap.end(); iter++)
	{
		typename ft::MapTest<Key, Value>::iterator upperIter = testMap.upper_bound(iter->first);
		if (upperIter != testMap.end() && upperIter->first <= iter->first)
		{
			std::cerr << "Error: upper_bound() returned incorrect iterator for key " << iter->first << std::endl;
			errorCount++;
		}
	}

	// Test: upper_bound() for non-existent key
	for (int i = 0; i < numIterations; i++)
	{
		Key key = randomValue<Key>::get();
		typename ft::MapTest<Key, Value>::iterator upperIter = testMap.upper_bound(key);
		if (upperIter != testMap.end() && upperIter->first <= key)
		{
			std::cerr << "Error: upper_bound() returned incorrect iterator for non-existent key " << key << std::endl;
			errorCount++;
		}
	}

	return errorCount;
}

template <class Key, class Value>
int testMapSwap(unsigned int seed, ft::MapTest<Key, Value> &testMap)
{
	std::srand(seed);
	int errorCount = 0;
	int numIterations = randomValue<Key>::getIteration(); // Get number of iterations for this test

	ft::MapTest<Key, Value> otherMap;
	for (int i = 0; i < numIterations; i++)
	{
		Key key = randomValue<Key>::get();
		Value value = randomValue<Value>::get();
		otherMap.insert(NAMESPACE::pair<Key, Value>(key, value));
	}

	// Test: swap() function
	ft::MapTest<Key, Value> tempTestMap = testMap;
	ft::MapTest<Key, Value> tempOtherMap = otherMap;

	testMap.swap(otherMap);

	if (testMap != tempOtherMap || otherMap != tempTestMap)
	{
		std::cerr << "Error: swap() function failed" << std::endl;
		errorCount++;
	}

	return errorCount;
}

template <class Key, class Value>
int testMapCombinedOperations(unsigned int seed, ft::MapTest<Key, Value> &testMap)
{
	std::srand(seed);
	int errorCount = 0;
	int numIterations = randomValue<Key>::getIteration(); // Get number of iterations for this test

	// Test: Insert multiple key-value pairs and then check if the map contains all of the keys
	std::set<Key> keys;
	for (int i = 0; i < numIterations; i++)
	{
		Key key = randomValue<Key>::get();
		Value value = randomValue<Value>::get();
		testMap.insert(NAMESPACE::pair<Key, Value>(key, value));
		keys.insert(key);
	}
	for (typename std::set<Key>::iterator it = keys.begin(); it != keys.end(); ++it)
	{
		if (testMap.find(*it) == testMap.end())
		{
			std::cerr << "Error: map does not contain key " << *it << " after insertion" << std::endl;
			errorCount++;
		}
	}

	// Test: Remove elements from the middle of the map using erase()
	typename ft::MapTest<Key, Value>::iterator it = testMap.begin();
	std::advance(it, numIterations / 2);
	Key keyToRemove = it->first;
	testMap.erase(it);
	if (testMap.find(keyToRemove) != testMap.end())
	{
		std::cerr << "Error: map still contains key " << keyToRemove << " after removal" << std::endl;
		errorCount++;
	}

	// Test: Copy constructor and assignment operator
	ft::MapTest<Key, Value> copyMap(testMap);
	ft::MapTest<Key, Value> assignedMap = testMap;
	if (copyMap != testMap || assignedMap != testMap)
	{
		std::cerr << "Error: copy constructor or assignment operator failed" << std::endl;
		errorCount++;
	}

	// Test: Comparison operators for maps with different configurations of elements
	ft::MapTest<Key, Value> emptyMap;
	if (!(testMap == testMap) || !(emptyMap == emptyMap) || !(testMap != emptyMap))
	{
		std::cerr << "Error: comparison operators failed" << std::endl;
		errorCount++;
	}

	return errorCount;
}

template <class Key, class Value>
int testMapEdgeCases(unsigned int seed, ft::MapTest<Key, Value>& testMap) {
    std::srand(seed);
    int errorCount = 0;

    // Test: Insert very large or very small keys or values
    Key verySmallKey = std::numeric_limits<Key>::min();
    Key veryLargeKey = std::numeric_limits<Key>::max();
    Value verySmallValue = std::numeric_limits<Value>::min();
    Value veryLargeValue = std::numeric_limits<Value>::max();
    testMap.insert(NAMESPACE::pair<Key, Value>(verySmallKey, verySmallValue));
    testMap.insert(NAMESPACE::pair<Key, Value>(veryLargeKey, veryLargeValue));

    std::size_t expectedSize = 0;
    if (verySmallKey != veryLargeKey) {
        expectedSize = 2;
    } else {
        expectedSize = 1;
    }

    if (testMap.size() != expectedSize) {
        std::cerr << "Error: map size is incorrect after inserting very large or very small keys or values" << std::endl;
        errorCount++;
    }

    // Test: Remove the last element from the map
    Key lastKey = testMap.rbegin()->first;
    testMap.erase(lastKey);
    if (testMap.find(lastKey) != testMap.end()) {
        std::cerr << "Error: map still contains last key " << lastKey << " after removal" << std::endl;
        errorCount++;
    }

    return errorCount;
}

template <class Key, class Value>
int testMapPerformance(unsigned int seed, ft::MapTest<Key, Value>& testMap) {
    std::srand(seed);
    int errorCount = 0;

    // Test: Insert and search for a large number of elements
    int numElements = 100000;
    std::vector<Key> insertedKeys;
    for (int i = 0; i < numElements; i++) {
        Key key = randomValue<Key>::get();
        Value value = randomValue<Value>::get();
        testMap.insert(NAMESPACE::pair<Key, Value>(key, value));
        insertedKeys.push_back(key);
    }
    for (int i = 0; i < numElements; i++) {
        Key key = insertedKeys[i];
        typename ft::MapTest<Key, Value>::iterator it = testMap.find(key);
        if (it == testMap.end()) {
            std::cerr << "Error: map does not contain key " << key << " after insertion" << std::endl;
            errorCount++;
        }
    }

    return errorCount;
}



template <class Key, class Value>
static int testAllMap(unsigned int seed)
{
	ft::MapTest<Key, Value> testMap;
	int errorCount = 0;
	errorCount += timeTest<ft::MapTest, Key, Value>("testMapInsert", testMapInsert<Key, Value>, testMap, seed);
	errorCount += timeTest<ft::MapTest, Key, Value>("testMapEraseByKey", testMapEraseByKey<Key, Value>, testMap, seed);
	errorCount += timeTest<ft::MapTest, Key, Value>("testMapEraseByIterator", testMapEraseByIterator<Key, Value>, testMap, seed);
	errorCount += timeTest<ft::MapTest, Key, Value>("testMapFind", testMapFind<Key, Value>, testMap, seed);
	errorCount += timeTest<ft::MapTest, Key, Value>("testMapCopyConstructor", testMapCopyConstructor<Key, Value>, testMap, seed);
	errorCount += timeTest<ft::MapTest, Key, Value>("testMapCopyAssignmentOperator", testMapCopyAssignmentOperator<Key, Value>, testMap, seed);
	errorCount += timeTest<ft::MapTest, Key, Value>("testMapIterator", testMapIterator<Key, Value>, testMap, seed);
	// testMap.clear();
	errorCount += timeTest<ft::MapTest, Key, Value>("testMapLowerBound", testMapLowerBound<Key, Value>, testMap, seed);
	errorCount += timeTest<ft::MapTest, Key, Value>("testMapEqualRange", testMapEqualRange<Key, Value>, testMap, seed);
	errorCount += timeTest<ft::MapTest, Key, Value>("testMapUpperBound", testMapUpperBound<Key, Value>, testMap, seed);
	errorCount += timeTest<ft::MapTest, Key, Value>("testMapSwap", testMapSwap<Key, Value>, testMap, seed);
	errorCount += timeTest<ft::MapTest, Key, Value>("testMapCombinedOperations", testMapCombinedOperations<Key, Value>, testMap, seed);
	testMap.clear();
	errorCount += timeTest<ft::MapTest, Key, Value>("testMapEdgeCases", testMapEdgeCases<Key, Value>, testMap, seed);
	errorCount += timeTest<ft::MapTest, Key, Value>("testMapPerformance", testMapPerformance<Key, Value>, testMap, seed);
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
	std::cout << "testAll<int, int>" << std::endl;
	int errorCount = testAllMap<int, int>(seed);
	std::cout << "testAll<int, char>" << std::endl;
	errorCount = testAllMap<int, char>(seed);
	std::cout << "testAll<int, std::string>" << std::endl;
	errorCount = testAllMap<int, std::string>(seed);
	std::cout << "testAll<int, MyClass>" << std::endl;
	errorCount = testAllMap<int, MyClass>(seed);

	std::cout << "testAll<char, int>" << std::endl;
	errorCount = testAllMap<char, int>(seed);
	std::cout << "testAll<char, char>" << std::endl;
	errorCount = testAllMap<char, char>(seed);
	std::cout << "testAll<char, std::string>" << std::endl;
	errorCount = testAllMap<char, std::string>(seed);
	std::cout << "testAll<char, MyClass>" << std::endl;
	errorCount = testAllMap<char, MyClass>(seed);

	std::cout << "testAll<std::string, int>" << std::endl;
	errorCount = testAllMap<char, int>(seed);
	std::cout << "testAll<std::string, char>" << std::endl;
	errorCount = testAllMap<std::string, char>(seed);
	std::cout << "testAll<std::string, std::string>" << std::endl;
	errorCount = testAllMap<std::string, std::string>(seed);
	std::cout << "testAll<std::string, MyClass>" << std::endl;
	errorCount = testAllMap<std::string, MyClass>(seed);

	std::cout << "testAll<MyClass, int>" << std::endl;
	errorCount = testAllMap<MyClass, int>(seed);
	std::cout << "testAll<MyClass, char>" << std::endl;
	errorCount = testAllMap<MyClass, char>(seed);
	std::cout << "testAll<MyClass, std::string>" << std::endl;
	errorCount = testAllMap<MyClass, std::string>(seed);
	std::cout << "testAll<MyClass, MyClass>" << std::endl;
	errorCount = testAllMap<MyClass, MyClass>(seed);
	return errorCount;
}