

#include "Bullet.hpp"

std::string		bullet_repr[1] = {std::string("--")};

Bullet::Bullet(int x, int y, bool is_character_bullet, int color) :
	GameEntity(x, y, bullet_repr, 1, is_character_bullet ? color : COLOR_RED),
	_is_character_bullet(is_character_bullet)
{
}

Bullet::Bullet(Bullet &other) :
	GameEntity(other),
	_is_character_bullet(other.isCharacterBullet())
{
}

Bullet::~Bullet()
{
}

Bullet	&Bullet::operator=(Bullet &other)
{
	return *(new Bullet(other));
}

bool	Bullet::isCharacterBullet()
{
	return this->_is_character_bullet;
}