

#include "Caval.hpp"

Caval::Caval() : Victim()
{
}

Caval::Caval(std::string name) : Victim(name)
{
	std::cout << "ca frite ?" << std::endl;
}

Caval::Caval(Caval &other) : Victim(other)
{
}

Caval::~Caval()
{
	std::cout << "lol i'm dying" << std::endl;
}

Caval		&Caval::operator=(Caval &other)
{
	this->_name = other.getName();
	return *this;
}

void		Caval::getPolymorphed() const
{
	std::cout << this->_name << " has been turned into a red carpet !" << std::endl;
}