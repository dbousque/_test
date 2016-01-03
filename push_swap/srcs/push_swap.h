/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/02 19:12:30 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/02 20:19:06 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libdodo.h"

# define SA 0
# define SB 1
# define SS 2
# define PA 3
# define PB 4
# define RA 5
# define RB 6
# define RR 7
# define RRA 8
# define RRB 9
# define RRR 10

typedef struct	s_pile
{
	int			*elts;
	int			top;
	int			length;
}				t_pile;

typedef struct	s_node2
{
	t_pile		*pile_a;
	t_pile		*pile_b;
	int			nb_moves;
	char		*previous_moves;
	int			score;
	int			priority;
}				t_node2;

typedef struct	s_tree
{
	t_node2		**tree;
	int			max_size;
	int			nb_elts;
	int			last;
}				t_tree;

void			put_pile(t_pile *pile);
void			free_pile(t_pile *pile);
void			double_pile_length(t_pile *pile);
char			put_on_pile(t_pile *pile, int nb);
int				take_from_pile(t_pile *pile);
t_pile			*empty_pile(void);
t_pile			*pile_from_array(int *nbs, int length);
void			push_a(t_pile *pile_a, t_pile *pile_b);
void			push_b(t_pile *pile_a, t_pile *pile_b);
void			swap_a(t_pile *pile, t_pile *unused);
void			swap_b(t_pile *unused, t_pile *pile);
void			swap_ab(t_pile *pile_a, t_pile *pile_b);
void			rotate_a(t_pile *pile, t_pile *unused);
void			rotate_b(t_pile *unused, t_pile *pile);
void			rotate_ab(t_pile *pile_a, t_pile *pile_b);
void			reverse_rotate_a(t_pile *pile, t_pile *unused);
void			reverse_rotate_b(t_pile *unused, t_pile *pile);
void			reverse_rotate_ab(t_pile *pile_a, t_pile *pile_b);
char			twice_same(int argc, int *nbs);
int				*get_nbs(int argc, char **argv);
int				nb_elts(t_pile *pile);
void			apply_function(t_pile *a, t_pile *b, int i);
int				apply_function_and_cancel(t_pile *a, t_pile *b, void (*f1)(t_pile*, t_pile*), void (*f2)(t_pile*, t_pile*));
void			print_fct_name(int i);
int				get_current_score(t_pile *pile_a, t_pile *pile_b);
void			calculate_moves_score(t_pile *a, t_pile *b, int scores[11]);
void			void_scores(int scores[11]);
void			print_scores(int scores[11]);
t_tree			*ft_empty_tree(void);
t_tree			*ft_add_to_tree2(t_tree *tree, t_node2 *node);
t_node2			*ft_get_top(t_tree *tree);
t_node2			*ft_swap(t_tree *tree, int *ind, int ind2, t_node2 *tmp);
t_node2			*ft_get_res_n_update(t_tree *tree);
int				ft_right_place(int *ind, t_tree *tree);
int				ft_first_higher(t_tree *tree, int ind1, int ind2);

#endif
