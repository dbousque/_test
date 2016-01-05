/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/05 17:15:15 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/05 17:15:32 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

char	*copy_moves(char *previous_moves, int nb_moves)
{
	char	*res;
	int		i;

	if (!(res = (char*)malloc(sizeof(char) * (nb_moves + 1))))
		return (NULL);
	i = 0;
	while (i < nb_moves)
	{
		res[i] = previous_moves[i];
		i++;
	}
	return (res);
}

t_pile	*copy_pile(t_pile *pile)
{
	t_pile	*res;

	if (!(res = (t_pile*)malloc(sizeof(t_pile))))
		return (NULL);
	if (!(res->elts = (int*)malloc(sizeof(int) * pile->length)))
		return (NULL);
	res->top = pile->top;
	res->length = pile->length;
	ft_memcpy(res->elts + res->top, pile->elts + res->top,
			nb_elts(res) * sizeof(int));
	return (res);
}

t_node2	*ft_new_node(t_pile *a, t_pile *b, int nb_moves, char *previous_moves)
{
	t_node2		*res;

	if (!(res = (t_node2*)malloc(sizeof(t_node2))))
		return (NULL);
	res->nb_moves = nb_moves;
	if (!(res->pile_a = copy_pile(a)))
		return (NULL);
	if (!(res->pile_b = copy_pile(b)))
		return (NULL);
	if (!(res->previous_moves = copy_moves(previous_moves, nb_moves)))
		return (NULL);
	res->score = get_current_score(res->pile_a, res->pile_b);
	res->priority = priority_function(res->score, res->nb_moves);
	return (res);
}
