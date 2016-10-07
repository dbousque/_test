

#include "RadScorpion.hpp"
#include <iostream>

std::string const	scorpion_name = "RadScorpion";

RadScorpion::RadScorpion() :
	Enemy(80, scorpion_name)
{
	std::cout << "* click click click *" << std::endl;
}

RadScorpion::RadScorpion(RadScorpion &other) :
	Enemy(other)
{
}

RadScorpion::~RadScorpion()
{
	std::cout << "* SPROTCH *" << std::endl;
}

RadScorpion		&RadScorpion::operator=(RadScorpion &other)
{
	return other;
}