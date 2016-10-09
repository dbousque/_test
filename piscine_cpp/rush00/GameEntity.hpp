

#ifndef GAMEENTITY_H
# define GAMEENTITY_H

#include <string>
#include <ncurses.h>
#include "Config.hpp"

class GameEntity
{
	public:
		GameEntity(int start_x, int start_y, std::string *representation, int repr_height);
		GameEntity(GameEntity &other);
		virtual ~GameEntity();

		GameEntity	&operator=(GameEntity &other);
		int			getX() const;
		int			getY() const;
		void		move(int dx, int dy);
		bool		touches(GameEntity &other) const;
		std::string	*getRepresentation() const;
		int			getReprLen() const;
		int			getReprHeight() const;
		int			getReprLenAtScale() const;
		int			getReprHeightAtScale() const;
		int			getVelocityX() const;
		int			getVelocityY() const;
		void		setVelocityX(int vel_x);
		void		setVelocityY(int vel_y);
		void		display() const;
		void		moveVelocity();

	protected:
		std::string	*_repr;
		int			_repr_height;
		int			_repr_height_at_scale;
		int			_x;
		int			_y;
		int			_velocity_x;
		int			_velocity_y;

	private:
		GameEntity();
};

#endif