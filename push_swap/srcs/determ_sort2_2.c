/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   determ_sort2_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/05 17:41:57 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/05 17:42:57 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

char	*get_previous_moves(int length, t_list *list)
{
	t_list	*tmp;
	char	*previous_moves;

	if (!(previous_moves = (char*)malloc(sizeof(char) * length)))
		return (NULL);
	length = 0;
	tmp = list;
	while (tmp)
	{
		previous_moves[length] = *((char*)(tmp->content));
		length++;
		tmp = tmp->next;
	}
	return (previous_moves);
}

t_node2	*list_to_node(t_list *list, t_pile *a, t_pile *b)
{
	t_node2	*res;
	t_list	*tmp;
	int		length;

	if (!(res = (t_node2*)malloc(sizeof(t_node2))))
		return (NULL);
	tmp = list;
	length = 0;
	while (tmp)
	{
		length++;
		tmp = tmp->next;
	}
	res->nb_moves = length;
	res->pile_a = a;
	res->pile_b = b;
	res->previous_moves = get_previous_moves(length, list);
	if (!(res->previous_moves))
		return (NULL);
	return (res);
}

int		min_index(t_pile *pile)
{
	int		i;
	int		min;

	min = -1;
	i = pile->top;
	while (i < pile->length)
	{
		if (min == -1 || pile->elts[i] < pile->elts[min])
			min = i;
		i++;
	}
	return (min);
}

int		next_unsorted(t_pile *pile)
{
	int		i;
	int		min_ind;

	min_ind = min_index(pile);
	if (min_ind == -1)
		return (-1);
	i = pile->top;
	while (i < min_ind - 1)
	{
		if (pile->elts[i] > pile->elts[i + 1])
			return (i);
		i++;
	}
	i = min_ind - 1;
	while (i++ < pile->length - 1)
	{
		if (pile->elts[i] > pile->elts[i + 1])
			return (i);
	}
	if (min_ind > pile->top)
	{
		if (pile->elts[pile->top] < pile->elts[pile->length - 1])
			return (pile->length - 1);
	}
	return (-1);
}

int		next_unsorted_b(t_pile *pile)
{
	int		i;
	int		min_ind;

	min_ind = min_index(pile);
	if (min_ind == -1)
		return (-1);
	i = pile->top;
	while (i < min_ind - 1)
	{
		if (pile->elts[i] < pile->elts[i + 1])
			return (i);
		i++;
	}
	i = min_ind - 1;
	while (i++ < pile->length - 1)
	{
		if (pile->elts[i] < pile->elts[i + 1])
			return (i);
	}
	if (min_ind > pile->top)
	{
		if (pile->elts[pile->top] > pile->elts[pile->length - 1])
			return (pile->length - 1);
	}
	return (-1);
}
