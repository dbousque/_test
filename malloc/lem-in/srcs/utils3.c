/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 18:29:34 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/13 12:19:08 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		intintlen(int **intint)
{
	int		i;

	i = 0;
	while (intint[i])
		i++;
	return (i);
}

int		int_tab_len(int *tab)
{
	int		i;

	ft_putstr("int tab len : ");
	print_address(tab);
	ft_putstr("\n");
	i = 0;
	while (tab[i] != -1)
	{
		print_number(tab[i]);
		ft_putstr("\n");
		i++;
	}
	print_number(tab[i]);
	ft_putstr("\n");
	return (i - 1);
}

int		*get_paths_len(int **best_paths, int nb_paths)
{
	int		i;
	int		*res;

	ft_putstr("GET PATHS LEN\n");
	if (!(res = (int*)malloc(sizeof(int) * (nb_paths + 1))))
		return (NULL);
	ft_putstr("GET PATHS LEN AFTER MALLOC\n");
	res[nb_paths] = 0;
	i = 0;
	ft_putstr("GET PATHS LEN BEFORE WHILE\n");
	while (i < nb_paths)
	{
		ft_putstr("GET PATHS LEN BEFORE INT TAB LEN\n");
		print_number(*(best_paths[i]));
		ft_putstr("GET PATHS LEN BEFORE AFTER VALUE TEST\n");
		res[i] = int_tab_len(best_paths[i]);
		ft_putstr("GET PATHS LEN AFTER\n");
		i++;
	}
	ft_putstr("GET PATHS LEN AFTER WHILE\n");
	return (res);
}
