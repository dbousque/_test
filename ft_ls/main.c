/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/09 13:59:24 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/09 16:08:06 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		flags->l = 1;
	else if (c == 'R')
		flags->r_maj = 1;
	else if (c == 'r')
		flags->r = 1;
	else if (c == 'a')
		flags->a = 1;
	else if (c == 't')
		flags->t = 1;
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
	return (res);
}

int		add_flags(char *arg, t_flags *flags)
{
	int		i;

	if (arg[0] != '-' || !arg[1])
		flags->dir = opendir(arg);
	else
	{
		i = 1;
		while (arg[i])
		{
			if (!set_flag(arg[i], flags))
				return (illegal_option(arg[i]));
			i++;
		}
	}
	return (1);
}

t_flags	*get_flags(int argc, char **argv)
{
	t_flags	*res;
	int		i;

	res = void_flags();
	if (!res || argc <= 1)
	{
		if (res)
			res->dir = opendir(".");
		return (res);
	}
	i = 1;
	while (i < argc)
	{
		if (!(add_flags(argv[i], res)))
			return (NULL);
		i++;
	}
	return (res);
}

void	listdir(DIR *dir, t_flags *flags)
{
	struct dirent	*tmp_child;
	t_list			**chidlren_list;
	t_list			**chidlren_list_end;
	struct dirent	**children;

	while ((tmp_child = readdir(dir)))
	{
		ft_printf("%s\n", child->d_name);
	}
}

int		main(int argc, char **argv)
{
	struct dirent	**children;
	struct dirent	*child;
	t_flags			*flags;

	if (!(flags = get_flags(argc, argv)))
		return (0);
	listdir(flags->dir, flags);
	return (0);
}
