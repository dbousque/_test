/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 19:24:55 by dbousque          #+#    #+#             */
/*   Updated: 2017/03/02 19:24:57 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"

char	init_list(t_list *list, size_t elt_size)
{
	if (!(list->elts = malloc(elt_size * 4)))
		return (0);
	list->size = 4;
	list->len = 0;
	list->elt_size = elt_size;
	return (1);
}

void	double_list_size(t_list *lst)
{
	char	*new_elts;
	char	*elts;
	int		i;
	size_t	x;

	lst->size *= 2;
	if (!(new_elts = (char*)malloc(lst->elt_size * lst->size)))
		return ;
	elts = (char*)lst->elts;
	i = 0;
	while (i < lst->len)
	{
		x = 0;
		while (x < lst->elt_size)
		{
			new_elts[i * lst->elt_size + x] = elts[i * lst->elt_size + x];
			x++;
		}
		i++;
	}
	free(lst->elts);
	lst->elts = (void*)new_elts;
}

void	*new_elt(t_list *lst)
{
	size_t	i;
	char	*elts;

	if (lst->size == lst->len)
		double_list_size(lst);
	if (!lst->elts)
		return (NULL);
	lst->len++;
	elts = (char*)lst->elts;
	return (&(elts[lst->elt_size * (lst->len - 1)]));
}
