/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 18:25:03 by dbousque          #+#    #+#             */
/*   Updated: 2016/09/22 18:25:09 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

t_list	*new_list(void)
{
	t_list	*lst;

	lst = my_malloc(sizeof(t_list));
	lst->elts = my_malloc(sizeof(void*) * 32);
	lst->size = 32;
	lst->len = 0;
	return (lst);
}

void	double_list_size(t_list *lst)
{
	int		i;
	void	**new_elts;

	lst->size *= 2;
	new_elts = my_malloc(sizeof(void*) * lst->size);
	i = 0;
	while (i < lst->len)
	{
		new_elts[i] = lst->elts[i];
		i++;
	}
	lst->elts = new_elts;
}

void	add_to_list(t_list *lst, void *elt)
{
	if (lst->size == lst->len)
		double_list_size(lst);
	lst->elts[lst->len] = elt;
	lst->len++;
}

void	sort_list(t_list *list, int (*cmp)(void *elt1, void *elt2))
{
	my_mergesort(list->elts, 0, list->len, cmp);
}

void	reverse_list(t_list *list)
{
	int		i;
	void	*tmp;

	i = 0;
	while (i < list->len / 2)
	{
		tmp = list->elts[i];
		list->elts[i] = list->elts[list->len - 1 - i];
		list->elts[list->len - 1 - i] = tmp;
		i++;
	}
}
