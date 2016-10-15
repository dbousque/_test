

#include "Field.hpp"

Field::Field(void *data, char type) :
	_data(data),
	_type(type)
{
}

Field::Field(Field const &other) :
	_data(other.getData()),
	_type(other.getType())
{
}

Field::~Field()
{
}

Field	&Field::operator=(Field &other)
{
	this->_data = other.getData();
	this->_type = other.getType();
	return *this;
}

void	*Field::getData() const
{
	return this->_data;
}

char	Field::getType() const
{
	return this->_type;
}