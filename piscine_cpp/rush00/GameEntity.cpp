

#include "GameEntity.hpp"
#include "Config.hpp"

GameEntity::GameEntity(int start_x, int start_y, std::string *representation, int repr_height) :
	_repr(representation),
	_repr_height(repr_len),
	_repr_height_at_scale(repr_len * Config::scale_y),
	_x(start_x),
	_y(start_y)
{
}

GameEntity::GameEntity(GameEntity &other) :
	_repr(other.getRepresentation()),
	_repr_height(other.getReprHeight()),
	_repr_height_at_scale(other.getReprHeightAtScale()),
	_x(other.getX()),
	_y(other.getY())
{
}

GameEntity::~GameEntity()
{
}

GameEntity	&GameEntity::operator(GameEntity &other)
{
	this->_repr = other.getRepresentation();
	this->_repr_height = other.getReprHeight();
	this->_repr_height_at_scale = other.getReprHeightAtScale();
	this->_x = other.getX();
	this->_y = other.getY();
	return *this;
}

int			GameEntity::getX() const
{
	return this->_x;
}

int			GameEntity::getY() const
{
	return this->_y;
}

void		GameEntity::move(int dx, int dy)
{
	this->_x += dx;
	this->_y += dy;
	if (this->_x < 0)
		this->_x = 0;
	if (this->_y < 0)
		this->_y = 0;
	if (this->_x + this->getReprLenAtScale() >= (Config::win_width - Config::start_x) * Config::scale_x)
		this->_x = (Config::win_width - Config::start_x) * Config::scale_x - 1;
	if (this->_y + this->getReprHeightAtScale() >= (Config::win_height - Config::start_y) * Config::scale_y)
		this->_y = (Config::win_height - Config::start_y) * Config::scale_y) - 1;
}

int			absolute(int x)
{
	if (x < 0)
		return -x;
	return x;
}

bool		GameEntity::touches(GameEntity &other) const
{
	return (absolute(this->_x - other.getX()) * 2 <= (this->getReprLenAtScale() + other.getReprLenAtScale()))
			&& (absolute(this->_y - other.getY()) * 2 <= (this->_repr_height_at_scale + other.getReprHeightAtScale()));
}

std::string	*GameEntity::getRepresentation() const
{
	return this->_repr;
}

int			GameEntity::getReprHeight() const
{
	return this->_repr_height;
}

int			GameEntity::getReprLen() const
{
	return this->_repr[0]->length();
}

int			GameEntity::getReprHeightAtScale() const
{
	return this->_repr_height * Config::scale_y;
}

int			GameEntity::getReprLenAtScale() const
{
	return this->_repr[0]->length() * Config::scale_x;
}

void		GameEntity::display() const
{
	int		actual_x;
	int		actual_y;

	actual_x = this->_x * Config::scale_x;
	actual_x += Config::start_x;
	actual_y = this->_y * Config::scale_y;
	actual_y += Config::start_y;
	for (int y = 0; y < this->_repr_height; y++)
	{
		for (int x = 0; x < this->getReprLen(); x++)
			mvaddch(actual_y + y, actual_x + x, this->_repr[y][x]);
	}
}