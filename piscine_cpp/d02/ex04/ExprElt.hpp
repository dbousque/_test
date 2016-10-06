

#ifndef EXPRELT_H
# define EXPRELT_H

#include "Fixed.hpp"
#include <iostream>

class ExprElt
{
	public:
		ExprElt();
		ExprElt(float val);
		ExprElt(char op);
		ExprElt(ExprElt &other);
		~ExprElt();

		ExprElt	&operator=(ExprElt &other);

		bool		isVal();
		Fixed		&getVal();
		char		getOp();

	private:
		char		_op;
		Fixed		&_val;
		bool		_is_val;
};

std::ostream	&operator<<(std::ostream &os, ExprElt &elt);

#endif