

#include "Sorcerer.hpp"

Sorcerer::Sorcerer()
{
}

Sorcerer::Sorcerer(std::string name, std::string title) :
	_name(name),
	_title(title)
{
	std::cout << this->_name << ", " << this->_title << " is born !" << std::endl;
}

Sorcerer::Sorcerer(Sorcerer &other) :
	_name(other.getName()),
	_title(other.getTitle())
{
}

Sorcerer::~Sorcerer()
{
	std::cout << this->_name << ", " << this->_title << " is dead. Consequences will never be the same !" << std::endl;
}

Sorcerer	&Sorcerer::operator=(Sorcerer &other)
{
	this->_name = other.getName();
	this->_title = other.getName();
	return *this;
}

std::string	&Sorcerer::getName()
{
	return this->_name;
}

std::string	&Sorcerer::getTitle()
{
	return this->_title;
}

void	Sorcerer::polymorph(Victim const &vict) const
{
	vict.getPolymorphed();
}

std::ostream	&operator<<(std::ostream &os, Sorcerer &sorc)
{
	os << "I am " << sorc.getName() << ", " << sorc.getTitle() << ", and I like ponies !" << std::endl;
	return os;
}