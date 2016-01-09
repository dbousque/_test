

#include "ft_ls.h"

int		illegal_option(char c)
{
	char	*str;

	str = "ft_ls: illegal option -- %c\nusage: ft_ls [-lRart] [file ...]\n";
	ft_printf(str, c);
	return (0);
}

int		set_flag(char c, t_flags *flags)
{
	if (c == 'l')
	{
		flags->l = 1;
		flags->minus = 0;
	}
	else if (c == 'R')
		flags->r_maj = 1;
	else if (c == 'r')
		flags->r = 1;
	else if (c == 'a')
		flags->a = 1;
	else if (c == 't')
		flags->t = 1;
	else if (c == '1')
	{
		flags->minus = 1;
		flags->l = 0;
	}
	else
		return (0);
	return (1);
}

t_flags	*void_flags(void)
{
	t_flags	*res;

	if (!(res = (t_flags*)malloc(sizeof(t_flags))))
		return (NULL);
	res->a = 0;
	res->r = 0;
	res->r_maj = 0;
	res->l = 0;
	res->t = 0;
	res->minus = 0;
	return (res);
}

int		add_flags(char *arg, t_flags *flags)
{
	int		i;

	if (arg[0] != '-' || !arg[1])
		return (2);
	else
	{
		i = 1;
		while (arg[i])
		{
			if (arg[i] == '-')
			{
				if (i != 1 || arg[i + 1] != '\0')
					return (illegal_option(arg[i]));
				return (3);
			}
			if (!set_flag(arg[i], flags))
				return (illegal_option(arg[i]));
			i++;
		}
	}
	return (1);
}

t_flags	*get_flags(int argc, char **argv, int *i)
{
	t_flags	*res;
	int		ret;

	res = void_flags();
	if (!res)
		return (NULL);
	*i = 1;
	while (*i < argc)
	{
		if (!(ret = add_flags(argv[*i], res)))
			return (NULL);
		if (ret == 2)
			return (res);
		if (ret == 3)
		{
			(*i)++;
			return (res);
		}
		(*i)++;
	}
	return (res);
}
