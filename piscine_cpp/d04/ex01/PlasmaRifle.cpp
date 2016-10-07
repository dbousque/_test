

#include "PlasmaRifle.hpp"

std::string const	plasma_name = "Plasma Rifle";

PlasmaRifle::PlasmaRifle() :
	AWeapon(plasma_name, 5, 21)
{

}

PlasmaRifle::PlasmaRifle(PlasmaRifle &other) :
	AWeapon(other.getName(), other.getAPCost(), other.getDamage())
{
}

PlasmaRifle::~PlasmaRifle()
{
}

PlasmaRifle		&PlasmaRifle::operator=(PlasmaRifle &other)
{
	return other;
}

void	PlasmaRifle::attack() const
{
	std::cout << "* piouuu piouuu piouuu *" << std::endl;
}