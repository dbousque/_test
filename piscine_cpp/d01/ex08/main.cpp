

#include "Human.hpp"
#include <iostream>

int		main(void)
{
	Human	human;

	std::cout << "calling action for the three functions : " << std::endl;
	human.action("meleeAttack", "dodo");
	human.action("rangedAttack", "dodo");
	human.action("intimidatingShout", "dodo");
	return (0);
}