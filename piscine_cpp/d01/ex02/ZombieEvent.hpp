

#ifndef ZOMBIEEVENT_H
# define ZOMBIEEVENT_H

#include "Zombie.hpp"

class ZombieEvent
{
	public:
		ZombieEvent();
		~ZombieEvent();
		void	setZombieType(std::string type);
		Zombie	*newZombie(std::string name);

	private:
		std::string		_type;
		bool			_type_set;

};

#endif