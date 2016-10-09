

#include "RetroWorld.hpp"

std::string		character_repr[4] = {
	std::string("   _        "),
	std::string("   \\ \\_____ "),
	std::string("###[==_____>"),
	std::string("   /_/      ")
};

RetroWorld::RetroWorld() :
	_character(*(new GameEntity(100, Config::win_height * Config::scale_y / 2, character_repr, 4, COLOR_WHITE))),
	_enemies(new Enemy*[16]),
	_backgrounds(new Background*[16]),
	_bullets(new Bullet*[128]),
	_nb_enemies(0),
	_nb_backgrounds(0),
	_nb_bullets(0),
	_score(0),
	_life(50)
{
	Background	*back = new Background(0, ((Config::win_height - 1) * Config::scale_y) - (13 * Config::scale_y));
	back->setVelocityX(-3);
	this->_addToList((GameEntity**)this->_backgrounds, back, 16, &(this->_nb_backgrounds));
}

RetroWorld::RetroWorld(RetroWorld &other) :
	_character(other.getCharacter()),
	_enemies(other.getEnemies()),
	_backgrounds(other.getBackgrounds()),
	_bullets(other.getBullets()),
	_nb_enemies(other.getNbEnemies()),
	_nb_backgrounds(other.getNbBackgrounds()),
	_nb_bullets(other.getNbBullets()),
	_score(other.getScore()),
	_life(other.getLife())
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

void	RetroWorld::_removeOutOfBounds(GameEntity **entities, int *nb)
{
	for (int i = 0; i < *nb; i++)
	{
		if (entities[i]->outOfBounds())
		{
			(*nb)--;
			for (int x = i; x < *nb; x++)
				entities[x] = entities[x + 1];
			i--;
		}
	}
}

void	RetroWorld::_checkDeads()
{
	bool	remove;

	for (int i = 0; i < this->_nb_bullets; i++)
	{
		if (!this->_bullets[i]->isCharacterBullet())
		{
			if (this->_bullets[i]->touches(this->_character))
			{
				this->_life -= 5;
				this->_nb_bullets--;
				for (int x = i; x < this->_nb_bullets; x++)
					this->_bullets[x] = this->_bullets[x + 1];
				i--;
			}
		}
		else
		{
			remove = false;
			for (int x = 0; x < this->_nb_enemies; x++)
			{
				if (this->_bullets[i]->touches(*(this->_enemies[x])))
				{
					remove = true;
					this->_enemies[x]->takeShoot(5);
					this->_score += 5;
					if (this->_score % 50)
					{
						this->_life += 1;
						if (this->_life > 100)
							this->_life = 100;
					}
					if (this->_enemies[x]->getLife() <= 0)
					{
						this->_nb_enemies--;
						for (int y = x; y < this->_nb_enemies; y++)
							this->_enemies[y] = this->_enemies[y + 1];
						x--;
					}
				}
			}
			if (remove)
			{
				this->_nb_bullets--;
				for (int z = i; z < this->_nb_bullets; z++)
					this->_bullets[z] = this->_bullets[z + 1];
				i--;
			}
		}
	}
}

void	RetroWorld::_checkEnemyCollision()
{
	for (int i = 0; i < this->_nb_enemies; i++)
	{
		if (this->_character.touches(*(this->_enemies[i])))
			this->_life -= 5;
	}
}

bool	RetroWorld::updateVars()
{
	static bool		already_boss = false;
	static int		count = 0;
	int				target_nb_enemies;

	Background		*back;

	this->_checkDeads();
	this->_checkEnemyCollision();
	if (this->_life <= 0)
		return false;
	if (!already_boss && this->_score % ((100 + (this->_score / 5)) / 5 * 5) == 0 && this->_score != 0)
	{
		already_boss = true;
		Enemy	*new_enemy = new Enemy((Config::win_width - 5) * Config::scale_x, (rand() % Config::win_height) * Config::scale_y, 0);
		this->_addToList((GameEntity**)this->_enemies, new_enemy, 16, &(this->_nb_enemies));
	}
	else if (this->_score % ((100 + (this->_score / 5)) / 5 * 5) != 0)
		already_boss = false;
	target_nb_enemies = (this->_score / (35 + (this->_score / 10))) + 1;
	if (target_nb_enemies > 16)
		target_nb_enemies = 16;
	if (this->_nb_enemies < target_nb_enemies)
	{
		while (this->_nb_enemies < target_nb_enemies)
		{
			Enemy	*new_enemy = new Enemy((Config::win_width - 5) * Config::scale_x, (rand() % Config::win_height) * Config::scale_y, 1);
			this->_addToList((GameEntity**)this->_enemies, new_enemy, 16, &(this->_nb_enemies));
		}
	}
	if (this->_backgrounds[this->_nb_backgrounds - 1]->getX() < (Config::win_width * Config::scale_x) * 0.7 && count % 2 == 0)
	{
		back = new Background(Config::win_width * Config::scale_x, 0);
		back->setVelocityX(-3);
		this->_addToList((GameEntity**)this->_backgrounds, back, 16, &(this->_nb_backgrounds));
		count++;
	}
	else if (this->_backgrounds[this->_nb_backgrounds - 1]->getX() < (Config::win_width * Config::scale_x) * 0.3 && count % 2 == 1)
	{
		back = new Background(Config::win_width * Config::scale_x,
				((Config::win_height - 1) * Config::scale_y) - (13 * Config::scale_y));
		back->setVelocityX(-3);
		this->_addToList((GameEntity**)this->_backgrounds, back, 16, &(this->_nb_backgrounds));
		count++;
	}
	for (int i = 0; i < this->_nb_backgrounds; i++)
		this->_backgrounds[i]->moveVelocity();
	for (int i = 0; i < this->_nb_enemies; i++)
	{
		if (this->_enemies[i]->maybeShoot())
		{
			Bullet	*new_bullet = new Bullet(this->_enemies[i]->getX() - this->_enemies[i]->getReprLenAtScale() - 1,
									this->_enemies[i]->getY() + (this->_enemies[i]->getReprHeightAtScale() / 2), false, 0);
			new_bullet->setVelocityX(-9);
			this->_addToList((GameEntity**)this->_bullets, new_bullet, 128, &(this->_nb_bullets));
		}
		this->_enemies[i]->moveVelocity();
	}
	for (int i = 0; i < this->_nb_bullets; i++)
		this->_bullets[i]->moveVelocity();
	this->_removeOutOfBounds((GameEntity**)this->_backgrounds, &(this->_nb_backgrounds));
	this->_removeOutOfBounds((GameEntity**)this->_bullets, &(this->_nb_bullets));
	return true;
}

void	RetroWorld::displayStuff()
{
	for (int i = 0; i < this->_nb_backgrounds; i++)
		this->_backgrounds[i]->display();
	for (int i = 0; i < this->_nb_bullets; i++)
		this->_bullets[i]->display();
	this->_character.display();
	for (int i = 0; i < this->_nb_enemies; i++)
		this->_enemies[i]->display();
}

void	RetroWorld::displayGameInfos()
{
	int				y = Config::start_y - 2, x = Config::start_x - 1, lifeGradient = 33, i = 0;
	char			s_life[] = "Life: ", s_score[] = "Score: ", s_time[] = "Elapsed time: ";

// Display Life bar
	mvaddstr(y, x, s_life);
	x += strlen(s_life);

// Red part of life bar
	attron(COLOR_PAIR(9));
	for (; i < lifeGradient && i < this->_life; i++, x++)
		mvaddch(y, x, '|');
	attroff(COLOR_PAIR(9));

	lifeGradient += lifeGradient;
// Yellow
	attron(COLOR_PAIR(10));
	for (; i < lifeGradient && i < this->_life; i++, x++)
		mvaddch(y, x, '|');
	attroff(COLOR_PAIR(10));

	lifeGradient += lifeGradient + 1;
// Green
	attron(COLOR_PAIR(11));
	for (; i < lifeGradient && i < this->_life; i++, x++)
		mvaddch(y, x, '|');
	attroff(COLOR_PAIR(11));

// Display score
	y = Config::start_y - 3; x = Config::start_x - 1;
	mvaddstr(y, x, s_score);
	x += strlen(s_score);
	mvaddstr(y, x, std::to_string(this->_score).c_str());

// Game time in seconds
	y = Config::start_y - 2; x = (Config::start_x + Config::win_width) - (strlen(s_time) + 3);
	mvaddstr(y, x, s_time);
	x += strlen(s_time);
	mvaddstr(y, x, std::to_string(this->getuTime() / 1000).c_str());
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
									this->_character.getY() + (this->_character.getReprHeightAtScale() / 2), true, COLOR_GREEN);
	new_bullet->setVelocityX(9);
	this->_addToList((GameEntity**)this->_bullets, new_bullet, 128, &(this->_nb_bullets));
	if (this->_score >= 400)
	{
		new_bullet = new Bullet(this->_character.getX() + this->_character.getReprLenAtScale() + 1,
									this->_character.getY() + (this->_character.getReprHeightAtScale() / 2), true, COLOR_CYAN);
		new_bullet->setVelocityX(7);
		new_bullet->setVelocityY(3);
		this->_addToList((GameEntity**)this->_bullets, new_bullet, 128, &(this->_nb_bullets));
		new_bullet = new Bullet(this->_character.getX() + this->_character.getReprLenAtScale() + 1,
									this->_character.getY() + (this->_character.getReprHeightAtScale() / 2), true, COLOR_CYAN);
		new_bullet->setVelocityX(7);
		new_bullet->setVelocityY(-3);
		this->_addToList((GameEntity**)this->_bullets, new_bullet, 128, &(this->_nb_bullets));
	}
	if ((this->_score >= 100 && this->_score < 400) || this->_score >= 800)
	{
		new_bullet = new Bullet(this->_character.getX() + this->_character.getReprLenAtScale() + 1,
									(this->_character.getY() + (1 * Config::scale_y)) + (this->_character.getReprHeightAtScale() / 2), true, COLOR_BLUE);
		new_bullet->setVelocityX(13);
		this->_addToList((GameEntity**)this->_bullets, new_bullet, 128, &(this->_nb_bullets));
		new_bullet = new Bullet(this->_character.getX() + this->_character.getReprLenAtScale() + 1,
									(this->_character.getY() - (1 * Config::scale_y)) + (this->_character.getReprHeightAtScale() / 2), true, COLOR_BLUE);
		new_bullet->setVelocityX(13);
		this->_addToList((GameEntity**)this->_bullets, new_bullet, 128, &(this->_nb_bullets));
	}
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

int		RetroWorld::getScore()
{
	return this->_score;
}

int		RetroWorld::getLife()
{
	return this->_life;
}

time_t	RetroWorld::getTime()
{
	return this->_time;
}

suseconds_t		RetroWorld::getuTime()
{
	return this->_uTime;
}

void	RetroWorld::addTime(time_t s)
{
	this->_time += s;
}

void	RetroWorld::adduTime(suseconds_t ms)
{
	this->_uTime += ms;
}