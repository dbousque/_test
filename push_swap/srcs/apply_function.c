/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/02 18:33:35 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/02 18:49:14 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int		apply_function_and_cancel(t_pile *a, t_pile *b,
		void (*f1)(t_pile*, t_pile *), void (*f2)(t_pile*, t_pile*))
{
	int		score;

	f1(a, b);
	score = get_current_score(a, b);
	f2(a, b);
	return (score);
}

void	print_fct_name(int i)
{
	if (i == 0)
		ft_putstr("sa");
	else if (i == 1)
		ft_putstr("sb");
	else if (i == 2)
		ft_putstr("ss");
	else if (i == 3)
		ft_putstr("pa");
	else if (i == 4)
		ft_putstr("pb");
	else if (i == 5)
		ft_putstr("ra");
	else if (i == 6)
		ft_putstr("rb");
	else if (i == 7)
		ft_putstr("rr");
	else if (i == 8)
		ft_putstr("rra");
	else if (i == 9)
		ft_putstr("rrb");
	else if (i == 10)
		ft_putstr("rrr");
}

void	apply_function(t_pile *a, t_pile *b, int i)
{
	if (i == 0)
		swap_a(a, b);
	else if (i == 1)
		swap_b(a, b);
	else if (i == 2)
		swap_ab(a, b);
	else if (i == 3)
		push_a(a, b);
	else if (i == 4)
		push_b(a, b);
	else if (i == 5)
		rotate_a(a, b);
	else if (i == 6)
		rotate_b(a, b);
	else if (i == 7)
		rotate_ab(a, b);
	else if (i == 8)
		reverse_rotate_a(a, b);
	else if (i == 9)
		reverse_rotate_b(a, b);
	else if (i == 10)
		reverse_rotate_ab(a, b);
	print_fct_name(i);
}
