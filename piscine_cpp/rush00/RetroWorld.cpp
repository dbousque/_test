

#include "RetroWorld.hpp"
#include <iostream>

std::string		character_repr[4] = {
	std::string("   _        "),
	std::string("   \\ \\_____ "),
	std::string("###[==_____>"),
	std::string("   /_/      ")
};

RetroWorld::RetroWorld() :
	_character(*(new GameEntity(100, Config::win_height * Config::scale_y / 2, character_repr, 4))),
	_enemies(new Enemy*[16]),
	_backgrounds(new Background*[16]),
	_bullets(new Bullet*[128]),
	_nb_enemies(0),
	_nb_backgrounds(0),
	_nb_bullets(0)
{
}

RetroWorld::RetroWorld(RetroWorld &other) :
	_character(other.getCharacter()),
	_enemies(other.getEnemies()),
	_backgrounds(other.getBackgrounds()),
	_bullets(other.getBullets()),
	_nb_enemies(other.getNbEnemies()),
	_nb_backgrounds(other.getNbBackgrounds()),
	_nb_bullets(other.getNbBullets())
{
}

RetroWorld::~RetroWorld()
{
	delete &(this->_character);
	for (int i = 0; i < this->_nb_enemies; i++)
		delete this->_enemies[i];
	delete [] this->_enemies;
	for (int i = 0; i < this->_nb_backgrounds; i++)
		delete this->_backgrounds[i];
	delete [] this->_backgrounds;
	for (int i = 0; i < this->_nb_bullets; i++)
		delete this->_bullets[i];
	delete [] this->_bullets;
}

RetroWorld	&RetroWorld::operator=(RetroWorld &other)
{
	return *(new RetroWorld(other));
}

void	RetroWorld::updateVars()
{
	for (int i = 0; i < this->_nb_bullets; i++)
		this->_bullets[i]->moveVelocity();
}

void	RetroWorld::displayStuff()
{
	this->_character.display();
	for (int i = 0; i < this->_nb_enemies; i++)
		this->_enemies[i]->display();
	for (int i = 0; i < this->_nb_backgrounds; i++)
		this->_backgrounds[i]->display();
	for (int i = 0; i < this->_nb_bullets; i++)
		this->_bullets[i]->display();
}

void		RetroWorld::characterLeft()
{
	this->_character.move(-1 * Config::scale_x, 0);
}

void		RetroWorld::characterRight()
{
	this->_character.move(1 * Config::scale_x, 0);
}

void		RetroWorld::characterUp()
{
	this->_character.move(0, -1 * Config::scale_y);
}

void		RetroWorld::characterDown()
{
	this->_character.move(0, 1 * Config::scale_y);
}

void		RetroWorld::characterShoot()
{
	Bullet	*new_bullet = new Bullet(this->_character.getX() + this->_character.getReprLenAtScale() + 1,
									this->_character.getY() + (this->_character.getReprHeightAtScale() / 2), true);
	new_bullet->setVelocityX(9);
	this->_addToList((GameEntity**)this->_bullets, new_bullet, 128, &(this->_nb_bullets));
}

void		RetroWorld::_addToList(GameEntity **list, GameEntity *elt, int nb_max, int *ind)
{
	if (*ind < nb_max)
	{
		list[*ind] = elt;
		(*ind)++;
	}
}

GameEntity	&RetroWorld::getCharacter()
{
	return this->_character;
}

Enemy		**RetroWorld::getEnemies()
{
	return this->_enemies;
}

Background	**RetroWorld::getBackgrounds()
{
	return this->_backgrounds;
}

Bullet		**RetroWorld::getBullets()
{
	return this->_bullets;
}

int			RetroWorld::getNbEnemies()
{
	return this->_nb_enemies;
}

int			RetroWorld::getNbBackgrounds()
{
	return this->_nb_backgrounds;
}

int			RetroWorld::getNbBullets()
{
	return this->_nb_bullets;
}