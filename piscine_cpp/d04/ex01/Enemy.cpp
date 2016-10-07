

#include "Enemy.hpp"

Enemy::Enemy(int hp, std::string const & type) :
	_type(type),
	_hp(hp)
{
}

Enemy::Enemy(Enemy &other) :
	_type(other.getType()),
	_hp(other.getHP())
{
}

Enemy::~Enemy()
{
}

Enemy				&Enemy::operator=(Enemy &other)
{
	return other;
}

std::string const	&Enemy::getType() const
{
	return this->_type;
}

int					Enemy::getHP() const
{
	return this->_hp;
}

void		Enemy::takeDamage(int amount)
{
	if (amount >= 0)
	{
		this->_hp -= amount;
		if (this->_hp < 0)
			this->_hp = 0;
	}
}