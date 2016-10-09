

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

	private:
		Background();
};

#endif