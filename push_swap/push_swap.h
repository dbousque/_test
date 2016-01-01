

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft.h"

typedef struct	s_pile
{
	int			*elts;
	int			top;
	int			length;
}				t_pile;

void			put_pile(t_pile *pile);
void			double_pile_length(t_pile *pile);
char			put_on_pile(t_pile *pile, int nb);
int				take_from_pile(t_pile *pile);
t_pile			*empty_pile(void);
t_pile			*pile_from_array(int *nbs, int length);
void			push_a(t_pile *pile_a, t_pile *pile_b);
void			push_b(t_pile *pile_a, t_pile *pile_b);
void			swap_a(t_pile *pile);
void			swap_b(t_pile *pile);
void			swap_ab(t_pile *pile_a, t_pile *pile_b);
void			rotate_a(t_pile *pile);
void			rotate_b(t_pile *pile);
void			rotate_ab(t_pile *pile_a, t_pile *pile_b);
void			reverse_rotate_a(t_pile *pile);
void			reverse_rotate_b(t_pile *pile);
void			reverse_rotate_ab(t_pile *pile_a, t_pile *pile_b);
char			twice_same(int argc, int *nbs);
int				*get_nbs(int argc, char **argv);

#endif
