

#include "EvalExpr.hpp"

int		main(int argc, char **argv)
{
	bool	error;
	int		i;
	bool	print_postfix;

	print_postfix = false;
	i = 1;
	if (argc > 1 && strncmp(argv[1], "-p", 3) == 0)
	{
		print_postfix = true;
		i = 2;
	}
	for (; i < argc; i++)
	{
		error = false;
		Fixed	tmp_expr = EvalExpr::parse_expr(argv[i], print_postfix, &error);
		if (!error)
			std::cout << tmp_expr << std::endl;
	}
	return (0);
}