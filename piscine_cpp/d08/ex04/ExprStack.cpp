

#include "ExprStack.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>

ExprStack::ExprStack() :
	_postfix(*(new List())),
	_parse_stack(*(new Stack())),
	_open_parenthese(0)
{
}

ExprStack::ExprStack(ExprStack &other) :
	_postfix(other.getPostfix()),
	_parse_stack(other.getParseStack()),
	_open_parenthese(0)
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

	this->_open_parenthese++;
	to_push = new char[1];
	to_push[0] = '(';
	this->_parse_stack.push(to_push);
}

void	ExprStack::closeBracket(bool *error)
{
	char	*top_elt;

	if (this->_open_parenthese == 0)
	{
		*error = true;
		std::cout << "Unbalanced parentheses" << std::endl;
		return ;
	}
	this->_open_parenthese--;
	while (this->_parse_stack.length() != 0
			&& *(top_elt = (char*)this->_parse_stack.pop()) != '(')
		this->_postfix.add(new ExprElt(*top_elt));
}

bool	inferior_or_egal_precedence(char op1, char op2)
{
	if (op1 == '+' || op1 == '-')
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
	std::cout << "Postfix : ";
	for (size_t i=0; i < postfix.length(); i++)
		std::cout << *((ExprElt*)postfix.get(i));
	std::cout << std::endl;
}

void	print_stack(Stack *stack)
{
	List	&lst = stack->toList();

	for (int i = lst.length() - 1; i >= 0; i--)
		std::cout << (reinterpret_cast<ExprElt*>(lst.get(i)))->getVal() << " ";
}

Fixed	ExprStack::resolve(bool print_post, bool *error)
{
	ExprElt	*tmp_elt;
	char	*top_elt;
	ExprElt	*val1;
	ExprElt	*val2;
	Stack	*elts_stack = new Stack();

	while (this->_parse_stack.length() != 0
			&& *(top_elt = (char*)this->_parse_stack.pop()) != '(')
		this->_postfix.add(new ExprElt(*top_elt));
	if (this->_parse_stack.length() != 0)
	{
		*error = true;
		std::cout << "Unbalanced parentheses" << std::endl;
		delete elts_stack;
		return Fixed();
	}
	if (print_post)
		print_postfix(this->_postfix);
	for (size_t i = 0; i < this->_postfix.length(); i++)
	{
		tmp_elt = ((ExprElt*)this->_postfix.get(i));
		if (tmp_elt->isVal())
		{
			std::stringstream ss(std::stringstream::in | std::stringstream::out);
			ss << "I Num(" << tmp_elt->getVal() << ")";
			std::cout << std::setw(9) << std::left << ss.str();
			std::cout << std::setw(15) << std::left << "| OP Push";
			std::cout << "| ST ";
			elts_stack->push(tmp_elt);
			print_stack(elts_stack);
			std::cout << "]" << std::endl;
		}
		else
		{
			val1 = (ExprElt*)elts_stack->pop();
			val2 = (ExprElt*)elts_stack->pop();
			if (!val1 || !val2)
			{
				*error = true;
				std::cout << "Syntax error" << std::endl;
				return Fixed();
			}
			std::stringstream ss(std::stringstream::in | std::stringstream::out);
			ss << "I Op(" << tmp_elt->getOp() << ")";
			std::cout << std::setw(9) << std::left << ss.str();
			std::cout << "| OP ";
			if (tmp_elt->getOp() == '+')
			{
				std::cout << std::setw(10) << std::left << "Add";
				tmp_elt = new ExprElt(new Fixed((*val2).getVal() + (*val1).getVal()));
			}
			else if (tmp_elt->getOp() == '-')
			{
				std::cout << std::setw(10) << std::left << "Substract";
				tmp_elt = new ExprElt(new Fixed((*val2).getVal() - (*val1).getVal()));
			}
			else if (tmp_elt->getOp() == '*')
			{
				std::cout << std::setw(10) << std::left << "Multiply";
				tmp_elt = new ExprElt(new Fixed((*val2).getVal() * (*val1).getVal()));
			}
			else
			{
				std::cout << std::setw(10) << std::left << "Divide";
				tmp_elt = new ExprElt(new Fixed((*val2).getVal() / (*val1).getVal()));
			}
			elts_stack->push(tmp_elt);
			std::cout << "| ST ";
			print_stack(elts_stack);
			std::cout << "]" << std::endl;
		}
	}
	Fixed	&to_ret = (*((ExprElt*)elts_stack->pop())).getVal();
	delete elts_stack;
	return to_ret;
}

List	&ExprStack::getPostfix()
{
	return this->_postfix;
}

Stack	&ExprStack::getParseStack()
{
	return this->_parse_stack;
}