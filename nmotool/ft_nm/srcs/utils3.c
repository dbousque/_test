/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 18:01:22 by dbousque          #+#    #+#             */
/*   Updated: 2016/09/22 18:01:24 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	print_n_char(char c, int n)
{
	int		i;

	i = 0;
	while (i < n)
	{
		write(1, &c, 1);
		i++;
	}
}

void	clear_options_and_free_all(void)
{
	clear_options();
	free_all();
}

void	ft_putstrn(char *str, int n)
{
	write(1, str, n);
}

char	is_ranlib(char *ptr)
{
	if (ptr[0] == '!' && ptr[1] == '<' && ptr[2] == 'a'
		&& ptr[3] == 'r' && ptr[4] == 'c' && ptr[5] == 'h'
		&& ptr[6] == '>' && ptr[7] == '\n')
		return (1);
	return (0);
}

int		display_help(void)
{
	ft_putstr("             -- nm --\n  displays content of Mach O files\n\n");
	ft_putstr("implemented options :\n");
	ft_putstr("  -g : Display only global (external) symbols.\n");
	ft_putstr("  -n : Sort numerically rather than alphabetically.\n");
	ft_putstr("  -o : Prepend file or archive element name to each output ");
	ft_putstr("line rather than only once.\n");
	ft_putstr("  -p : Don't sort; display in symbol-table order.\n");
	ft_putstr("  -r : Sort in reverse order.\n");
	ft_putstr("  -u : Display only undefined symbols.\n");
	ft_putstr("  -U : Don't display undefined symbols.\n");
	clear_options();
	free_all();
	return (0);
}
