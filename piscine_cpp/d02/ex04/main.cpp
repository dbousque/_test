

#include "EvalExpr.hpp"

int		main(int argc, char **argv)
{
	bool	error;

	for (int i = 1; i < argc; i++)
	{
		error = false;
		Fixed	tmp_expr = EvalExpr::parse_expr(argv[i], &error);
		if (!error)
			std::cout << tmp_expr << std::endl;
	}
	return (0);
}