

#include "otool.h"

void	*get_set_options_handler(void *ptr, char option)
{
	static void		*data = NULL;

	if (option == 1)
		data = ptr;
	return (data);
}

void	set_current_options(void *ptr)
{
	get_set_options_handler(ptr, 1);
}

void	*get_current_options(void)
{
	return (get_set_options_handler(NULL, 2));
}

void	clear_options(void)
{
	get_set_options_handler(NULL, 1);
}

void	void_options(t_flags *options)
{
	options->t = 0;
}

void	set_options(char **argv, int i, int x, t_flags *options)
{
	if (argv[i][x] == 't')
		options->t = 1;
}

int		read_options(int argc, char **argv, t_flags *options)
{
	int		i;
	int		x;

	i = 1;
	while (i < argc)
	{
		if (argv[i][0] != '-')
			return (i);
		x = 1;
		while (argv[i][x])
		{
			set_options(argv, i, x, options);
			x++;
		}
		i++;
	}
	return (i);
}