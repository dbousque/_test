/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 15:54:58 by dbousque          #+#    #+#             */
/*   Updated: 2016/12/08 15:55:00 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p_server.h"

int		create_server(int port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;
	int					ret;

	proto = getprotobyname("tcp");
	if (!proto)
		return (-1);
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	if (sock == -1)
		return (-1);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	ret = bind(sock, (const struct sockaddr*)&sin, sizeof(sin));
	if (ret == -1)
		return (-1);
	listen(sock, NB_CONNECTIONS);
	return (sock);
}

void	usage(char *command)
{
	ft_putstr("Usage : ");
	ft_putstr(command);
	ft_putstr(" <port[1-65535]> ?<start_dir> ?<[strict]>\n");
	exit(-1);
}

void	could_not_create_server(void)
{
	ft_putstr("Could not create server\n");
	exit(-1);
}

int		main(int argc, char **argv, char **env)
{
	t_options	options;
	int			server;

	if (argc <= 1)
		usage(argv[0]);
	parse_options(argc, argv, &options);
	if (options.error)
		usage(argv[0]);
	server = create_server(options.port);
	if (server == -1)
		could_not_create_server();
	launch_server(server, &options, env);
	return (0);
}
