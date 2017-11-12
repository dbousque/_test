

#include "irc_client.h"

char	connect_to_server(t_env *e, t_opts *opts)
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

char	send_user_input_to_server(t_env *e, char *buffer)
{
	int		ret;

	ret = read(0, buffer, READ_BUFFER_SIZE - 2);
	if (ret == -1 || ret == 0)
	{
		printf(ret == -1 ? "Error while reading input\n" : "Bye\n");
		close(e->server_fd);
		return (0);
	}
	if (buffer[ret - 1] == '\n')
	{
		buffer[ret - 1] = '\r';
		buffer[ret] = '\n';
		ret++;
	}
	buffer[ret] = '\0';
	//if (startswith(buffer, "/connect"))
	if ((write(e->server_fd, buffer, ret)) == -1)
	{
		printf("Error while sending input to server\n");
		close(e->server_fd);
		return (0);
	}
	return (1);
}

char	read_server_input(t_env *e, char *buffer)
{
	int		ret;

	ret = read(e->server_fd, buffer, READ_BUFFER_SIZE - 1);
	if (ret == -1)
	{
		printf("Error while reading server input\n");
		close(e->server_fd);
		return (0);
	}
	buffer[ret] = '\0';
	if (ret > 0)
		printf("%s\n", buffer);
	return (1);
}

void	main_loop(t_env *e)
{
	char	buffer[READ_BUFFER_SIZE];
	int		highest_fd;
	int		nb_ready;

	while (1)
	{
		FD_ZERO(&(e->read_fds));
		FD_SET(0, &(e->read_fds));
		if (e->connected)
			FD_SET(e->server_fd, &(e->read_fds));
		highest_fd = e->server_fd > 0 ? e->server_fd : 0;
		nb_ready = select(highest_fd + 1, &(e->read_fds), NULL, NULL, NULL);
		if (nb_ready == -1)
		{
			printf("Select error\n");
			close(e->server_fd);
			return ;
		}
		if (nb_ready > 0)
		{
			if (e->connected && FD_ISSET(e->server_fd, &(e->read_fds)))
			{
				if (!read_server_input(e, buffer))
					return ;
				nb_ready--;
			}
			if (nb_ready > 0 && FD_ISSET(0, &(e->read_fds)))
			{
				if (!send_user_input_to_server(e, buffer))
					return ;
				nb_ready--;
			}
		}
	}
}

int		main(int argc, char **argv)
{
	t_opts	opts;
	t_env	e;

	init_env(&e);
	if (!parse_options(&opts, argc, argv))
		return (0);
	if (opts.host && opts.port && !connect_to_server(&e, &opts))
		printf("Could not connect to server\n");
	main_loop(&e);
	return (1);
}