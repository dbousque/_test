/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/05 17:48:42 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/05 17:54:40 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int		last_to_push_into_nb_to_consider_a(t_pile *a, int nb_to_cons, int pivot)
{
	int		i;
	int		last;

	i = 1;
	last = 0;
	while (i < nb_to_cons)
	{
		if (a->elts[i + a->top] < pivot)
			last = i;
		i++;
	}
	return (last);
}

int		last_to_push_into_nb_to_consider_b(t_pile *b, int nb_to_cons, int pivot)
{
	int		i;
	int		last;

	i = 1;
	last = 0;
	while (i < nb_to_cons)
	{
		if (b->elts[i + b->top] > pivot)
			last = i;
		i++;
	}
	return (last);
}

int		push_smaller_to_b(t_pile *a, t_pile *b, t_list **list_end,
													int nb_consider_pivot[2])
{
	int		nb_pushed;
	int		i;
	int		nb_to_consider;
	int		pivot;

	pivot = nb_consider_pivot[1];
	nb_to_consider = nb_consider_pivot[0];
	i = 0;
	nb_pushed = 0;
	while (i < nb_to_consider)
	{
		if (a->elts[a->top] < pivot)
		{
			nb_pushed++;
			make_function(a, b, list_end, PB);
		}
		else
			make_function(a, b, list_end, RA);
		i++;
	}
	return (nb_pushed);
}

int		push_higher_to_a(t_pile *a, t_pile *b, t_list **list_end,
													int nb_consider_pivot[2])
{
	int		nb_pushed;
	int		i;
	int		nb_to_consider;
	int		pivot;

	pivot = nb_consider_pivot[1];
	nb_to_consider = nb_consider_pivot[0];
	i = 0;
	nb_pushed = 0;
	while (i < nb_to_consider)
	{
		if (b->elts[b->top] > pivot)
		{
			nb_pushed++;
			make_function(a, b, list_end, PA);
		}
		else
			make_function(a, b, list_end, RB);
		i++;
	}
	return (nb_pushed);
}

void	return_to_ori_position_a(t_pile *a, t_list **list_end, int to_ret)
{
	int		i;

	i = 0;
	while (i < to_ret)
	{
		make_function(a, NULL, list_end, RRA);
		i++;
	}
}
