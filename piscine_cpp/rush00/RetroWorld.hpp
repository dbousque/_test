

#ifndef RETROWORLD_H
# define RETROWORLD_H

#include <sys/time.h>
#include <cstdlib>
#include "GameEntity.hpp"
#include "Enemy.hpp"
#include "Background.hpp"
#include "Bullet.hpp"
#include "Config.hpp"

class RetroWorld
{
	public:
		RetroWorld();
		RetroWorld(RetroWorld &other);
		virtual ~RetroWorld();

		RetroWorld	&operator=(RetroWorld &other);
		bool		updateVars();
		void		displayStuff();
		void		displayGameInfos();
		void		characterLeft();
		void		characterRight();
		void		characterUp();
		void		characterDown();
		void		characterShoot();
		GameEntity	&getCharacter();
		Enemy		**getEnemies();
		Background	**getBackgrounds();
		Bullet		**getBullets();
		int			getNbEnemies();
		int			getNbBackgrounds();
		int			getNbBullets();
		int			getScore();
		int			getLife();
		time_t		getTime();
		suseconds_t	getuTime();
		void		addTime(time_t s);	// Add s to _time
		void		adduTime(suseconds_t ms); // Add ms to _uTime

	private:
		void		_checkDeads();
		void		_checkEnemyCollision();
		void		_removeOutOfBounds(GameEntity **entities, int *nb);
		void		_addToList(GameEntity **list, GameEntity *elt, int nb_max, int *ind);
		GameEntity	&_character;
		Enemy		**_enemies;
		Background	**_backgrounds;
		Bullet		**_bullets;
		int			_nb_enemies;
		int			_nb_backgrounds;
		int			_nb_bullets;
		int			_score;
		int			_life;
		time_t		_time;	// Time since the start of the game, in second
		suseconds_t	_uTime;	// Time since the start of the game in milliseconds
};

#endif