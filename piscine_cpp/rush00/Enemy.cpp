

#include "Enemy.hpp"

std::string		enemy_repr[3] = {std::string("**"), std::string("**"), std::string("**")};
std::string		boss_repr[5] = {
	std::string("****"),
	std::string("****"),
	std::string("****"),
	std::string("****"),
	std::string("****")
};

Enemy::Enemy(int x, int y, int type) :
	GameEntity(x, y,
		type == 1 ? enemy_repr : boss_repr,
		type == 1 ? 3 : 5, type == 1 ? COLOR_RED : COLOR_MAGENTA)
{
	this->_value = type == 1 ? 5 : 30;
	this->_iter_shoot = type == 1 ? (rand() % 60 + 60) : (rand() % 20 + 10);
	this->_iter_change_dir = 1;
	this->_life = type == 1 ? 10 : 100;
	this->_type = type;
}

Enemy::Enemy(Enemy &other) :
	GameEntity(other),
	_value(other.getValue()),
	_iter_shoot(other.getIterShoot()),
	_iter_change_dir(other.getIterChangeDir()),
	_life(other.getLife()),
	_type(other.getType())
{
}

Enemy::~Enemy()
{
}

Enemy	&Enemy::operator=(Enemy &other)
{
	return *(new Enemy(other));
}

void	Enemy::moveVelocity()
{
	this->_iter_change_dir--;
	if (this->_iter_change_dir == 0)
	{
		this->_iter_change_dir = rand() % 50 + 130;
		this->setVelocityX(rand() % 8 - 3);
		this->setVelocityY(rand() % 8 - 4);
	}
	this->GameEntity::moveVelocity();
}

bool	Enemy::maybeShoot()
{
	this->_iter_shoot--;
	if (this->_iter_shoot == 0)
	{
		this->_iter_shoot = this->_type == 1 ? (rand() % 80 + 80) : (rand() % 30 + 30);
		return true;
	}
	return false;
}

void	Enemy::takeShoot(int val)
{
	this->_life -= val;
}

int		Enemy::getValue()
{
	return this->_value;
}

int		Enemy::getIterShoot()
{
	return this->_iter_shoot;
}

int		Enemy::getIterChangeDir()
{
	return this->_iter_change_dir;
}

int		Enemy::getLife()
{
	return this->_life;
}

int		Enemy::getType()
{
	return this->_type;
}