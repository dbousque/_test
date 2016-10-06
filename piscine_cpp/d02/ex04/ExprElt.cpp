

#include "ExprElt.hpp"

char 	default_op = 'l';
Fixed	default_val = Fixed();

ExprElt::ExprElt() :
	_op(default_op),
	_val(default_val),
	_is_val(false)
{
}

ExprElt::ExprElt(float val) :
	_op(default_op),
	_val(*(new Fixed(val))),
	_is_val(true)
{
}

ExprElt::ExprElt(char op) :
	_op(op),
	_val(default_val),
	_is_val(false)
{
}

ExprElt::ExprElt(ExprElt &other) :
	_op(other.getOp()),
	_val(other.getVal()),
	_is_val(other.isVal())
{
}

ExprElt::~ExprElt()
{
}

ExprElt	&ExprElt::operator=(ExprElt &other)
{
	return *(new ExprElt(other));
}

bool		ExprElt::isVal()
{
	return this->_is_val;
}

Fixed		&ExprElt::getVal()
{
	return this->_val;
}

char		ExprElt::getOp()
{
	return this->_op;
}

std::ostream	&operator<<(std::ostream &os, ExprElt &elt)
{
	if (elt.isVal())
		os << elt.getVal();
	else
		os << elt.getOp();
	return os;
}