

#include "Stack.hpp"

Stack::Stack() :
	_lst(*(new List()))
{
}

Stack::Stack(Stack &other) :
	 _lst(other.toList())
{
}

Stack::~Stack()
{
}

Stack	&Stack::operator=(Stack &other)
{
	this->_lst = other.toList();
	return *this;
}

void	Stack::push(void *elt)
{
	this->_lst.add(elt);
}

void	*Stack::pop()
{
	return (this->_lst.pop());
}

void	*Stack::getTop()
{
	return (this->_lst.getTop());
}

size_t	Stack::length()
{
	return (this->_lst.length());
}

List	&Stack::toList()
{
	return this->_lst;
}