

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

Zombie::Zombie(void) :
	_type("SheepZombie"),
	_name(get_random_name())
{
}

Zombie::Zombie(std::string const type, std::string const name) :
	_type(type),
	_name(name)
{
}

Zombie::~Zombie()
{
}

void	Zombie::announce(void) const
{
	std::cout << "<Zombie \"" << this->_name << "\" (";
	std::cout << this->_type << ")> " << "Brainzzz..." << std::endl;
}