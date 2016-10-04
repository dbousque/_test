

#include "Weapon.hpp"

Weapon::Weapon(std::string type) :
	_type(type)
{
}

Weapon::~Weapon()
{
}

void	Weapon::setType(std::string type)
{
	this->_type = type;
}

std::string const	&Weapon::getType(void) const
{
	return this->_type;
}