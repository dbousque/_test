

#include "FragTrap.hpp"
#include <iostream>

std::string const	default_name = "default_name";

FragTrap::FragTrap() :
	_hit_points(100),
	_max_hit_points(100),
	_energy_points(100),
	_max_energy_points(100),
	_level(1),
	_name(default_name),
	_melee_attack_damage(30),
	_ranged_attack_damage(20),
	_armor_damage_reduction(5)
{
	std::cout << "No no no no! Cancel directive three!" << std::endl;
}

FragTrap::FragTrap(std::string const &name) :
	_hit_points(100),
	_max_hit_points(100),
	_energy_points(100),
	_max_energy_points(100),
	_level(1),
	_name(name),
	_melee_attack_damage(30),
	_ranged_attack_damage(20),
	_armor_damage_reduction(5)
{
	std::cout << "Directive one: Protect humanity! Directive two: Obey Jack at all costs. Directive three: Dance!" << std::endl;
}

FragTrap::FragTrap(FragTrap &other) :
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

FragTrap::~FragTrap()
{
}

void				FragTrap::rangedAttack(std::string const & target)
{
	if (this->_energy_points < this->_ranged_attack_damage)
	{
		std::cout << "Not enough energy to perform rangedAttack" << std::endl;
		return ;
	}
	std::cout << "FR4G-TP " << this->_name << " attacks " << target;
	std::cout << " with rangedAttack, causing " << this->_ranged_attack_damage;
	std::cout << " points of damage !" << std::endl;
	this->_energy_points -= this->_ranged_attack_damage;
}

void				FragTrap::meleeAttack(std::string const & target)
{
	if (this->_energy_points < this->_melee_attack_damage)
	{
		std::cout << "Not enough energy to perform meleeAttack" << std::endl;
		return ;
	}
	std::cout << "FR4G-TP " << this->_name << " attacks " << target;
	std::cout << " with meleeAttack, causing " << this->_melee_attack_damage;
	std::cout << " points of damage !" << std::endl;
	this->_energy_points -= this->_melee_attack_damage;
}

// make the attacker loose no energy, but weak attack
void				FragTrap::snore(std::string const & target)
{
	std::cout << "FR4G-TP " << this->_name << " attacks " << target;
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
	std::cout << "FR4G-TP " << this->_name << " attacks " << target;
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
	std::cout << "FR4G-TP " << this->_name << " attacks " << target;
	std::cout << " with myAttack3, causing " << 70;
	std::cout << " points of damage !" << std::endl;
	this->_energy_points -= 40;
	this->takeDamage(20);
}

void				FragTrap::takeDamage(unsigned int amount)
{
	std::cout << "FragTrap " << this->_name << " takes " << amount << " damage" << std::endl;
	amount -= this->_armor_damage_reduction;
	if (amount > this->_hit_points)
		this->_hit_points = 0;
	else
		this->_hit_points -= amount;
}

void				FragTrap::beRepaired(unsigned int amount)
{
	std::cout << "FragTrap " << this->_name << " is repaired : " << amount << std::endl;
	if (amount + this->_hit_points > this->_max_hit_points)
		this->_hit_points = this->_max_hit_points;
	else
		this->_hit_points += amount;
	if (amount + this->_energy_points > this->_max_energy_points)
		this->_energy_points = this->_max_energy_points;
	else
		this->_energy_points += amount;
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

void	FragTrap::displayInfos()
{
	std::cout << "FR4G-TP " << this->_name << " :" << std::endl;
	std::cout << "  hit_points             : " << this->_hit_points << std::endl;
	std::cout << "  max_hit_points         : " << this->_max_hit_points << std::endl;
	std::cout << "  energy_points          : " << this->_energy_points << std::endl;
	std::cout << "  max_energy_points      : " << this->_max_energy_points << std::endl;
	std::cout << "  level                  : " << this->_level << std::endl;
	std::cout << "  melee_attack_damage    : " << this->_melee_attack_damage << std::endl;
	std::cout << "  ranged_attack_damage   : " << this->_ranged_attack_damage << std::endl;
	std::cout << "  armor_damage_reduction : " << this->_armor_damage_reduction << std::endl;
}

unsigned int		FragTrap::getHitPoints()
{
	return this->_hit_points;
}

unsigned int		FragTrap::getMaxHitPoints()
{
	return this->_max_hit_points;
}

unsigned int		FragTrap::getEnergyPoints()
{
	return this->_energy_points;
}

unsigned int		FragTrap::getMaxEnergyPoints()
{
	return this->_max_energy_points;
}

unsigned int		FragTrap::getLevel()
{
	return this->_level;
}

std::string const	&FragTrap::getName()
{
	return this->_name;
}

unsigned int		FragTrap::getMeleeAttackDamage()
{
	return this->_melee_attack_damage;
}

unsigned int		FragTrap::getRangedAttackDamage()
{
	return this->_ranged_attack_damage;
}

unsigned int		FragTrap::getArmorDamageReduction()
{
	return this->_armor_damage_reduction;
}