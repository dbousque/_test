

#ifndef NINJATRAP_H
# define NINJATRAP_H

#include <string>
#include "ClapTrap.hpp"
#include "FragTrap.hpp"
#include "ScavTrap.hpp"

class NinjaTrap : public ClapTrap
{
	public:
		NinjaTrap();
		NinjaTrap(std::string const &name);
		NinjaTrap(NinjaTrap &other);
		~NinjaTrap();
		NinjaTrap	&operator=(NinjaTrap &other);

		void	ninjaShoebox(FragTrap &fragtrap);
		void	ninjaShoebox(ScavTrap &scavtrap);
		void	ninjaShoebox(NinjaTrap &ninjatrap);
		void	ninjaShoebox(ClapTrap &claptrap);
};

#endif