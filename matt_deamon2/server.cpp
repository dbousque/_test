

#include "matt_daemon.hpp"

int		create_server(int port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in6	sin;
	int					ret;

	proto = getprotobyname("tcp");
	if (!proto)
		return (-1);
	sock = socket(AF_INET6, SOCK_STREAM, proto->p_proto);
	if (sock == -1)
		return (-1);
	ret = 0;
	setsockopt(sock, IPPROTO_IPV6, IPV6_V6ONLY, &ret, sizeof(int));
	sin.sin6_family = AF_INET6;
	sin.sin6_port = htons(port);
	sin.sin6_addr = in6addr_any;
	ret = bind(sock, (const struct sockaddr*)&sin, sizeof(sin));
	if (ret == -1)
		return (-1);
	ret = listen(sock, MAX_NB_CLIENTS + 1);
	if (ret == -1)
		return (-1);
	return (sock);
}

bool	read_and_log_client_input(Tintin_reporter &reporter, int i, int *clients, int *nb_clients)
{
	char	buf[512];
	int		ret;
	int		x;

	ret = read(clients[i], buf, 511);
	if (ret < 0)
	{
		if (!(reporter.log((char*)"Could not read client input", INFO)))
			return (false);
	}
	if (ret <= 0)
	{
		if (!(reporter.log((char*)"Closing client", INFO)))
			return (false);
		x = i;
		while (x < *nb_clients - 1)
		{
			clients[x] = clients[x + 1];
			x++;
		}
		(*nb_clients)--;
		return (true);
	}
	if (ret == 5 && buf[0] == 'q' && buf[1] == 'u' && buf[2] == 'i' && buf[3] == 't' && buf[4] == '\n')
	{
		reporter.log((char*)"Request quit", INFO);
		return (false);
	}
	buf[ret] = '\0';
	if (!(reporter.log(buf, LOG)))
		return (false);
	return (true);
}

bool	accept_client(Tintin_reporter &reporter, int server_fd, int *clients, int *nb_clients)
{
	struct sockaddr_in	sin;
	socklen_t			len;

	clients[*nb_clients] = accept(server_fd, (struct sockaddr*)&sin, &len);
	if (*nb_clients >= MAX_NB_CLIENTS)
	{
		close(clients[*nb_clients]);
		if (!(reporter.log((char*)"Could not accept new client, too many clients connected", INFO)))
			return (false);
		return (true);
	}
	if (clients[*nb_clients] == -1)
	{
		if (!(reporter.log((char*)"accept failed", INFO)))
			return (false);
		return (true);
	}
	if (!(reporter.log((char*)"Accepted new client", INFO)))
		return (false);
	(*nb_clients)++;
	return (true);
}

void	run_server(Tintin_reporter &reporter, int server_fd, int lock_file_fd)
{
	int		highest_fd;
	int		clients[MAX_NB_CLIENTS];
	int		nb_clients;
	int		nb_ready;
	fd_set	fds;
	int		i;

	nb_clients = 0;
	while (1)
	{
		FD_ZERO(&fds);
		FD_SET(server_fd, &fds);
		highest_fd = server_fd;
		i = 0;
		while (i < nb_clients)
		{
			if (clients[i] > highest_fd)
				highest_fd = clients[i];
			FD_SET(clients[i], &fds);
			i++;
		}
		reporter.log((char*)"before select", INFO);
		nb_ready = select(highest_fd + 1, &fds, NULL, NULL, NULL);
		char buf[100];
		sprintf(buf, "nb_ready %d\n", nb_ready);
		reporter.log(buf, INFO);
		reporter.log((char*)"after select", INFO);
		if (nb_ready == -1)
		{
			reporter.log((char*)"select error", ERROR);
			return (exit_daemon(reporter, server_fd, lock_file_fd));
		}
		if (nb_ready > 0)
		{
			if (FD_ISSET(server_fd, &fds))
			{
				reporter.log((char*)"server_fd is ready !", INFO);
				if (!accept_client(reporter, server_fd, clients, &nb_clients))
					return (exit_daemon(reporter, server_fd, lock_file_fd));
				nb_ready--;
			}
			i = 0;
			while (i < nb_clients)
			{
				if (FD_ISSET(clients[i], &fds))
				{
					reporter.log((char*)"client is ready !", INFO);
					if (!read_and_log_client_input(reporter, i, clients, &nb_clients))
						return (exit_daemon(reporter, server_fd, lock_file_fd));
				}
				i++;
			}
		}
	}
}
