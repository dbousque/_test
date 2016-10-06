

#include "EvalExpr.hpp"
#include "ExprStack.hpp"
#include <iostream>
#include <sstream>

std::string const	allowed_chars = "0123456789 \t+-*/()";

Fixed	ret_error(std::string msg, bool *error)
{
	*error = true;
	std::cout << msg << std::endl;
	return Fixed();
}

bool	allowed_char(char c)
{
	return allowed_chars.find(c) != std::string::npos;
}

Fixed	EvalExpr::parse_expr(std::string const &expr_str, bool *error)
{
	std::istringstream	expr(expr_str);
	float				tmp_val;
	char				tmp_char[1];
	ExprStack			&expr_stack = *(new ExprStack());

	if (expr_str.length() == 0)
		return ret_error("Void expression", error);
	while (expr)
	{
		expr.read(tmp_char, 1);
		std::cout << "tmp_char : " << tmp_char << " gcount " << expr.gcount() << std::endl;
		if (tmp_char[0] == '\0')
			break ;
		if (!allowed_char(tmp_char[0]))
			return ret_error(std::string("Unexpected character : ") + tmp_char, error);
		if (tmp_char[0] == '(')
			expr_stack.openBracket();
		else if (tmp_char[0] == ')')
			expr_stack.closeBracket();
		else if (tmp_char[0] == '+' || tmp_char[0] == '-'
			|| tmp_char[0] == '/' || tmp_char[0] == '*')
			expr_stack.newOperator(tmp_char[0]);
		else if (isdigit(tmp_char[0]))
		{
			expr.unget();
			std::cout << "expr : " << expr << std::endl;
			expr >> tmp_val;
			expr_stack.newVal(tmp_val);
		}
	}
	return expr_stack.resolve();
}