/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   determ_sort2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/05 17:33:02 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/05 20:19:57 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_node2	*sort_pile_determ2(t_pile *pile_a)
{
	t_pile	*b;
	t_pile	*a;
	t_list	*list;
	t_list	*list_end;
	char	car;

	car = SA;
	list = NULL;
	list_end = NULL;
	if (!(a = copy_pile(pile_a)))
		return (NULL);
	b = empty_pile();
	ft_lstaddend(&list_end, ft_lstnew(&car, sizeof(char)));
	list = list_end;
	quicksort_a(a, b, &list_end, nb_elts(a));
	list = list->next;
	return (list_to_node(list, a, b));
}

t_node2	*sort_pile_determ3(t_pile *pile_a)
{
	t_pile	*a;
	t_list	*list;
	t_list	*list_end;

	list = NULL;
	list_end = NULL;
	if (!(a = copy_pile(pile_a)))
		return (NULL);
	sort_a(a, &list, &list_end);
	return (list_to_node(list, a, NULL));
}
