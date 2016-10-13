

#include "easyfind.hpp"
#include <iostream>
#include <vector>

void	my_assert(bool cond)
{
	if (!cond)
		std::cout << "Assertion failed" << std::endl;
}

int		main(void)
{
	std::cout << "Creating vector with 10 ints of value 42" << std::endl;
	std::vector<int>	vect(10, 42);
	std::cout << "Calling easyfind(vect, 100) and asserting the the result == vect.end()" << std::endl;
	my_assert(easyfind(vect, 100) == vect.end());
	std::cout << "ok" << std::endl;
	return (0);
}