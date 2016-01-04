

#include "push_swap.h"

char	next_best(int scores[11], int best)
{
	int		i;
	int		min;

	i = best + 1;
	min = -1;
	while (i < 11)
	{
		if (scores[i] != -1 && scores[min] > scores[i])
			min = i;
		i++;
	}
	return (min);
}

t_node2	*sort_pile_determ(t_pile *a)
{
	int		current_score;
	int		scores[11];
	int		best;
	t_node2	*node;
	t_node2	*tmp;

	if (!(node = ft_new_node(a, empty_pile(), 0, NULL)))
		return (NULL);
	best = 0;
	while (!(nb_elts(node->pile_b) == 0 && is_sorted_ab(node->pile_a, 1)) && best != -1)
	{
		void_scores(scores);
		current_score = get_current_score(node->pile_a, node->pile_b);
		calculate_moves_score(node->pile_a, node->pile_b, scores);
		best = best_score_min_index(scores);
		if (best != -1)
		{
			if (scores[4] == scores[best] && (current_score < scores[best] || (current_score == scores[best] && nb_elts(node->pile_b) == 0)) && !looping_nodes(node, 4))
				best = 4;
			while (best != -1 && node->nb_moves > 0 && looping_nodes(node, best))
			{
				best = next_best(scores, best);
			}
			if (best != -1)
			{
				tmp = ft_new_node(node->pile_a, node->pile_b, node->nb_moves, node->previous_moves);
				update_node(tmp, best, 0);
				free_node(node);
				node = tmp;
			}
		}
	}
	if (best == -1)
	{
		ft_putendl("PROBLEEEEMEE !");
		free_node(node);
		return (NULL);
	}
	return (node);
}
