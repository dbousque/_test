

#include "Enemy.hpp"

std::string		enemy_repr[2] = {std::string("**"), std::string("**")};

Enemy::Enemy(int x, int y) :
	GameEntity(x, y, enemy_repr, 2)
{
}

Enemy::Enemy(Enemy &other) :
	GameEntity(other)
{
}

Enemy::~Enemy()
{
}

Enemy	&Enemy::operator=(Enemy &other)
{
	return *(new Enemy(other));
}