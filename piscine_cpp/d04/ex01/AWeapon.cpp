

#include "AWeapon.hpp"

std::string	default_name = "salut";

AWeapon::AWeapon() :
	_name(default_name)
{
}

AWeapon::AWeapon(std::string const &name, int apcost, int damage) :
	_name(name),
	_apcost(apcost),
	_damage(damage)
{
}

AWeapon::AWeapon(AWeapon &other) :
	_name(other.getName()),
	_apcost(other.getAPCost()),
	_damage(other.getDamage())
{
}

AWeapon::~AWeapon()
{
}

AWeapon				&AWeapon::operator=(AWeapon &other)
{
	return other;
}

std::string const	&AWeapon::getName() const
{
	return this->_name;
}

int			AWeapon::getAPCost() const
{
	return this->_apcost;
}

int			AWeapon::getDamage() const
{
	return this->_damage;
}