/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_options.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 17:58:55 by dbousque          #+#    #+#             */
/*   Updated: 2016/09/22 17:58:58 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	*get_set_options_handler(void *ptr, char option)
{
	static void		*data = NULL;

	if (option == 1)
		data = ptr;
	return (data);
}

void	clear_options(void)
{
	get_set_options_handler(NULL, 1);
}

void	void_options(t_flags *options)
{
	options->g = 0;
	options->n = 0;
	options->o = 0;
	options->p = 0;
	options->r = 0;
	options->u = 0;
	options->u_maj = 0;
	options->j = 0;
}

void	set_options(char **argv, int i, int x, t_flags *options)
{
	if (argv[i][x] == 'g')
		options->g = 1;
	if (argv[i][x] == 'n')
		options->n = 1;
	if (argv[i][x] == 'o')
		options->o = 1;
	if (argv[i][x] == 'p')
		options->p = 1;
	if (argv[i][x] == 'r')
		options->r = 1;
	if (argv[i][x] == 'u')
		options->u = 1;
	if (argv[i][x] == 'U')
		options->u_maj = 1;
	if (argv[i][x] == 'j')
		options->j = 1;
}

int		read_options(int argc, char **argv, t_flags *options)
{
	int		i;
	int		x;

	i = 1;
	while (i < argc)
	{
		if (argv[i][0] != '-')
			return (i);
		x = 1;
		while (argv[i][x])
		{
			set_options(argv, i, x, options);
			x++;
		}
		i++;
	}
	return (i);
}
