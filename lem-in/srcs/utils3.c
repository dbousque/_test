/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 18:29:34 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/08 18:29:42 by dbousque         ###   ########.fr       */
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

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int		*get_paths_len(int **best_paths, int nb_paths)
{
	int		i;
	int		*res;

	if (!(res = (int*)malloc(sizeof(int) * (nb_paths + 1))))
		return (NULL);
	res[nb_paths] = 0;
	i = 0;
	while (i < nb_paths)
	{
		res[i] = int_tab_len(best_paths[i]);
		i++;
	}
	return (res);
}
