

#include "Human.hpp"
#include <iostream>

void	Human::meleeAttack(std::string const & target)
{
	std::cout << "meleeAttack called with param \"" << target << "\"" << std::endl;
}

void	Human::rangedAttack(std::string const & target)
{
	std::cout << "rangedAttack called with param \"" << target << "\"" << std::endl;
}

void	Human::intimidatingShout(std::string const & target)
{
	std::cout << "intimidatingShout called with param \"" << target << "\"" << std::endl;
}

int		index_of(std::string *array, std::string const &to_find, int len)
{
	int		i;

	i = 0;
	while (i < len && array[i] != to_find)
		i++;
	return (i);
}

void	Human::action(std::string const & action_name, std::string const & target)
{
	std::string	names[3] = {"meleeAttack", "rangedAttack", "intimidatingShout"};
	void	(Human::*funcs[3])(std::string const & target) = {&Human::meleeAttack, &Human::rangedAttack, &Human::intimidatingShout};
	int		ind;

	ind = index_of(names, action_name, 3);
	if (ind != 3)
		(this->*funcs[ind])(target);
}