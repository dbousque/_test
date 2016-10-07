

#ifndef SCAVTRAP_H
# define SCAVTRAP_H

#include <string>
#include "ClapTrap.hpp"

class ScavTrap : public ClapTrap
{
	public:
		ScavTrap();
		ScavTrap(std::string const &name);
		ScavTrap(ScavTrap &other);
		~ScavTrap();
		ScavTrap	&operator=(ScavTrap &other);

		void				challenge1();
		void				challenge2();
		void				challenge3();
		void				challengeNewcomer();
};

#endif