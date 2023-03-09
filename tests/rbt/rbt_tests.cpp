#include "rbt_tests.hpp"
#include "_rbt.hpp"
#include "../randomValue.hpp"
#include "../utils.hpp"
#include <cstdlib>
#include <list>


template <class T>
int testValidBST(unsigned int seed, ft::RBTTest<T>& tree) {
	srand(seed);
	size_t numInputs = randomValue<T>::getIteration();
	size_t val;
	for (size_t i = 0; i < numInputs; i++) {
		val = randomValue<T>::get();
		while (tree.search(val))
			val = randomValue<T>::get();
		tree.insert(val);
	}
	std::list<ft::RBNode<T>*> inorderlst = tree.inorder_list();
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
static int testAll(unsigned int seed) {
	ft::RBTTest<T>	tree;
	int errorCount = 0;
	
	errorCount += timeTest<ft::RBTTest, T>("testValidBST", testValidBST<T>, tree, seed);

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
	int errorCount = testAll<int>(seed);
	return errorCount;
}