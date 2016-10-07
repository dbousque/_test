

#ifndef RADSCORPION_H
# define RADSCORPION_H

#include "Enemy.hpp"

class RadScorpion : public Enemy
{
	public:
		RadScorpion();
		RadScorpion(RadScorpion &other);
		virtual ~RadScorpion();

		RadScorpion		&operator=(RadScorpion &other);
};

#endif