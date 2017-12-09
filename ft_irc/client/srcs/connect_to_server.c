/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_to_server.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 16:52:47 by dbousque          #+#    #+#             */
/*   Updated: 2017/12/09 16:52:49 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_client.h"

char	connect_to_server_ipv4(t_env *e, t_opts *opts)
{
	struct sockaddr_in	serv_addr;
	struct protoent		*proto;

	proto = getprotobyname("tcp");
	if (!proto)
		return (0);
	e->server_fd = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	if (e->server_fd == -1)
		return (0);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(opts->port);
	serv_addr.sin_addr.s_addr = inet_addr(opts->host);
	if ((int)serv_addr.sin_addr.s_addr == -1)
		return (0);
	if (connect(e->server_fd, (struct sockaddr *)&serv_addr,
		sizeof(serv_addr)) == -1)
	{
		return (0);
	}
	e->connected = 1;
	return (1);
}

char	connect_to_server_ipv6(t_env *e, t_opts *opts)
{
	struct sockaddr_in6	serv_addr;
	struct protoent		*proto;

	proto = getprotobyname("tcp");
	if (!proto)
		return (0);
	e->server_fd = socket(AF_INET6, SOCK_STREAM, proto->p_proto);
	if (e->server_fd == -1)
		return (0);
	serv_addr.sin6_family = AF_INET6;
	serv_addr.sin6_port = htons(opts->port);
	if (inet_pton(AF_INET6, opts->host, &serv_addr.sin6_addr) != 1)
		return (0);
	if (connect(e->server_fd, (struct sockaddr *)&serv_addr,
		sizeof(serv_addr)) == -1)
	{
		return (0);
	}
	e->connected = 1;
	return (1);
}

char	connect_to_server(t_env *e, t_opts *opts)
{
	char	is_ipv6;
	int		i;

	is_ipv6 = 0;
	i = 0;
	while (opts->host[i])
	{
		if (opts->host[i] == ':')
		{
			is_ipv6 = 1;
			break ;
		}
		i++;
	}
	if (is_ipv6)
		return (connect_to_server_ipv6(e, opts));
	return (connect_to_server_ipv4(e, opts));
}

char	try_connect(t_env *e, char *host, char *port)
{
	int		argc;
	char	*argv[3];
	t_opts	opts;

	argc = 2;
	argv[1] = host;
	if (port)
	{
		argc = 3;
		argv[2] = port;
	}
	if (!parse_options(&opts, argc, argv))
		return (1);
	if (e->connected)
	{
		win_write("Disconnecting from current server...\n");
		close(e->server_fd);
		e->connected = 0;
	}
	if (opts.host && opts.port && !connect_to_server(e, &opts))
		win_write("|x Could not connect to server\n");
	return (1);
}

char	handle_reconnect_command_parse_res(t_env *e, t_msg *msg)
{
	int		nb_params;
	char	*port;

	nb_params = 0;
	while (msg->params[nb_params])
		nb_params++;
	if (nb_params > 0 && msg->params[nb_params - 1][0] == '\0')
		nb_params--;
	if (nb_params <= 0 || nb_params > 2)
	{
		win_write("|x Wrong number of params for /connect, expects 1 or 2\n");
		return (1);
	}
	port = nb_params > 1 ? msg->params[1] : NULL;
	try_connect(e, msg->params[0], port);
	return (1);
}
