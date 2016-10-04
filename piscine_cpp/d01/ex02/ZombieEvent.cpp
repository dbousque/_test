

#include "ZombieEvent.hpp"

ZombieEvent::ZombieEvent() : _type_set(false)
{
}

ZombieEvent::~ZombieEvent()
{
}

void	ZombieEvent::setZombieType(std::string type)
{
	this->_type_set = true;
	this->_type = type;
}

Zombie	*ZombieEvent::newZombie(std::string name)
{
	if (!this->_type_set)
	{
		std::cout << "The ZombieEvent type has not been set, unable to create zombie." << std::endl;
		return (NULL);
	}
	return (new Zombie(this->_type, name));
}