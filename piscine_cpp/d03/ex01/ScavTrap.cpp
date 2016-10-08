

#include "ScavTrap.hpp"
#include <iostream>

std::string const	default_name = "default_name";

ScavTrap::ScavTrap() :
	_hit_points(100),
	_max_hit_points(100),
	_energy_points(50),
	_max_energy_points(50),
	_level(1),
	_name(default_name),
	_melee_attack_damage(20),
	_ranged_attack_damage(15),
	_armor_damage_reduction(3)
{
	std::cout << "Jack: Nonono, you're not dead, you're --" << std::endl;
	std::cout << "ScavTrap: I'M DEAD I'M DEAD OHMYGOD I'M DEAD!" << std::endl;
}

ScavTrap::ScavTrap(std::string const &name) :
	_hit_points(100),
	_max_hit_points(100),
	_energy_points(50),
	_max_energy_points(50),
	_level(1),
	_name(name),
	_melee_attack_damage(20),
	_ranged_attack_damage(15),
	_armor_damage_reduction(3)
{
	std::cout << "ScavTrap: -- Are you god? Am I dead?" << std::endl;
}

ScavTrap::ScavTrap(ScavTrap &other) :
	_hit_points(other.getHitPoints()),
	_max_hit_points(other.getMaxHitPoints()),
	_energy_points(other.getEnergyPoints()),
	_max_energy_points(other.getMaxEnergyPoints()),
	_level(other.getLevel()),
	_name(other.getName()),
	_melee_attack_damage(other.getMeleeAttackDamage()),
	_ranged_attack_damage(other.getRangedAttackDamage()),
	_armor_damage_reduction(other.getArmorDamageReduction())
{
	std::cout << "Copy constructor called for " << other.getName() << std::endl;
}

ScavTrap::~ScavTrap()
{
	std::cout << "ScavTrap " << this->_name << " deleted" << std::endl;
}

ScavTrap	&ScavTrap::operator=(ScavTrap &other)
{
	return *(new ScavTrap(other));
}

void				ScavTrap::rangedAttack(std::string const & target)
{
	if (this->_energy_points < this->_ranged_attack_damage)
	{
		std::cout << "Not enough energy to perform rangedAttack" << std::endl;
		return ;
	}
	std::cout << "ScavTrap " << this->_name << " attacks " << target;
	std::cout << " with rangedAttack, causing " << this->_ranged_attack_damage;
	std::cout << " points of damage !" << std::endl;
	this->_energy_points -= this->_ranged_attack_damage;
}

void				ScavTrap::meleeAttack(std::string const & target)
{
	if (this->_energy_points < this->_melee_attack_damage)
	{
		std::cout << "Not enough energy to perform meleeAttack" << std::endl;
		return ;
	}
	std::cout << "ScavTrap " << this->_name << " attacks " << target;
	std::cout << " with meleeAttack, causing " << this->_melee_attack_damage;
	std::cout << " points of damage !" << std::endl;
	this->_energy_points -= this->_melee_attack_damage;
}

void				ScavTrap::takeDamage(unsigned int amount)
{
	std::cout << "ScavTrap " << this->_name << " takes " << amount << " damage" << std::endl;
	amount -= this->_armor_damage_reduction;
	if (amount > this->_hit_points)
		this->_hit_points = 0;
	else
		this->_hit_points -= amount;
}

void				ScavTrap::beRepaired(unsigned int amount)
{
	std::cout << "ScavTrap " << this->_name << " is repaired : " << amount << std::endl;
	if (amount + this->_hit_points > this->_max_hit_points)
		this->_hit_points = this->_max_hit_points;
	else
		this->_hit_points += amount;
	if (amount + this->_energy_points > this->_max_energy_points)
		this->_energy_points = this->_max_energy_points;
	else
		this->_energy_points += amount;
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

void	ScavTrap::displayInfos()
{
	std::cout << "ScavTrap " << this->_name << " :" << std::endl;
	std::cout << "  hit_points             : " << this->_hit_points << std::endl;
	std::cout << "  max_hit_points         : " << this->_max_hit_points << std::endl;
	std::cout << "  energy_points          : " << this->_energy_points << std::endl;
	std::cout << "  max_energy_points      : " << this->_max_energy_points << std::endl;
	std::cout << "  level                  : " << this->_level << std::endl;
	std::cout << "  melee_attack_damage    : " << this->_melee_attack_damage << std::endl;
	std::cout << "  ranged_attack_damage   : " << this->_ranged_attack_damage << std::endl;
	std::cout << "  armor_damage_reduction : " << this->_armor_damage_reduction << std::endl;
}

unsigned int		ScavTrap::getHitPoints()
{
	return this->_hit_points;
}

unsigned int		ScavTrap::getMaxHitPoints()
{
	return this->_max_hit_points;
}

unsigned int		ScavTrap::getEnergyPoints()
{
	return this->_energy_points;
}

unsigned int		ScavTrap::getMaxEnergyPoints()
{
	return this->_max_energy_points;
}

unsigned int		ScavTrap::getLevel()
{
	return this->_level;
}

std::string const	&ScavTrap::getName()
{
	return this->_name;
}

unsigned int		ScavTrap::getMeleeAttackDamage()
{
	return this->_melee_attack_damage;
}

unsigned int		ScavTrap::getRangedAttackDamage()
{
	return this->_ranged_attack_damage;
}

unsigned int		ScavTrap::getArmorDamageReduction()
{
	return this->_armor_damage_reduction;
}