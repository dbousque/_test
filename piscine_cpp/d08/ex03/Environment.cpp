

#include "Environment.hpp"

Environment::Environment()
{
	this->_data_start = new unsigned char[2048];
	this->_data_pointer = new unsigned char*;
	*(this->_data_pointer) = this->_data_start;
	this->_n = 2048;
	for (size_t i = 0; i < this->_n; i++)
		this->_data_start[i] = 0;
}

Environment::Environment(size_t n)
{
	this->_data_start = new unsigned char[n];
	this->_data_pointer = new unsigned char*;
	*(this->_data_pointer) = this->_data_start;
	this->_n = n;
	for (size_t i = 0; i < this->_n; i++)
		this->_data_start[i] = 0;
}

Environment::Environment(Environment const &other)
{
	this->_data_start = other.getDataStart();
	this->_data_pointer = other.getDataPointer();
	this->_n = other.getN();
}

Environment::~Environment()
{
}

Environment		&Environment::operator=(Environment &other)
{
	this->_data_start = other.getDataStart();
	this->_data_pointer = other.getDataPointer();
	this->_n = other.getN();
	return *this;
}

unsigned char	**Environment::getDataPointer() const
{
	return this->_data_pointer;
}

unsigned char	*Environment::getDataStart() const
{
	return this->_data_start;
}

size_t			Environment::getN() const
{
	return this->_n;
}