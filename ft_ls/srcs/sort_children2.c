/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_children2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 19:15:13 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/13 19:15:24 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	sort_by_name(struct dirent **children, int nb)
{
	if (nb < 400)
		quicksort((void**)children, nb, ft_strcmp_child_name, NULL);
	else
		insertion_sort((void**)children, nb, ft_strcmp_child_name, NULL);
}

void	sort_by_size(struct dirent **children, int nb, char *dir_name)
{
	if (nb < 400)
		quicksort((void**)children, nb, compare_sizes, dir_name);
	else
		insertion_sort((void**)children, nb, compare_sizes, dir_name);
}

void	sort_by_date(struct dirent **children, int nb, char *dir_name, char l)
{
	if (l)
	{
		if (nb < 400)
			quicksort((void**)children, nb, compare_by_date, (void*)dir_name);
		else
			insertion_sort((void**)children, nb,
											compare_by_date, (void*)dir_name);
	}
	else
	{
		if (nb < 400)
			quicksort((void**)children, nb,
									compare_by_access_date, (void*)dir_name);
		else
			insertion_sort((void**)children, nb,
									compare_by_access_date, (void*)dir_name);
	}
}
