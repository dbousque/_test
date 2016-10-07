

#ifndef NINJATRAP_H
# define NINJATRAP_H

#include <string>
#include "ClapTrap.hpp"

class NinjaTrap : public ClapTrap
{
	public:
		NinjaTrap();
		NinjaTrap(std::string const &name);
		NinjaTrap(NinjaTrap &other);
		~NinjaTrap();
		NinjaTrap	&operator=(NinjaTrap &other);

		void				challenge1();
		void				challenge2();
		void				challenge3();
		void				challengeNewcomer();
};

#endif