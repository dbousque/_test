

#ifndef BULLET_H
# define BULLET_H

#include "GameEntity.hpp"

class Bullet : public GameEntity
{
	public:
		Bullet(int x, int y, bool is_character_bullet);
		Bullet(Bullet &other);
		virtual ~Bullet();

		Bullet	&operator=(Bullet &other);
		bool	isCharacterBullet();

	private:
		Bullet();
		bool	_is_character_bullet;
};

#endif