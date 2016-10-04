

#include "ZombieHorde.hpp"

int		main(void)
{
	ZombieHorde	horde = ZombieHorde(10);

	std::cout << "Created ZombieHorde of 10 zombies, and calling announce :" << std::endl;
	horde.announce();
	return (0);
}