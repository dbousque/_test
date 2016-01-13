/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_columns.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 18:51:09 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/13 19:14:31 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		next_tab(int largest)
{
	return (largest + 8 - largest % 8);
}

int		get_largest_string(char **strings)
{
	int		i;
	int		largest;

	i = 0;
	largest = -1;
	while (strings[i])
	{
		if ((int)ft_strlen(strings[i]) > largest)
			largest = (int)ft_strlen(strings[i]);
		i++;
	}
	return (next_tab(largest));
}

void	print_n_tabs(int n)
{
	while (n > 0)
	{
		ft_putstr("\t");
		n--;
	}
}

int		init_w(struct winsize *w)
{
	if (!(w = (struct winsize*)malloc(sizeof(struct winsize))))
		return (0);
	ioctl(STDOUT_FILENO, TIOCGWINSZ, w);
	return (1);
}

int		print_string_array_columns(char **strings, int nb, int nb_l, int nb_per)
{
	int				i;
	int				x;
	int				larg;
	struct winsize	*w;

	larg = get_largest_string(strings);
	if (!(w = NULL) && !init_w(w))
		return (0);
	nb_per = w->ws_col / larg;
	nb_l = nb / nb_per + 1;
	x = 0;
	while (x < nb_l && x < nb)
	{
		i = 0;
		while (i < nb_per && i * nb_l + x < nb)
		{
			ft_putstr(strings[i * nb_l + x]);
			if (i + 1 < nb_per && (i + 1) * nb_l + x < nb)
				print_n_tabs((larg - ft_strlen(strings[i * nb_l + x]) + 7) / 8);
			i++;
		}
		ft_putchar('\n');
		x++;
	}
	return (1);
}
