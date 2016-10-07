

#include "ClapTrap.hpp"
#include <iostream>

std::string const	default_name = "default_name";
std::string			clap_name = "ClapTrap ";

ClapTrap::ClapTrap() :
	_hit_points(100),
	_max_hit_points(100),
	_energy_points(100),
	_max_energy_points(100),
	_level(1),
	_name(default_name),
	_melee_attack_damage(30),
	_ranged_attack_damage(20),
	_armor_damage_reduction(5),
	_class_name(clap_name)
{
	std::cout << "CLAPTRAP DEFAULT CONSTRUCTOR" << std::endl;
}

ClapTrap::ClapTrap(std::string const &name,
	unsigned int hit_points,
	unsigned int max_hit_points,
	unsigned int energy_points,
	unsigned int max_energy_points,
	unsigned int level,
	unsigned int melee_attack_damage,
	unsigned int ranged_attack_damage,
	unsigned int carmor_damage_reduction,
	std::string &class_name) :

	_hit_points(hit_points),
	_max_hit_points(max_hit_points),
	_energy_points(energy_points),
	_max_energy_points(max_energy_points),
	_level(level),
	_name(name),
	_melee_attack_damage(melee_attack_damage),
	_ranged_attack_damage(ranged_attack_damage),
	_armor_damage_reduction(carmor_damage_reduction),
	_class_name(class_name)
{
	std::cout << "CLAPTRAP CONSTRUCTOR" << std::endl;
}

ClapTrap::ClapTrap(ClapTrap &other) :
	_hit_points(other.getHitPoints()),
	_max_hit_points(other.getMaxHitPoints()),
	_energy_points(other.getEnergyPoints()),
	_max_energy_points(other.getMaxEnergyPoints()),
	_level(other.getLevel()),
	_name(other.getName()),
	_melee_attack_damage(other.getMeleeAttackDamage()),
	_ranged_attack_damage(other.getRangedAttackDamage()),
	_armor_damage_reduction(other.getArmorDamageReduction()),
	_class_name(other.getClassName())
{
	std::cout << "Copy constructor called for " << other.getName() << std::endl;
}

ClapTrap::~ClapTrap()
{
	std::cout << "ClapTrap " << this->_name << " deleted" << std::endl;
}

ClapTrap	&ClapTrap::operator=(ClapTrap &other)
{
	return *(new ClapTrap(other));
}

void				ClapTrap::rangedAttack(std::string const & target)
{
	if (this->_energy_points < this->_ranged_attack_damage)
	{
		std::cout << "Not enough energy to perform rangedAttack" << std::endl;
		return ;
	}
	std::cout << this->getClassName() << this->_name << " attacks " << target;
	std::cout << " with rangedAttack, causing " << this->_ranged_attack_damage;
	std::cout << " points of damage !" << std::endl;
	this->_energy_points -= this->_ranged_attack_damage;
}

void				ClapTrap::meleeAttack(std::string const & target)
{
	if (this->_energy_points < this->_melee_attack_damage)
	{
		std::cout << "Not enough energy to perform meleeAttack" << std::endl;
		return ;
	}
	std::cout << this->getClassName() << this->_name << " attacks " << target;
	std::cout << " with meleeAttack, causing " << this->_melee_attack_damage;
	std::cout << " points of damage !" << std::endl;
	this->_energy_points -= this->_melee_attack_damage;
}

void				ClapTrap::takeDamage(unsigned int amount)
{
	std::cout << this->getClassName() << this->_name << " takes " << amount << " damage" << std::endl;
	amount -= this->_armor_damage_reduction;
	if (amount > this->_hit_points)
		this->_hit_points = 0;
	else
		this->_hit_points -= amount;
}

void				ClapTrap::beRepaired(unsigned int amount)
{
	std::cout << this->getClassName() << this->_name << " is repaired : " << amount << std::endl;
	if (amount + this->_hit_points > this->_max_hit_points)
		this->_hit_points = this->_max_hit_points;
	else
		this->_hit_points += amount;
	if (amount + this->_energy_points > this->_max_energy_points)
		this->_energy_points = this->_max_energy_points;
	else
		this->_energy_points += amount;
}

void	ClapTrap::displayInfos()
{
	std::cout << this->getClassName() << this->_name << " :" << std::endl;
	std::cout << "  hit_points             : " << this->_hit_points << std::endl;
	std::cout << "  max_hit_points         : " << this->_max_hit_points << std::endl;
	std::cout << "  energy_points          : " << this->_energy_points << std::endl;
	std::cout << "  max_energy_points      : " << this->_max_energy_points << std::endl;
	std::cout << "  level                  : " << this->_level << std::endl;
	std::cout << "  melee_attack_damage    : " << this->_melee_attack_damage << std::endl;
	std::cout << "  ranged_attack_damage   : " << this->_ranged_attack_damage << std::endl;
	std::cout << "  armor_damage_reduction : " << this->_armor_damage_reduction << std::endl;
}

unsigned int		ClapTrap::getHitPoints()
{
	return this->_hit_points;
}

unsigned int		ClapTrap::getMaxHitPoints()
{
	return this->_max_hit_points;
}

unsigned int		ClapTrap::getEnergyPoints()
{
	return this->_energy_points;
}

unsigned int		ClapTrap::getMaxEnergyPoints()
{
	return this->_max_energy_points;
}

unsigned int		ClapTrap::getLevel()
{
	return this->_level;
}

std::string const	&ClapTrap::getName()
{
	return this->_name;
}

unsigned int		ClapTrap::getMeleeAttackDamage()
{
	return this->_melee_attack_damage;
}

unsigned int		ClapTrap::getRangedAttackDamage()
{
	return this->_ranged_attack_damage;
}

unsigned int		ClapTrap::getArmorDamageReduction()
{
	return this->_armor_damage_reduction;
}

std::string			&ClapTrap::getClassName()
{
	return this->_class_name;
}