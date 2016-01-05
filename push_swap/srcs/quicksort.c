/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/05 17:49:53 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/05 17:50:36 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	return_to_ori_position_b(t_pile *b, t_list **list_end, int to_ret)
{
	int		i;

	i = 0;
	while (i < to_ret)
	{
		make_function(NULL, b, list_end, RRB);
		i++;
	}
}

void	restore_a(t_pile *a, t_pile *b, t_list **list_end, int nb_pushed)
{
	while (nb_pushed > 0)
	{
		make_function(a, b, list_end, PA);
		nb_pushed--;
	}
}

void	restore_b(t_pile *a, t_pile *b, t_list **list_end, int nb_pushed)
{
	while (nb_pushed > 0)
	{
		make_function(a, b, list_end, PB);
		nb_pushed--;
	}
}

void	quicksort_a(t_pile *a, t_pile *b, t_list **list_end, int nb_to_consider)
{
	int		pivot;
	int		nb_pushed;
	int		nb_consider_pivot[2];

	nb_pushed = 0;
	if (nb_elts(a) > 1 && nb_to_consider > 1)
	{
		pivot = a->elts[a->top];
		make_function(a, b, list_end, RA);
		nb_to_consider--;
		nb_consider_pivot[0] = nb_to_consider;
		nb_consider_pivot[1] = pivot;
		nb_pushed = push_smaller_to_b(a, b, list_end, nb_consider_pivot);
		return_to_ori_position_a(a, list_end, nb_to_consider - nb_pushed);
	}
	if (nb_to_consider - nb_pushed > 1)
		quicksort_a(a, b, list_end, nb_to_consider - nb_pushed);
	if (nb_elts(a) > 1)
		make_function(a, b, list_end, RRA);
	if (nb_pushed > 1)
		quicksort_b(a, b, list_end, nb_pushed);
	restore_a(a, b, list_end, nb_pushed);
}

void	quicksort_b(t_pile *a, t_pile *b, t_list **list_end, int nb_to_consider)
{
	int		pivot;
	int		nb_pushed;
	int		nb_consider_pivot[2];

	nb_pushed = 0;
	if (nb_elts(b) > 1 && nb_to_consider > 1)
	{
		pivot = b->elts[b->top];
		make_function(a, b, list_end, RB);
		nb_to_consider--;
		nb_consider_pivot[0] = nb_to_consider;
		nb_consider_pivot[1] = pivot;
		nb_pushed = push_higher_to_a(a, b, list_end, nb_consider_pivot);
		return_to_ori_position_b(b, list_end, nb_to_consider - nb_pushed);
	}
	if (nb_to_consider - nb_pushed > 1)
		quicksort_b(a, b, list_end, nb_to_consider - nb_pushed);
	if (nb_elts(b) > 1)
		make_function(a, b, list_end, RRB);
	if (nb_pushed > 1)
		quicksort_a(a, b, list_end, nb_pushed);
	restore_b(a, b, list_end, nb_pushed);
}
