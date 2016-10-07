

#include "PowerFist.hpp"

std::string const	plasma_name = "Power Fist";

PowerFist::PowerFist() :
	AWeapon(plasma_name, 8, 50)
{

}

PowerFist::PowerFist(PowerFist &other) :
	AWeapon(other.getName(), other.getAPCost(), other.getDamage())
{
}

PowerFist::~PowerFist()
{
}

PowerFist		&PowerFist::operator=(PowerFist &other)
{
	return other;
}

void	PowerFist::attack() const
{
	std::cout << "* pschhh... SBAM! *" << std::endl;
}