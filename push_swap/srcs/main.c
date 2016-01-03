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

int		priority_function(int score, int nb_moves)
{
	(void)nb_moves;
	return (-(score * score * 10));
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

char	last_move(t_node2 *node)
{
	if (node->nb_moves <= 0)
		return (-1);
	return (node->previous_moves[node->nb_moves - 1]);
}

char	last_move_to_a(t_node2 *node)
{
	int		i;
	char	tmp;

	i = node->nb_moves - 1;
	while (i >= 0)
	{
		tmp = node->previous_moves[i];
		if (tmp == SA || tmp == SS || tmp == PA || tmp == PB
			|| tmp == RA || tmp == RR || tmp == RRA || tmp == RRR)
			return (tmp);
		i--;
	}
	return (-1);
}

char	last_move_to_b(t_node2 *node)
{
	int		i;
	char	tmp;

	i = node->nb_moves - 1;
	while (i >= 0)
	{
		tmp = node->previous_moves[i];
		if (tmp == SB || tmp == SS || tmp == PA || tmp == PB
			|| tmp == RB || tmp == RR || tmp == RRB || tmp == RRR)
			return (tmp);
		i--;
	}
	return (-1);
}

char	looping_nodes(t_node2 *top, int best)
{
	char	last_move_a;
	char	last_move_b;

	last_move_a = last_move_to_a(top);
	last_move_b = last_move_to_b(top);
	if (best == SA && (last_move_a == SA || last_move_a == SS))
		return (1);
	if (best == SB && (last_move_b == SB || last_move_b == SS))
		return (1);
	if (best == SS && (last_move_a == SS || last_move_a == SA || last_move_b == SB))
		return (1);
	if (best == PA && last_move_a == PB)
		return (1);
	if (best == PB && last_move_b == PA)
		return (1);
	if (best == RA && (last_move_a == RRA || last_move_a == RRR))
		return (1);
	if (best == RB && (last_move_b == RRB || last_move_b == RRR))
		return (1);
	if (best == RR && (last_move_a == RRR || last_move_a == RRA || last_move_b == RRB))
		return (1);
	if (best == RRA && (last_move_a == RA || last_move_a == RR))
		return (1);
	if (best == RRB && (last_move_b == RB || last_move_b == RR))
		return (1);
	if (best == RRR && (last_move_a == RR || last_move_a == RA || last_move_b == RB))
		return (1);
	return (0);
}

void	update_node(t_node2 *node, char move)
{
	apply_function(node->pile_a, node->pile_b, move);
	node->nb_moves++;
	node->previous_moves[node->nb_moves - 1] = move;
	node->score = get_current_score(node->pile_a, node->pile_b);
	node->priority = priority_function(node->score, node->nb_moves);
}

void	add_new_nodes(t_tree *tree, t_node2 *top, int scores[11])
{
	int		i;
	t_node2	*to_add;

	i = 0;
	while (i < 11)
	{
		if (scores[i] != -1 && !looping_nodes(top, i))
		{
			to_add = ft_new_node(top->pile_a, top->pile_b,
									top->nb_moves, top->previous_moves);
			update_node(to_add, i);
			tree = ft_add_to_tree2(tree, to_add);
		}
		i++;
	}
}

char	possible_best(t_node2 *top, t_node2 *best_so_far)
{
	if (!best_so_far)
		return (1);
	if (best_so_far->nb_moves > top->nb_moves)
		return (1);
	return (0);
}

t_node2	*sort_pile(t_pile *pile_a)
{
	t_tree	*tree;
	t_node2	*top;
	t_node2	*best_so_far;
	int		scores[11];
	int		poss;
	int		non_poss;

	best_so_far = NULL;
	tree = ft_empty_tree();
	tree = ft_add_to_tree2(tree, ft_new_node(pile_a, empty_pile(), 0, NULL));
	poss = 0;
	non_poss = 0;
	while (tree->last > 0)
	{
		top = ft_get_top(tree);
		if (possible_best(top, best_so_far))
		{
			poss ++;
			if (nb_elts(top->pile_b) == 0 && is_sorted_ab(top->pile_a, 1))
			{
				put_pile(top->pile_a);
				best_so_far = top;
				poss = 0;
				non_poss = 0;
			}
			else
			{
				//ft_printf("PILE A : ");
				//put_pile(top->pile_a);
				//ft_printf("PILE B : ");
				//put_pile(top->pile_b);
				//ft_printf("Node priority : %d\n", top->priority);
				void_scores(scores);
				calculate_moves_score(top->pile_a, top->pile_b, scores);
				//print_scores(scores);
				add_new_nodes(tree, top, scores);
			}
		}
		else
			non_poss++;
	}
	ft_printf("POSSIBLE : %d\nNON-POSS : %d\n", poss, non_poss);
	return (best_so_far);
}

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
	ft_putchar('\n');
	ft_printf("PILE : ");
	put_pile(best->pile_a);
}

int		main(int argc, char **argv)
{
	int		*nbs;
	t_pile	*pile_a;
	t_node2	*best;

	nbs = get_nbs(argc, argv);
	if (!nbs || twice_same(argc - 1, nbs))
		return (error(nbs));
	if (!(pile_a = pile_from_array(nbs, argc - 1)))
		return (error(nbs));
	free(nbs);
	nbs = NULL;
	best = sort_pile(pile_a);
	print_best_path(best);
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
