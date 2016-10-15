

#include "EvalExpr.hpp"
#include "ExprStack.hpp"
#include <iostream>
#include <sstream>
#include <string>

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

Fixed	EvalExpr::parse_expr(std::string const &expr_str, bool print_postfix, bool *error)
{
	std::istringstream	expr(expr_str);
	float				tmp_val;
	char				tmp_char;
	ExprStack			&expr_stack = *(new ExprStack());
	std::string			to_print;

	if (expr_str.length() == 0)
		return ret_error("Void expression", error);
	to_print = "Tokens: ";
	while (expr)
	{
		tmp_char = expr.get();
		if (tmp_char == '\0' || tmp_char < 0)
			break ;
		if (!allowed_char(tmp_char))
			return ret_error(std::string("Unexpected character : ") + tmp_char, error);
		if (tmp_char == '(')
		{
			to_print += "ParOpen ";
			expr_stack.openBracket();
		}
		else if (tmp_char == ')')
		{
			to_print += "ParClose ";
			expr_stack.closeBracket(error);
		}
		else if (tmp_char == '+' || tmp_char == '-'
			|| tmp_char == '/' || tmp_char == '*')
		{
			to_print += "Op(" + (std::string(1, tmp_char)) + ") ";
			expr_stack.newOperator(tmp_char);
		}
		else if (isdigit(tmp_char))
		{
			expr.unget();
			expr >> tmp_val;
			std::stringstream ss(std::stringstream::in | std::stringstream::out);
			ss << tmp_val;
			to_print += "Num(" + ss.str() + ") ";
			expr_stack.newVal(tmp_val);
		}
		if (*error)
			return Fixed();
	}
	std::cout << to_print << std::endl;
	return expr_stack.resolve(print_postfix, error);
}