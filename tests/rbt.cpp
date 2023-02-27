#include "_rbt.hpp"
#include "utils.hpp"
#include <cstdlib>
#include <list>


int testValidBST(unsigned int seed) {
	ft::RBT<int>	tree;
	srand(seed);
	int numInputs = rand() % 9901 + 100;
	int val = 0;
	for (int i = 0; i < numInputs; i++) {
		val = rand();
		tree.insert(val);
	}
	std::list<ft::Node<int>*> inorderlst = tree.inorder_list();
	std::list<ft::Node<int>*>::iterator it = inorderlst.begin();
	int	lastval = (*it)->key;
	it++;
	int errorcount = 0;
	for (; it != inorderlst.end(); it++) {
		if (((*it)->key <= lastval))
			errorcount++;
		lastval = (*it)->key;
	}
	return errorcount;
}

static int testAll(unsigned int seed) {
	int errorCount = 0;
	errorCount += timeTest("testValidBST", testValidBST, seed);

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
	int errorCount = testAll(seed);
	return errorCount;
}