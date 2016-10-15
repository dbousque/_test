

#include "List.hpp"

List::List() :
	_elts(new void*[16]),
	_len(0),
	_size(16)
{
}

List::List(List &other)
{
	this->_len = other.length();
	this->_elts = new void*[this->_len];
	this->_size = this->_len;
	for (size_t i = 0; i < this->_len; i++)
		this->_elts[i] = other.get(i);
}

List::~List()
{
	delete [] _elts;
}

List	&List::operator=(List &other)
{
	return *(new List(other));
}

void	List::add(void *elt)
{
	if (this->_len == this->_size)
		this->_doubleListSize();
	this->_elts[this->_len] = elt;
	this->_len++;
}

size_t	List::length()
{
	return this->_len;
}

void	*List::get(size_t n)
{
	return this->_elts[n];
}

void	*List::pop()
{
	void	*to_pop;

	if (this->_len == 0)
		return (NULL);
	to_pop = this->_elts[this->_len - 1];
	this->_len--;
	return (to_pop);
}

void	*List::getTop()
{
	return this->_elts[this->_len - 1];
}

void	List::_doubleListSize()
{
	void	**new_elts = new void*[this->_size * 2];
	for (size_t i = 0; i < this->_len; i++)
		new_elts[i] = this->_elts[i];
	delete [] this->_elts;
	this->_elts = new_elts;
	this->_size *= 2;
}