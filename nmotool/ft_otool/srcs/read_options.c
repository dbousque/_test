/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_options.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 18:38:41 by dbousque          #+#    #+#             */
/*   Updated: 2016/09/22 18:38:43 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

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
	options->t = 0;
}

void	set_options(char **argv, int i, int x, t_flags *options)
{
	if (argv[i][x] == 't')
		options->t = 1;
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
