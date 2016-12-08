/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 16:28:03 by dbousque          #+#    #+#             */
/*   Updated: 2016/12/08 16:30:57 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p_client.h"

int		connect_to_server(t_options *options)
{
	struct sockaddr_in	serv_addr;
	int					sock;
	struct protoent		*proto;

	proto = getprotobyname("tcp");
	if (!proto)
		return (-1);
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	if (sock == -1)
		return (-1);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(options->port);
	serv_addr.sin_addr.s_addr = inet_addr(options->host);
	if ((int)serv_addr.sin_addr.s_addr == -1)
		return (-1);
	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
		return (-1);
	return (sock);
}

char	*inp_error(char *msg)
{
	ft_putstr(msg);
	return (NULL);
}

char	*get_input(void)
{
	char	buffer[512];
	char	*inp;
	char	*tmp;
	size_t	size;
	int		ret;

	size = 0;
	while ((ret = read(0, buffer, 511)))
	{
		buffer[ret] = '\0';
		if (!(tmp = ft_strconcat(inp, buffer, size, ret + 1)))
			return (inp_error("malloc error\n"));
		if (size > 0)
			free(inp);
		inp = tmp;
		size += ret;
		if (char_in_str(buffer, '\n'))
			break ;
	}
	if (ret == -1)
		return (inp_error("read error\n"));
	inp[size] = '\0';
	return (inp);
}

void	launch_client(t_options *options)
{
	int				server;
	char			*command;

	ft_putstr("  --- FTP client ---\n");
	server = connect_to_server(options);
	if (server == -1)
	{
		ft_putstr("Could not establish connection with server.\nExiting.\n");
		return ;
	}
	ft_putstr("Connection established.\n\n");
	while (1)
	{
		ft_putstr(" $> ");
		command = get_input();
		if (!command || ft_strcmp(command, "quit\n") == 0)
		{
			ft_putstr("Bye\n");
			break ;
		}
		if (send_command(server, options, command))
			read_response(server, get_type_of_command(command), NULL);
		free(command);
	}
	close(server);
}

int		main(int argc, char **argv)
{
	t_options	options;

	if (argc <= 2)
		usage(argv[0]);
	parse_options(argc, argv, &options);
	if (options.error)
		usage(argv[0]);
	launch_client(&options);
	return (0);
}
