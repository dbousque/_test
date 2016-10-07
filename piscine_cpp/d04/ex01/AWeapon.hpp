

#ifndef AWEAPON_H
# define AWEAPON_H

#include <string>

class AWeapon
{
	public:
		AWeapon(std::string const &name, int apcost, int damage);
		AWeapon(AWeapon &other);
		~AWeapon();

		std::string const	&getName() const;
		int					getAPCost() const;
		int					getDamage() const;
		virtual void		attack() const = 0;

	private:
		AWeapon();
		std::string const	&_name;
		int					_apcost;
		int					_damage;
};

#endif