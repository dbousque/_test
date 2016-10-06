

#include "ExprStack.hpp"
#include <iostream>

ExprStack::ExprStack() :
	_postfix(*(new List())),
	_parse_stack(*(new Stack()))
{
}

ExprStack::ExprStack(ExprStack &other) :
	_postfix(other.getPostfix()),
	_parse_stack(other.getParseStack())
{
}

ExprStack::~ExprStack()
{
}

ExprStack	&ExprStack::operator=(ExprStack &other)
{
	return *(new ExprStack(other));
}

void	ExprStack::openBracket()
{
	char	*to_push;

	to_push = new char[1];
	to_push[0] = '(';
	this->_parse_stack.push(to_push);
}

void	ExprStack::closeBracket()
{
	char	*top_elt;

	while (this->_parse_stack.length() != 0
			&& *(top_elt = (char*)this->_parse_stack.pop()) != '(')
		this->_postfix.add(new ExprElt(*top_elt));
}

bool	inferior_or_egal_precedence(char op1, char op2)
{
	if (op1 == '+' || op2 == '-')
		return true;
	if (op2 == '+' || op2 == '-')
		return false;
	return true;
}

void	ExprStack::newOperator(char op)
{
	char	*to_push;
	char	*top_elt;

	while (this->_parse_stack.length() != 0
			&& *(top_elt = (char*)this->_parse_stack.getTop()) != '('
			&& inferior_or_egal_precedence(op, *top_elt))
		this->_postfix.add(new ExprElt(*((char*)this->_parse_stack.pop())));
	to_push = new char[1];
	to_push[0] = op;
	this->_parse_stack.push(to_push);
}

void	ExprStack::newVal(float val)
{
	this->_postfix.add(new ExprElt(val));
}

void	print_postfix(List &postfix)
{
	for (size_t i=0; i < postfix.length(); i++)
	{
		std::cout << *((ExprElt*)postfix.get(i)) << ' ';
	}
	std::cout << std::endl;
}

Fixed	ExprStack::resolve()
{
	print_postfix(this->_postfix);
	return Fixed();
}

List	&ExprStack::getPostfix()
{
	return this->_postfix;
}

Stack	&ExprStack::getParseStack()
{
	return this->_parse_stack;
}