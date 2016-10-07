

#include "Victim.hpp"

Victim::Victim()
{
}

Victim::Victim(std::string name) :
	_name(name)
{
	std::cout << "Some random victim called " << this->_name << " just popped !" << std::endl;
}

Victim::Victim(Victim &other) :
	_name(other.getName())
{
}

Victim::~Victim()
{
	std::cout << "Victim " << this->_name << " just died for no apparent reason !" << std::endl;
}

Victim	&Victim::operator=(Victim &other)
{
	this->_name = other.getName();
	return *this;
}

std::string	&Victim::getName()
{
	return this->_name;
}

void	Victim::getPolymorphed() const
{
	std::cout << this->_name << " has been turned into a cute little sheep !" << std::endl;
}

std::ostream	&operator<<(std::ostream &os, Victim &vict)
{
	os << "I'm " << vict.getName() << " and I like otters !" << std::endl;
	return os;
}