

#ifndef ZOMBIEHORDE_H
# define ZOMBIEHORDE_H

#include "Zombie.hpp"

class ZombieHorde
{
	public:
		ZombieHorde(int n);
		~ZombieHorde();
		void	announce(void) const;

	private:
		Zombie		*_zombies;
		int const	_n;

};

#endif