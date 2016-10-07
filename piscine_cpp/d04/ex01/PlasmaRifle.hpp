

#ifndef PLASMARIFLE_H
# define PLASMARIFLE_H

#include <string>
#include "AWeapon.hpp"
#include <iostream>

class PlasmaRifle : public AWeapon
{
	public:
		PlasmaRifle();
		PlasmaRifle(PlasmaRifle &other);
		virtual ~PlasmaRifle();

		PlasmaRifle		&operator=(PlasmaRifle &other);
		void			attack() const;
};

#endif