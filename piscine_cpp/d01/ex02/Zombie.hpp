

#ifndef ZOMBIE_H
# define ZOMBIE_H

#include <string>
#include <iostream>

class Zombie
{
	public:
		Zombie(std::string type, std::string name);
		~Zombie();
		void	announce(void) const;

	private:
		std::string const	_type;
		std::string const	_name;

};

#endif