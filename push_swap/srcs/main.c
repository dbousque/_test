/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/30 19:55:41 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/02 12:33:49 by dbousque         ###   ########.fr       */
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

void	sort_pile(t_pile *pile_a)
{
	t_pile	*pile_b;


	(void)pile_a;
	pile_b = empty_pile();
}

int		main(int argc, char **argv)
{
	int		*nbs;
	t_pile	*pile_a;
	t_pile	*pile_b;

	nbs = get_nbs(argc, argv);
	if (!nbs || twice_same(argc - 1, nbs))
		return (error(nbs));
	if (!(pile_a = pile_from_array(nbs, argc - 1)))
		return (error(nbs));
	free(nbs);
	nbs = NULL;
	pile_b = empty_pile();
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
