/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   determ_sort2_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/05 17:45:30 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/05 17:46:20 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	put_next_unsorted_on_top(t_pile *a, int next_unsorted,
											t_list **list, t_list **list_end)
{
	int		val;
	char	car;

	val = a->elts[next_unsorted];
	car = (next_unsorted - a->top > nb_elts(a) / 2) ? RRA : RA;
	if (next_unsorted - a->top > nb_elts(a) / 2)
	{
		while (a->elts[a->top] != val)
		{
			ft_lstaddend(list_end, ft_lstnew(&car, sizeof(char)));
			if (!(*list))
				*list = *list_end;
			apply_function(a, NULL, RRA);
		}
	}
	else
	{
		while (a->elts[a->top] != val)
		{
			ft_lstaddend(list_end, ft_lstnew(&car, sizeof(char)));
			if (!(*list))
				*list = *list_end;
			apply_function(a, NULL, RA);
		}
	}
}

void	put_min_on_top(t_pile *pile, t_list **list, t_list **list_end)
{
	int		min_ind;

	min_ind = min_index(pile);
	put_next_unsorted_on_top(pile, min_ind, list, list_end);
}

void	sort_a(t_pile *a, t_list **list, t_list **list_end)
{
	int		next_unsort;
	char	sa;

	sa = SA;
	while (!(is_sorted_ab(a, 1)))
	{
		next_unsort = next_unsorted(a);
		if (next_unsort > a->top)
			put_next_unsorted_on_top(a, next_unsort, list, list_end);
		if (next_unsort != -1)
		{
			ft_lstaddend(list_end, ft_lstnew(&sa, sizeof(char)));
			if (!(*list))
				*list = *list_end;
			apply_function(a, NULL, SA);
		}
		else
			put_min_on_top(a, list, list_end);
	}
}

void	sort_b(t_pile *b, t_list **list, t_list **list_end)
{
	int		next_unsort;
	char	sa;

	sa = SA;
	while (!(is_sorted_ab(b, 0)))
	{
		next_unsort = next_unsorted_b(b);
		if (next_unsort > b->top)
			put_next_unsorted_on_top(b, next_unsort, list, list_end);
		if (next_unsort != -1)
		{
			ft_lstaddend(list_end, ft_lstnew(&sa, sizeof(char)));
			if (!(*list))
				*list = *list_end;
			apply_function(b, NULL, SA);
		}
		else
			put_min_on_top(b, list, list_end);
	}
}

void	make_function(t_pile *a, t_pile *b, t_list **list_end, char func)
{
	apply_function(a, b, func);
	ft_lstaddend(list_end, ft_lstnew(&func, sizeof(char)));
}
