

#ifndef RETROWORLD_H
# define RETROWORLD_H

#include "Character.hpp"
#include "Enemy.hpp"
#include "Background.hpp"
#include "Bullet.hpp"

class RetroWorld
{
	public:
		RetroWorld();
		RetroWorld(RetroWorld &other);
		~RetroWorld();

		RetroWorld	&operator=(RetroWorld &other);
		void		characterLeft();
		void		characterRight();
		void		characterUp();
		void		characterDown();
		void		characterShoot();

	private:
		Character	&_character;
		Enemy		**_enemies;
		Background	**_backgrounds;
		Bullet		**_bullets;
};

#endif