/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/09 13:59:24 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/09 14:46:14 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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

int		main(int argc, char **argv)
{
	struct dirent	*child;
	t_flags			*flags;

	if (!(flags = get_flags(argc, argv)))
		return (0);
	while ((child = readdir(flags->dir)))
	{
		ft_printf("%s\n", child->d_name);
	}
	return (0);
}
