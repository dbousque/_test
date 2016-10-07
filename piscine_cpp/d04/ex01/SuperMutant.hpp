

#ifndef SUPERMUTANT_H
# define SUPERMUTANT_H

#include "Enemy.hpp"

class SuperMutant : public Enemy
{
	public:
		SuperMutant();
		SuperMutant(SuperMutant &other);
		virtual ~SuperMutant();

		SuperMutant		&operator=(SuperMutant &other);
		virtual void	takeDamage(int amount);
};

#endif