

#ifndef EVALEXPR_H
# define EVALEXPR_H

#include <string>
#include "Fixed.hpp"

class EvalExpr
{
	public:
		EvalExpr();
		EvalExpr(std::string const &to_parse);
		EvalExpr(EvalExpr &other);
		~EvalExpr();

		EvalExpr			&operator=(EvalExpr &other);
		Fixed				parse(void) const;
		std::string const	&getExpr(void) const;

	private:
		std::string const	&_to_parse;
};

#endif