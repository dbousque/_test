/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_flags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 19:12:39 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/08 19:31:31 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_flag	*void_flags(void)
{
	t_flag	*flags;

	if (!(flags = (t_flag*)malloc(sizeof(t_flag))))
		return (NULL);
	flags->n = 0;
	flags->c = 0;
	return (flags);
}

int		flags_error(void)
{
	ft_putendl_fd("bad flags format", 2);
	return (0);
}

int		get_flags(int argc, char **argv, t_flag *flags)
{
	int		i;

	i = 1;
	while (i < argc)
	{
		if (ft_strcmp(argv[i], "-n") == 0)
			flags->n = 1;
		else if (ft_strcmp(argv[i], "-c") == 0)
			flags->c = 1;
		else if (ft_strcmp(argv[i], "-b") == 0)
			flags->b = 1;
		else
			return (flags_error());
		i++;
	}
	return (1);
}
