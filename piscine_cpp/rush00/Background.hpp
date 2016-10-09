

#ifndef BACKGROUND_H
# define BACKGROUND_H

#include "GameEntity.hpp"

class Background : public GameEntity
{
	public:
		Background(int x, int y);
		Background(Background &other);
		virtual ~Background();

		Background	&operator=(Background &other);
		void		move(int dx, int dy);
		bool		outOfBounds();
		void		display() const;

	private:
		Background();
};

#endif