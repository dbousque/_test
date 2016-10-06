

#ifndef EVALEXPR_H
# define EVALEXPR_H

#include <string>
#include "Fixed.hpp"

namespace EvalExpr
{
	Fixed	parse_expr(std::string const &expr, bool *error);
}

#endif