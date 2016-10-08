

#ifndef CHARACTER_H
# define CHARACTER_H

#include "AWeapon.hpp"
#include "Enemy.hpp"
#include <iostream>
#include <string>

class Character
{
	public:
		Character(std::string const & name);
		Character(Character &other);
		~Character();

		Character			&operator=(Character &other);
		void				recoverAP();
		void				equip(AWeapon* weapon);
		void				attack(Enemy* enemy);
		std::string const	&getName() const;
		int					getAP();
		std::string			getWeaponName();
		AWeapon				*getWeapon();

	protected:
		std::string const	&_name;
		int					_ap;
		AWeapon				*_weapon;

	private:
		Character();
};

std::ostream	&operator<<(std::ostream &os, Character &character);

#endif