

#ifndef HUMANA_H
# define HUMANA_H

#include "Weapon.hpp"

class HumanA
{
	public:
		HumanA(std::string name, Weapon &weapon);
		~HumanA();
		void	attack(void) const;

	private:
		std::string const	_name;
		Weapon				&_weapon;
};

#endif