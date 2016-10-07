

#include "SuperTrap.hpp"
#include <iostream>

std::string const	default_name = "default_name";
std::string			super_name = "SuperTrap ";

SuperTrap::SuperTrap() : NinjaTrap(default_name), FragTrap(default_name)
{
	std::cout << "SuperTrap: O-KAY! Thanks for giving me a second chance, God. I really appreciate it." << std::endl;
	std::cout << "Jack: What? No, nooo, you are so STUPID! Whatever. You're welcome." << std::endl;
}

SuperTrap::SuperTrap(std::string const &name) : NinjaTrap(name), FragTrap(name)
{
	std::cout << "SuperTrap: O-KAY! Thanks for giving me a second chance, God. I really appreciate it." << std::endl;
	std::cout << "Jack: What? No, nooo, you are so STUPID! Whatever. You're welcome." << std::endl;
}

SuperTrap::~SuperTrap()
{
	std::cout << "SuperTrap " << this->FragTrap::_name << " deleted" << std::endl;
}

void				SuperTrap::rangedAttack(std::string const & target)
{
	this->FragTrap::rangedAttack(target);
}

void				SuperTrap::meleeAttack(std::string const & target)
{
	this->NinjaTrap::meleeAttack(target);
}

void				SuperTrap::takeDamage(unsigned int amount)
{
	this->FragTrap::takeDamage(amount);
}

void				SuperTrap::beRepaired(unsigned int amount)
{
	this->FragTrap::beRepaired(amount);
}

unsigned int		SuperTrap::getHitPoints()
{
	return this->FragTrap::getHitPoints();
}

unsigned int		SuperTrap::getMaxHitPoints()
{
	return this->FragTrap::getMaxHitPoints();
}

unsigned int		SuperTrap::getEnergyPoints()
{
	return this->NinjaTrap::getEnergyPoints();
}

unsigned int		SuperTrap::getMaxEnergyPoints()
{
	return this->NinjaTrap::getMaxEnergyPoints();
}

unsigned int		SuperTrap::getLevel()
{
	return this->FragTrap::getLevel();
}

std::string const	&SuperTrap::getName()
{
	return this->FragTrap::getName();
}

unsigned int		SuperTrap::getMeleeAttackDamage()
{
	return this->NinjaTrap::getMeleeAttackDamage();
}

unsigned int		SuperTrap::getRangedAttackDamage()
{
	return this->FragTrap::getRangedAttackDamage();
}

unsigned int		SuperTrap::getArmorDamageReduction()
{
	return this->FragTrap::getArmorDamageReduction();
}

std::string			&SuperTrap::getClassName()
{
	return super_name;
}

void				SuperTrap::displayInfos()
{
	std::cout << this->getClassName() << this->getName() << " :" << std::endl;
	std::cout << "  hit_points             : " << this->getHitPoints()<< std::endl;
	std::cout << "  max_hit_points         : " << this->getMaxHitPoints() << std::endl;
	std::cout << "  energy_points          : " << this->getEnergyPoints() << std::endl;
	std::cout << "  max_energy_points      : " << this->getMaxEnergyPoints() << std::endl;
	std::cout << "  level                  : " << this->getLevel() << std::endl;
	std::cout << "  melee_attack_damage    : " << this->getMeleeAttackDamage() << std::endl;
	std::cout << "  ranged_attack_damage   : " << this->getRangedAttackDamage() << std::endl;
	std::cout << "  armor_damage_reduction : " << this->getArmorDamageReduction() << std::endl;
}