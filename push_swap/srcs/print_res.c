/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_res.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/05 17:16:27 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/05 17:16:29 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_best_path(t_node2 *best)
{
	int		i;

	i = 0;
	while (i < best->nb_moves)
	{
		if (i != 0)
			ft_putstr(" ");
		print_fct_name(best->previous_moves[i]);
		i++;
	}
	if (i > 0)
		ft_putchar('\n');
}

void	print_best_path_each_step(t_pile *pile_a, t_node2 *best)
{
	int		i;
	t_pile	*pile_b;

	pile_b = empty_pile();
	i = 0;
	while (i < best->nb_moves)
	{
		ft_putstr("A : ");
		put_pile(pile_a);
		ft_putstr("B : ");
		put_pile(pile_b);
		ft_putstr("\n     |\n ");
		print_fct_name(best->previous_moves[i]);
		if (best->previous_moves[i] > 7)
			ft_putstr(" |\n     v\n\n");
		else
			ft_putstr("  |\n     v\n\n");
		apply_function(pile_a, pile_b, best->previous_moves[i]);
		i++;
	}
	ft_putstr("A : ");
	put_pile(pile_a);
	ft_putstr("B : ");
	put_pile(pile_b);
	free_pile(pile_b);
}

void	print_best_path_color(t_node2 *best)
{
	int		i;

	i = 0;
	while (i < best->nb_moves)
	{
		if (i != 0)
			ft_putstr(" ");
		if (i == best->nb_moves - 1)
		{
			ft_printf("{red}");
			print_fct_name(best->previous_moves[i]);
			ft_printf("{eoc}");
		}
		else
			print_fct_name(best->previous_moves[i]);
		i++;
	}
	if (i > 0)
		ft_putchar('\n');
}

char	get_flag(int *argc, char **argv)
{
	char	flag;

	flag = 0;
	if (ft_strcmp(argv[*argc - 1], "-n") == 0)
	{
		flag = 5;
		(*argc)--;
	}
	if (ft_strcmp(argv[*argc - 1], "-v") == 0)
		flag += 1;
	else if (ft_strcmp(argv[*argc - 1], "-c") == 0)
		flag += 2;
	if (flag != 0 && flag != 5)
		(*argc)--;
	return (flag);
}

void	print_res(t_pile *pile_a, t_node2 *best, char flag)
{
	if (flag == 0 || flag == 5)
		print_best_path(best);
	if (flag == 2 || flag == 7)
		print_best_path_color(best);
	if (flag == 1 || flag == 6)
		print_best_path_each_step(pile_a, best);
	if (flag >= 5)
		ft_printf("--> {cyan}NB MOVES{eoc} : {red}%d{eoc}\n", best->nb_moves);
}
