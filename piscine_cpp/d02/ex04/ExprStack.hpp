

#ifndef EXPRSTACK_H
# define EXPRSTACK_H

#include "List.hpp"
#include "Stack.hpp"
#include "ExprElt.hpp"
#include "Fixed.hpp"

class ExprStack
{
	public:
		ExprStack();
		ExprStack(ExprStack &other);
		~ExprStack();

		ExprStack	&operator=(ExprStack &other);

		void	openBracket();
		void	closeBracket();
		void	newOperator(char op);
		void	newVal(float val);
		Fixed	resolve();
		List	&getPostfix();
		Stack	&getParseStack();

	private:
		List		&_postfix;
		Stack		&_parse_stack;
		
};

#endif