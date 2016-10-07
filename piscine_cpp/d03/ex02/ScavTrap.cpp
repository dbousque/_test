

#include "ScavTrap.hpp"
#include <iostream>

std::string const	default_name = "default_name";
std::string			scav_name = "ScavTrap ";

ScavTrap::ScavTrap() : ClapTrap(default_name, 100, 100, 50, 50, 1, 20, 15, 3, scav_name)
{
	std::cout << "Jack: Nonono, you're not dead, you're --" << std::endl;
	std::cout << "ScavTrap: I'M DEAD I'M DEAD OHMYGOD I'M DEAD!" << std::endl;
}

ScavTrap::ScavTrap(std::string const &name) : ClapTrap(name, 100, 100, 50, 50, 1, 20, 15, 3, scav_name)
{
	std::cout << "ScavTrap: -- Are you god? Am I dead?" << std::endl;
}

ScavTrap::~ScavTrap()
{
	std::cout << "ScavTrap " << this->_name << " deleted" << std::endl;
}

void	ScavTrap::challenge1()
{
	std::cout << "[challenge] : " << "Eat 10 pounds of dirt" << std::endl;
}

void	ScavTrap::challenge2()
{
	std::cout << "[challenge] : " << "Make 142 pushups" << std::endl;
}

void	ScavTrap::challenge3()
{
	std::cout << "[challenge] : " << "Tell world's funniest joke" << std::endl;
}

void	(ScavTrap::*challenges[3])(void) = {
	&ScavTrap::challenge1,
	&ScavTrap::challenge2,
	&ScavTrap::challenge3
};

void	ScavTrap::challengeNewcomer()
{
	static bool	already_called = false;

	if (!already_called)
	{
		srand(time(NULL));
		already_called = true;
	}
	(this->*challenges[rand() % 3])();
}