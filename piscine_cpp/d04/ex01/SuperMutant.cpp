

#include "SuperMutant.hpp"
#include <iostream>

std::string const	mutant_name = "Super Mutant";

SuperMutant::SuperMutant() :
	Enemy(170, mutant_name)
{
	std::cout << "Gaaah. Me want smash heads !" << std::endl;
}

SuperMutant::SuperMutant(SuperMutant &other) :
	Enemy(other)
{
}

SuperMutant::~SuperMutant()
{
	std::cout << "Aaargh ..." << std::endl;
}

SuperMutant		&SuperMutant::operator=(SuperMutant &other)
{
	return other;
}

void	SuperMutant::takeDamage(int amount)
{
	this->Enemy::takeDamage(amount - 3);
}