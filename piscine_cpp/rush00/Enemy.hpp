

#ifndef ENEMY_H
# define ENEMY_H

#include "GameEntity.hpp"

class Enemy : public GameEntity
{
	public:
		Enemy(int x, int y, int type);
		Enemy(Enemy &other);
		virtual ~Enemy();

		Enemy	&operator=(Enemy &other);
		void	moveVelocity();
		bool	maybeShoot();
		void	takeShoot(int val);
		int		getValue();
		int		getIterShoot();
		int		getIterChangeDir();
		int		getLife();
		int		getType();

	private:
		Enemy();
		int		_value;
		int		_iter_shoot;
		int		_iter_change_dir;
		int		_life;
		int		_type;
};

#endif