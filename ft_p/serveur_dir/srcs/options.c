/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 15:55:08 by dbousque          #+#    #+#             */
/*   Updated: 2016/12/15 18:34:32 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p_server.h"

int		parse_port(char *port)
{
	size_t	i;
	int		res;

	i = 0;
	while (port[i] && port[i] >= '0' && port[i] <= '9')
		i++;
	if (port[i] != '\0' || i > 5)
		return (0);
	i = 0;
	res = 0;
	while (port[i])
	{
		res = res * 10 + (port[i] - '0');
		i++;
	}
	return (res);
}

void	parse_options(int argc, char **argv, t_options *options)
{
	options->strict = 1;
	if (argc > 4)
	{
		options->error = 1;
		return ;
	}
	if (argc > 2)
	{
		if (chdir(argv[2]) == -1)
		{
			ft_putstr("invalid start directory\n");
			options->error = 1;
			return ;
		}
		if (argc == 4 && ft_strcmp(argv[3], "any") == 0)
			options->strict = 0;
	}
	options->port = parse_port(argv[1]);
	if (options->port < 1 || options->port > 65535)
	{
		options->error = 1;
		return ;
	}
	options->log = 1;
}
