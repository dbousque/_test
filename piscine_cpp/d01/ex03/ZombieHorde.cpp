

#include "ZombieHorde.hpp"

ZombieHorde::ZombieHorde(int n) :
	_n(n)
{
	this->_zombies = new Zombie[n];
}

ZombieHorde::~ZombieHorde(void)
{
	delete [] this->_zombies;
}

void	ZombieHorde::announce(void) const
{
	for (int i = 0; i < this->_n; i++)
		this->_zombies[i].announce();
}