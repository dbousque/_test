

#include "FragTrap.hpp"
#include <iostream>

std::string const	default_name = "default_name";
std::string			frag_name = "FragTrap ";

FragTrap::FragTrap() : ClapTrap(default_name, 100, 100, 100, 100, 1, 30, 20, 5, frag_name)
{
	std::cout << "No no no no! Cancel directive three!" << std::endl;
}

FragTrap::FragTrap(std::string const &name) : ClapTrap(name, 100, 100, 100, 100, 1, 30, 20, 5, frag_name)
{
	std::cout << "Directive one: Protect humanity! Directive two: Obey Jack at all costs. Directive three: Dance!" << std::endl;
}

FragTrap::~FragTrap()
{
	std::cout << "FragTrap " << this->_name << " deleted" << std::endl;
}

// make the attacker loose no energy, but weak attack
void				FragTrap::snore(std::string const & target)
{
	std::cout << "FragTrap " << this->_name << " attacks " << target;
	std::cout << " with snore, causing " << 5;
	std::cout << " points of damage !" << std::endl;
}

// restores some HP, but costs a lot of energy
void				FragTrap::myAttack2(std::string const & target)
{
	if (this->_energy_points < 50)
	{
		std::cout << "Not enough energy to perform meleeAttack" << std::endl;
		return ;
	}
	std::cout << "FragTrap " << this->_name << " attacks " << target;
	std::cout << " with myAttack2, causing " << 50;
	std::cout << " points of damage !" << std::endl;
	this->_energy_points -= 50;
	this->beRepaired(10);
}

// makes big damage, but costs some HP and some energy
void				FragTrap::myAttack3(std::string const & target)
{
	if (this->_energy_points < 40)
	{
		std::cout << "Not enough energy to perform meleeAttack" << std::endl;
		return ;
	}
	std::cout << "FragTrap " << this->_name << " attacks " << target;
	std::cout << " with myAttack3, causing " << 70;
	std::cout << " points of damage !" << std::endl;
	this->_energy_points -= 40;
	this->takeDamage(20);
}

void	(FragTrap::*attack_funcs[5])(std::string const &) = {
	&FragTrap::rangedAttack,
	&FragTrap::meleeAttack,
	&FragTrap::snore,
	&FragTrap::myAttack2,
	&FragTrap::myAttack3
};

void	FragTrap::vaulthunter_dot_exe(std::string const & target)
{
	static bool	already_called = false;

	if (!already_called)
	{
		srand(time(NULL));
		already_called = true;
	}
	if (25 > this->_energy_points)
		this->_energy_points = 0;
	else
		this->_energy_points -= 25;
	(this->*attack_funcs[rand() % 5])(target);
}