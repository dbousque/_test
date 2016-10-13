

#include "Environment.hpp"

Environment::Environment()
{
	this->_data_start = new unsigned char[2048];
	this->_data_pointer = this->_data_start;
	this->_n = 2048;
}

Environment::Environment(size_t n)
{
	this->_data_start = new unsigned char[n];
	this->_data_pointer = this->_data_start;
	this->_n = n;
}

Environment::Environment(Environment const &other)
{
	this->_data_start = other.getDataStart();
	this->_data_pointer = other.getDataPointer();
	this->_n = other.getN();
}

Environment::~Environment()
{
	delete [] this->_data_start;
}

Environment		&Environment::operator=(Environment &other)
{
	this->_data_start = other.getDataStart();
	this->_data_pointer = other.getDataPointer();
	this->_n = other.getN();
	return *this;
}

unsigned char	*Environment::getDataPointer() const
{
	return &(this->_data_pointer);
}

unsigned char	*Environment::getDataStart() const
{
	return this->_data_start;
}

size_t			Environment::getN() const
{
	return this->_n;
}