/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/30 19:55:41 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/02 13:25:06 by dbousque         ###   ########.fr       */
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

char	is_sorted(t_pile *pile)
{
	int		i;

	i = pile->top;
	while (i < pile->length - 1)
	{
		if (pile->elts[i] >= pile->elts[i + 1])
			return (0);
		i++;
	}
	return (1);
}

int		get_score_pile_b(t_pile *pile_b)
{
	int		i;
	int		j;
	int		score;

	score = 0;
	i = pile_b->top;
	while (i < pile_b->length - 1)
	{
		j = i + 1;
		while (j < pile_b->length)
		{
			if (pile_b->elts[i] > pile_b->elts[j])
				score += j - i;
			j++;
		}
		i++;
	}
	return (score);
}

int		get_current_score(t_pile *pile_a, t_pile *pile_b)
{
	int		score;
	int		i;
	int		j;

	score = 0;
	i = pile_a->top;
	while (i < pile_a->length - 1)
	{
		j = i + 1;
		while (j < pile_a->length)
		{
			if (pile_a->elts[i] < pile_a->elts[j])
				score += j - i;
			j++;
		}
		i++;
	}
	score += get_score_pile_b(pile_b);
	return (score);
}

char	is_sorted(t_pile *pile, char is_a)
{
	int		i;

	i = pile->top;
	while (i < pile->length - 1)
	{
		if (is_a && pile->elts[i] > pile->elts[i + 1])
			return (0);
		else if (!is_a && pile->elts[i] < pile->elts[i + 1])
			return (0);
		i++;
	}
	return (1);
}

void	make_turn(t_pile *pile_a, t_pile *pile_b)
{

}

void	sort_pile(t_pile *pile_a)
{
	t_pile	*pile_b;
	int		score;

	pile_b = empty_pile();
	score = get_current_score(pile_a, pile_b);
	ft_printf("Score : %d\n", score);
	while (!is_sorted(pile_a))
	{
		make_turn(pile_a, pile_b);
	}
}

int		main(int argc, char **argv)
{
	int		*nbs;
	t_pile	*pile_a;

	nbs = get_nbs(argc, argv);
	if (!nbs || twice_same(argc - 1, nbs))
		return (error(nbs));
	if (!(pile_a = pile_from_array(nbs, argc - 1)))
		return (error(nbs));
	free(nbs);
	nbs = NULL;
	sort_pile(pile_a);
	put_pile(pile_a);
	/*ft_putstr("A : ");
	put_pile(pile_a);
	ft_putstr("B : ");
	put_pile(pile_b);
	push_b(pile_a, pile_b);

	ft_putstr("A : ");
	put_pile(pile_a);
	ft_putstr("B : ");
	put_pile(pile_b);
	swap_a(pile_a);

	ft_putstr("A : ");
	put_pile(pile_a);
	ft_putstr("B : ");
	put_pile(pile_b);
	push_a(pile_a, pile_b);

	ft_putstr("A : ");
	put_pile(pile_a);
	ft_putstr("B : ");
	put_pile(pile_b);
	swap_a(pile_a);

	
	ft_putstr("A : ");
	put_pile(pile_a);
	ft_putstr("B : ");
	put_pile(pile_b);*/
	return (0);
}
