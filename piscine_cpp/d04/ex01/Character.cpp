

#include "Character.hpp"

Character::Character(std::string const & name) :
	_name(name),
	_ap(40),
	_weapon(NULL)
{
}

Character::Character(Character &other) :
	_name(other.getName()),
	_ap(other.getAP()),
	_weapon(other.getWeapon())
{
}

Character::~Character()
{
}

Character			&Character::operator=(Character &other)
{
	return other;
}

void				Character::recoverAP()
{
	this->_ap += 10;
	if (this->_ap > 40)
		this->_ap = 40;
}

void				Character::equip(AWeapon* weapon)
{
	this->_weapon = weapon;
}

void				Character::attack(Enemy* enemy)
{
	if (!this->_weapon || !enemy)
		return ;
	if (this->_ap < this->_weapon->getAPCost())
		return ;
	std::cout << this->_name << " attacks " << enemy->getType();
	std::cout << " with a " << this->_weapon->getName() << std::endl;
	this->_weapon->attack();
	enemy->takeDamage(this->_weapon->getDamage());
	if (enemy->getHP() <= 0)
		delete enemy;
	this->_ap -= this->_weapon->getAPCost();
	if (this->_ap < 0)
		this->_ap = 0;
}

std::string const	&Character::getName() const
{
	return this->_name;
}

int		Character::getAP()
{
	return this->_ap;
}

std::string		Character::getWeaponName()
{
	if (this->_weapon)
		return this->_weapon->getName();
	return "NULL";
}

AWeapon			*Character::getWeapon()
{
	return this->_weapon;
}

std::ostream	&operator<<(std::ostream &os, Character &character)
{
	if (!character.getWeapon())
	{
		os << character.getName() << " has " << character.getAP();
		os << " AP and is unarmed" << std::endl;
	}
	else
	{
		os << character.getName() << " has " << character.getAP();
		os << " AP and wields a " << character.getWeaponName() << std::endl;
	}
	return os;
}