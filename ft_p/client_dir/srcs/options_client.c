/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_client.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 16:28:42 by dbousque          #+#    #+#             */
/*   Updated: 2016/12/08 16:28:44 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p_client.h"

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
	if (argc > 3)
	{
		options->error = 1;
		return ;
	}
	options->port = parse_port(argv[2]);
	if (options->port < 1 || options->port > 65535)
	{
		options->error = 1;
		return ;
	}
	options->log = 1;
	if (ft_strcmp(argv[1], "localhost") == 0)
		options->host = ft_strdup("127.0.0.1");
	else
		options->host = argv[1];
}
