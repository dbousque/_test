

#include "Zombie.hpp"

Zombie::Zombie(std::string const type, std::string const name) :
	_type(type),
	_name(name)
{
}

Zombie::~Zombie()
{
}

void	Zombie::announce(void) const
{
	std::cout << "<Zombie \"" << this->_name << "\" (";
	std::cout << this->_type << ")> " << "Brainzzz..." << std::endl;
}