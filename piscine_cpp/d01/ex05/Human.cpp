

#include "Human.hpp"

Human::Human() :
	_brain(Brain())
{
}

Human::~Human()
{
}

std::string	Human::identify(void) const
{
	return this->_brain.identify();
}

Brain const	&Human::getBrain(void) const
{
	return this->_brain;
}