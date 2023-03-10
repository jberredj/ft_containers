#include "rbt_tests.hpp"
#include "_rbt.hpp"
#include "../randomValue.hpp"
#include "../utils.hpp"
#include "../MyClass.hpp"
#include <exception>
#include <cstdlib>
#include <list>

//TODO: Add Alloc/delete Tracking
template <class T>
int testSearch(unsigned int seed, ft::RBTTest<T>& tree) {
	(void)seed;
	size_t	numInputs = randomValue<T>::getIteration() % 500;
	std::list<T>	valuesList;
	for (size_t i = 0; i < numInputs; i++)
		valuesList.push_back(randomValue<T>::get());
	valuesList.unique();
	int	errorCount = 0;
	typename std::list<T>::iterator	it = valuesList.begin();
	for (; it != valuesList.end(); it++) {
		tree.insert(*(it));
		if (!tree.search(*(it)))
			errorCount++;
	}
	return errorCount;
}

template <class T>
int testEmpty(unsigned int seed, ft::RBTTest<T>& tree) {
	(void)seed;
	tree.emptyTree();
	if (tree.size())
	{
		std::cerr << "tree should be empty but tree.size() returned " << tree.size() << std::endl;
		return 1;
	}
	tree.insert(randomValue<T>::get());
	if (!tree.size())
	{
		std::cerr << "tree.size() should be 1 but tree.size() returned " << tree.size() << std::endl;
		return 2;
	}
	tree.emptyTree();
	return 0;
}



template <class T>
int testInsert(unsigned int seed, ft::RBTTest<T>& tree) {
	srand(seed);
	size_t	numInputs = randomValue<T>::getIteration();
	for (size_t i = 0; i < numInputs; i++) {
		T val = randomValue<T>::get();
		while (tree.search(val))
			val = randomValue<T>::get();
		tree.insert(val);
	}
	if (tree.size() != numInputs)
		std::cerr << "tree.size() expected to be " << numInputs << " but " << tree.size() << " was returned." << std::endl;
	return static_cast<int>(numInputs - tree.size());
}

template <class T>
void inorderList(ft::RBNode<T> *node, std::list<ft::RBNode<T> *> &lst)
{
	if (node->isLeaf())
		return;
	inorderList(node->left, lst);
	lst.push_back(node);
	inorderList(node->right, lst);
}

template <class T>
int testValidBST(unsigned int seed, ft::RBTTest<T>& tree) {
	(void)seed;
	std::list<ft::RBNode<T> *> inorderlst;
	inorderList<T>(tree.getRoot(), inorderlst);
	typename std::list<ft::RBNode<T>*>::iterator it = inorderlst.begin();
	T	lastval = (*it)->key;
	it++;
	int errorcount = 0;
	for (; it != inorderlst.end(); it++) {
		if (((*it)->key <= lastval))
			errorcount++;
		lastval = (*it)->key;
	}
	return errorcount;
}

template <class T>
size_t	validRBT(ft::RBNode<T>& node)
{
	if (node.isLeaf())
		return 0;
	if (node.isRed() && node.left->isNotBlack() && node.right->isNotBlack())
		throw std::logic_error("A Red Node should have two black child.");
	size_t lBHeight = validRBT(*node.left);
	size_t rBHeight = validRBT(*node.right);

	if (lBHeight != rBHeight)
		throw std::length_error("RBT is unbalanced");
	return lBHeight + static_cast<size_t>(node.color);
}

template <class T>
int testValidRBT(unsigned int seed, ft::RBTTest<T>& tree) {
	(void)seed;
	try
	{
		validRBT<T>(*tree.getRoot());
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return 1;
	}
	
	return 0;
}

template <class T>
int testRemove(unsigned int seed, ft::RBTTest<T>& tree) {
	srand(seed);
	std::list<ft::RBNode<T> *> inorderlst;
	inorderList<T>(tree.getRoot(), inorderlst);
	typename std::list<ft::RBNode<T>*>::iterator it = inorderlst.begin();
	int errorcount = 0;
	for (size_t i = tree.size() - 1; it != inorderlst.end(); it++, i--) {
		tree.remove((*it)->key);
		if ((randomValue<T>::getIteration() % 4) && i != tree.size()) {
			std::cerr << "tree.size() expected to be " << i << " but " << tree.size() << " was returned." << std::endl;
			return 1;
		}
		else if (randomValue<T>::getIteration() % 4)
			validRBT<T>(*tree.getRoot());

	}
	return errorcount;
}

template <class T>
static int testAll(unsigned int seed) {
	ft::RBTTest<T>	tree;
	int errorCount = 0;
	errorCount += timeTest<ft::RBTTest, T>("testSearch", testSearch<T>, tree, seed);
	errorCount += timeTest<ft::RBTTest, T>("testEmpty", testEmpty<T>, tree, seed);
	errorCount += timeTest<ft::RBTTest, T>("testInsert", testInsert<T>, tree, seed);
	errorCount += timeTest<ft::RBTTest, T>("testValidBST", testValidBST<T>, tree, seed);
	errorCount += timeTest<ft::RBTTest, T>("testValidRBT", testValidRBT<T>, tree, seed);
	errorCount += timeTest<ft::RBTTest, T>("testRemove", testRemove<T>, tree, seed);
	std::cout << std::endl;
	return errorCount;
}

#ifdef STANDALONE
# include <cstdlib> 
int main(int ac, char* av[]) {
	if (ac != 2) {
		std::cerr << "Usage: " << av[0] << " seed" << std::endl;
		return 1;
	}
	unsigned int seed = atoi(av[1]);
#else
int	rbt_main(unsigned int seed) {
#endif
	std::cout << "testAll<int>" << std::endl;
	int errorCount = testAll<int>(seed);
	std::cout << "testAll<char>" << std::endl;
	errorCount = testAll<char>(seed);
	std::cout << "testAll<std::string>" << std::endl;
	errorCount = testAll<std::string>(seed);
	std::cout << "testAll<MyClass>" << std::endl;
	errorCount = testAll<MyClass>(seed);
	return errorCount;
}