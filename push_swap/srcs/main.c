/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/30 19:55:41 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/02 20:27:40 by dbousque         ###   ########.fr       */
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

int		get_current_score(t_pile *pile_a, t_pile *pile_b)
{
	int		score;
	int		i;

	score = 0;
	i = pile_a->top;
	while (i < pile_a->length - 1)
	{
		if (pile_a->elts[i] > pile_a->elts[i + 1])
			score++;
		i++;
	}
	i = pile_b->top;
	while (i < pile_b->length - 1)
	{
		if (pile_b->elts[i] < pile_b->elts[i + 1])
			score++;
		i++;
	}
	score += nb_elts(pile_b);
	return (score);
}

char	is_sorted_ab(t_pile *pile, char is_a)
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

int		best_score_min_index(int scores[11])
{
	int		i;
	int		best;

	best = 0;
	i = 1;
	while (i < 11)
	{
		if (scores[best] == -1 || (scores[i] != -1 && scores[i] < scores[best]))
			best = i;
		i++;
	}
	return (best);
}

/*void	make_turn(t_tree *tree)
{
	int		current_score;
	int		scores[11];
	int		best;

	void_scores(scores);
	current_score = get_current_score(a, b);
	calculate_moves_score(a, b, scores);
	//ft_printf("current_score : %d\n", current_score);
	//print_scores(scores);
	best = best_score_min_index(scores);
	//ft_printf("best : %d\n", best);
	if (best != -1)
	{
		if (scores[4] == scores[best] && (current_score < scores[best] || (current_score == scores[best] && nb_elts(b) == 0)))
			best = 4;
		apply_function(a, b, best);
	}
}*/

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
	return (res);
}

void	sort_pile(t_pile *pile_a)
{
	int		i;
	t_tree	*tree;
	t_node2	*top;
	t_node2	*best_so_far;

	i = 0;
	best_so_far = NULL;
	tree = ft_empty_tree();
	tree = ft_add_to_tree2(tree, ft_new_node(pile_a, empty_pile(), 0, NULL));
	while (tree->last > 0)
	{
		top = ft_get_top(tree);
		put_pile(top->pile_a);
	}

	/*while (i < 8 && (!is_sorted_ab(pile_a, 1) || nb_elts(pile_b) > 0))
	{
		ft_printf("\n   PILE A : ");
		put_pile(pile_a);
		ft_printf("   PILE B : ");
		put_pile(pile_b);
		make_turn(tree);
		if (!is_sorted_ab(pile_a, 1) || nb_elts(pile_b) > 0)
			ft_putstr(" ");
		i++;
	}*/
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
