

#ifndef WEAPON_H
#define WEAPON_H

#include <string>

class Weapon
{
	public:
		Weapon(std::string type);
		~Weapon();
		void				setType(std::string type);
		std::string const	&getType(void) const;

	private:
		std::string	_type;
};

#endif