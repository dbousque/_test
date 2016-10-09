

#ifndef ENEMY_H
# define ENEMY_H

#include "GameEntity.hpp"

class Enemy : public GameEntity
{
	public:
		Enemy(int x, int y);
		Enemy(Enemy &other);
		virtual ~Enemy();

		Enemy	&operator=(Enemy &other);

	private:
		Enemy();
};

#endif