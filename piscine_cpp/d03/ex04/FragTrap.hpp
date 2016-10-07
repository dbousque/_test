

#ifndef FRAGTRAP_H
# define FRAGTRAP_H

#include <string>
#include "ClapTrap.hpp"

class FragTrap : public ClapTrap
{
	public:
		FragTrap();
		FragTrap(std::string const &name);
		FragTrap(FragTrap &other);
		~FragTrap();
		FragTrap	&operator=(FragTrap &other);

		void				rangedAttack(std::string const & target);
		void				meleeAttack(std::string const & target);
		void				snore(std::string const & target);
		void				myAttack2(std::string const & target);
		void				myAttack3(std::string const & target);
		void				vaulthunter_dot_exe(std::string const & target);
};

#endif