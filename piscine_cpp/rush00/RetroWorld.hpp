

#ifndef RETROWORLD_H
# define RETROWORLD_H

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
		~RetroWorld();

		RetroWorld	&operator=(RetroWorld &other);
		void		updateVars();
		void		displayStuff();
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

	private:
		void		_addToList(GameEntity **list, GameEntity *elt, int nb_max, int *ind);
		GameEntity	&_character;
		Enemy		**_enemies;
		Background	**_backgrounds;
		Bullet		**_bullets;
		int			_nb_enemies;
		int			_nb_backgrounds;
		int			_nb_bullets;
};

#endif