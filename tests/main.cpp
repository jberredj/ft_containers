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
	
	vector_main(seed);
	stack_main(seed);
	map_main(seed);
	return 0
}