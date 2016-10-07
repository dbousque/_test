

#ifndef POWERFIST_H
# define POWERFIST_H

#include <string>
#include "AWeapon.hpp"
#include <iostream>

class PowerFist : public AWeapon
{
	public:
		PowerFist();
		PowerFist(PowerFist &other);
		virtual ~PowerFist();

		PowerFist		&operator=(PowerFist &other);
		void			attack() const;
};

#endif