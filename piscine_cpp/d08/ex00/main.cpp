

#include "easyfind.hpp"
#include <iostream>
#include <vector>

void	my_assert(bool cond)
{
	if (!cond)
		std::cout << "Assertion failed" << std::endl;
	else
		std::cout << "Assertion ok" << std::endl;
}

int		main(void)
{
	std::cout << "Creating vector with 10 ints of value 42" << std::endl;
	std::vector<int>	vect(10, 42);
	std::cout << "Calling easyfind(vect, 100) and asserting the the result == vect.end()" << std::endl;
	my_assert(easyfind(vect, 100) == vect.end());
	std::cout << "Calling easyfind(vect, 42) and asserting the the result == vect.begin()" << std::endl;
	my_assert(easyfind(vect, 42) == vect.begin());
	std::cout << "Asserting that *(easyfind(vect, 42)) == 42" << std::endl;
	my_assert(*(easyfind(vect, 42)) == 42);
	std::cout << std::endl << "Creating vector with [0,1,2,3,4,5,6,7,8,9]" << std::endl;
	std::vector<int>	vect2;
	for (int i = 0; i < 10; i++)
		vect2.push_back(i);
	std::cout << "Asserting that easyfind(vect2, 0) == vect2.begin()" << std::endl;
	my_assert(easyfind(vect2, 0) == vect2.begin());
	std::cout << "Asserting that easyfind(vect2, 1) == vect2.begin() + 1" << std::endl;
	my_assert(easyfind(vect2, 1) == vect2.begin() + 1);
	std::cout << "Asserting that easyfind(vect2, 9) == vect2.end() - 1" << std::endl;
	my_assert(easyfind(vect2, 9) == vect2.end() - 1);
	return (0);
}