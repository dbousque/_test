

#include "Peon.hpp"

Peon::Peon() : Victim()
{
}

Peon::Peon(std::string name) : Victim(name)
{
	std::cout << "Zog zog." << std::endl;
}

Peon::Peon(Peon &other) : Victim(other)
{
}

Peon::~Peon()
{
	std::cout << "Bleuark..." << std::endl;
}

Peon		&Peon::operator=(Peon &other)
{
	this->_name = other.getName();
	return *this;
}

void		Peon::getPolymorphed() const
{
	std::cout << this->_name << " has been turned into a pink pony !" << std::endl;
}