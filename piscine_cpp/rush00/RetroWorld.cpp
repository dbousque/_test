

#include "RetroWorld.hpp"
#include <iostream>

RetroWorld::RetroWorld() :
	_character(*(new Character)),
	_enemies(new Enemy*[16]),
	_backgrounds(new Background*[16]),
	_bullets(new Bullet*[128])
{
}

RetroWorld::RetroWorld(RetroWorld &other) :
	_character(other.getCharacter()),
	_enemies(other.getEnemies()),
	_backgrounds(other.getBackgrounds()),
	_bullets(other.getBullets())
{
}

RetroWorld::~RetroWorld()
{
	delete this->_character;
	delete this->_enemies;
	delete this->_backgrounds;
	delete this->_bullets;
}

RetroWorld	&RetroWorld::operator=(RetroWorld &other)
{
	return *(new RetroWorld(other));
}

void		RetroWorld::characterLeft()
{
	this->_character.left();
}

void		RetroWorld::characterRight()
{
	this->_character.right();
}

void		RetroWorld::characterUp()
{
	this->_character.up();
}

void		RetroWorld::characterDown()
{
	this->_character.down();
}

void		RetroWorld::characterShoot()
{
	this->_character.shoot();
}