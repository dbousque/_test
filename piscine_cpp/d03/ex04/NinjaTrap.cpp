

#include "NinjaTrap.hpp"
#include <iostream>

std::string const	default_name = "default_name";
std::string			ninja_name = "NinjaTrap ";

NinjaTrap::NinjaTrap() : ClapTrap(default_name, 60, 60, 120, 120, 1, 60, 5, 0, ninja_name)
{
	std::cout << "NinjaTrap: O-KAY! Thanks for giving me a second chance, God. I really appreciate it." << std::endl;
	std::cout << "Jack: What? No, nooo, you are so STUPID! Whatever. You're welcome." << std::endl;
}

NinjaTrap::NinjaTrap(std::string const &name) : ClapTrap(name, 60, 60, 120, 120, 1, 60, 5, 0, ninja_name)
{
	std::cout << "NinjaTrap: O-KAY! Thanks for giving me a second chance, God. I really appreciate it." << std::endl;
	std::cout << "Jack: What? No, nooo, you are so STUPID! Whatever. You're welcome." << std::endl;
}

NinjaTrap::~NinjaTrap()
{
	std::cout << "NinjaTrap " << this->_name << " deleted" << std::endl;
}

void	NinjaTrap::ninjaShoebox(FragTrap &fragtrap)
{
	std::cout << "Ninja sees FragTrap, ninja attacks" << std::endl;
	this->rangedAttack(fragtrap.getName());
	fragtrap.takeDamage(this->_ranged_attack_damage);
}

void	NinjaTrap::ninjaShoebox(ScavTrap &scavtrap)
{
	std::cout << "Ninja sees ScavTrap, ninja doesn't like ScavTrap, ninja attacks harder" << std::endl;
	this->meleeAttack(scavtrap.getName());
	scavtrap.takeDamage(this->_melee_attack_damage);
}

void	NinjaTrap::ninjaShoebox(NinjaTrap &ninjatrap)
{
	std::cout << "Ninja sees an other ninja. Ninja waits for him to attack, and so does the other." << std::endl;
	(void)ninjatrap;
}

void	NinjaTrap::ninjaShoebox(ClapTrap &claptrap)
{
	std::cout << "Ninja sees generic ClapTrap, ninja is afraid and flees" << std::endl;
	std::cout << "ClapTrap confidence is therefore restored and he gains some HP" << std::endl;
	claptrap.beRepaired(15);
}