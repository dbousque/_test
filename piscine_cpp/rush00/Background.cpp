

#include "Background.hpp"

std::string		background_repr[5] = {
	std::string("^^^^^^^^^^^"),
	std::string("^^^^^^^^^^^"),
	std::string("^^^^^^^^^^^"),
	std::string("^^^^^^^^^^^"),
	std::string("^^^^^^^^^^^")
};

Background::Background(int x, int y) :
	GameEntity(x, y, background_repr, 5)
{
}

Background::Background(Background &other) :
	GameEntity(other)
{
}

Background::~Background()
{
}

Background	&Background::operator=(Background &other)
{
	return *(new Background(other));
}