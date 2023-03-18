#include <cstdlib>
#include "map/map_tests.hpp"
#include "vector/vector_tests.hpp"
#include "stack/stack_tests.hpp"


int main(int ac, char *av[])
{
	if (ac != 2)
	{
		std::cerr << "Usage: " << av[0] << " seed" << std::endl;
		return 1;
	}
	unsigned int seed = atoi(av[1]);
#ifdef USING_STD
	std::cout << "Testing std::vector" << std::endl;
#else
	std::cout << "Testing ft::vector" << std::endl;	
#endif
	vector_main(seed);
	stack_main(seed);
	map_main(seed);
	return 0;
}