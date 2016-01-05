/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/30 19:55:41 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/05 20:22:32 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int		error(int *nbs)
{
	if (nbs)
		free(nbs);
	nbs = NULL;
	ft_putendl_fd("Error", 2);
	return (0);
}

int		priority_function(int score, int nb_moves)
{
	(void)nb_moves;
	return (-(score));
}

void	lst_del(void *content, size_t size)
{
	(void)size;
	free(content);
	content = NULL;
}

t_node2	*sort_pile(int argc, t_pile *pile_a, char function)
{
	t_node2	*best;
	t_node2	*best2;

	best = NULL;
	if (argc < 30 && function == 0)
		best = sort_pile_tree(pile_a);
	if (!best)
	{
		if (function == 0 || function == 1)
		{
			best = sort_pile_determ2(pile_a);
			if (best)
				best = reduce_best(best);
		}
		if ((argc < 300 || function == 2) && function != 1)
		{
			best2 = sort_pile_determ3(pile_a);
			if (best2)
				best2 = reduce_best(best2);
			if (best2 && (!best || best->nb_moves > best2->nb_moves))
				best = best2;
		}
	}
	return (best);
}

int		main(int argc, char **argv)
{
	int		*nbs;
	t_pile	*pile_a;
	t_node2	*best;
	char	flag;
	char	function;

	flag = get_flag(&argc, argv, &function);
	nbs = get_nbs(argc, argv);
	if (!nbs || twice_same(argc - 1, nbs)
		|| !(pile_a = pile_from_array(nbs, argc - 1)))
		return (error(nbs));
	free(nbs);
	nbs = NULL;
	best = sort_pile(argc, pile_a, function);
	if (!best)
	{
		free_pile(pile_a);
		return (error(nbs));
	}
	if (best)
		print_res(pile_a, best, flag);
	if (best)
		free_node(best);
	free_pile(pile_a);
	return (0);
}
