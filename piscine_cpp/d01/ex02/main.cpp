

#include "ZombieEvent.hpp"
#include "Zombie.hpp"

std::string	consonants = "bcdfghjklmnpqrstvwxz";
std::string	vowels = "aeiouy";

char	random_letter(void)
{
	if (rand() % 5 >= 3)
		return consonants[rand() % consonants.length()];
	return vowels[rand() % vowels.length()];
}

std::string	get_random_name(void)
{
	std::string	to_ret;

	to_ret = "";
	for (int i = 0; i < 7; i++)
	{
		to_ret += random_letter();
	}
	to_ret[0] = std::toupper(to_ret[0]);
	return to_ret;
}

void	randomChump(void)
{
	static bool	already_called = false;

	if (!already_called)
	{
		srand(time(NULL));
		already_called = true;
	}
	Zombie	zombie = Zombie("Brainwasher", get_random_name());

	zombie.announce();
}

int		main(void)
{
	Zombie			*tmp_zombie;
	ZombieEvent		*zombie_event;

	std::cout << "Manually creating a zombie and announcing him : " << std::endl;
	tmp_zombie = new Zombie("Village idiot", "Mister Poppy");
	tmp_zombie->announce();
	delete tmp_zombie;
	std::cout << std::endl << "Calling randomChump three times : " << std::endl;
	randomChump();
	randomChump();
	randomChump();
	std::cout << std::endl;
	std::cout << "Creating a ZombieEvent with type \"Sneaky\", and creating two zombies with it :" << std::endl;
	zombie_event = new ZombieEvent();
	zombie_event->setZombieType("Sneaky");
	tmp_zombie = zombie_event->newZombie("Gérard");
	tmp_zombie->announce();
	delete tmp_zombie;
	tmp_zombie = zombie_event->newZombie("Hervé");
	tmp_zombie->announce();
	delete tmp_zombie;
	delete zombie_event;
	return (0);
}