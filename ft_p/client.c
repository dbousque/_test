

#include "ft_p_client.h"

void	usage(char *command)
{
	ft_putstr("Usage : ");
	ft_putstr(command);
	ft_putstr(" <host> <port[1-65535]>\n");
	exit(-1);
}

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

char	send_raw_command(int server, char type, char *command)
{
	t_packet_header	*header;
	unsigned char	*to_send;
	uint64_t		size;

	size = (sizeof(char) * ft_strlen(command)) + sizeof(t_packet_header);
	if (!(to_send = (unsigned char*)malloc(size)))
		return (0);
	header = (t_packet_header*)to_send;
	header->type = type;
	header->tot_data_len = size;
	ft_strcat((char*)to_send, command, sizeof(t_packet_header),
														ft_strlen(command));
	write(server, to_send, size);
	return (1);
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
	while ((ret = read(0, buffer, 512)))
	{
		if (!(tmp = ft_strconcat(inp, buffer, size, ret)))
			return (inp_error("malloc error\n"));
		if (size > 0)
			free(inp);
		inp = tmp;
		size += ret;
		buffer[ret] = '\0';
		if (char_in_str(buffer, '\n'))
			break ;
	}
	if (ret == -1)
		return (inp_error("read error\n"));
	inp[size] = '\0';
	return (inp);
}

#  include <stdio.h>
// NEED TO CHANGE WITH PROPER PROTOCOL FOR GET. NOW !!!
void	read_response(int server)
{
	char	buffer[512];
	int		ret;

	while ((ret = read(server, buffer, 511)))
	{
		buffer[ret] = '\0';
		ft_putstr(buffer);
		printf("\n (nb)%d %s", ret, buffer);
		fflush(stdout);
		if ((ret == 5 && ft_strcmp(buffer, "ERROR") == 0)
			|| (ret == 7 && ft_strcmp(buffer, "SUCCESS") == 0))
		{
			ft_putstr("\n");
			break ;
		}
	}
	if (ret == -1)
		ft_putstr("read error\n");
}

void	launch_client(t_options *options)
{
	int				server;
	char			*command;

	ft_putstr("  --- FTP client ---\n");
	server = connect_to_server(options);
	if (!server)
	{
		ft_putstr("Could not establish connection with server.\nExiting.\n");
		return ;
	}
	ft_putstr("Connection established.\n\n");
	while (1)
	{
		ft_putstr(" $> ");
		command = get_input();
		if (!command || ft_strcmp(command, "quit") == 0)
		{
			ft_putstr("Bye\n");
			break ;
		}
		if (!(send_raw_command(server, CMD_RAW_COMMAND, command)))
			ft_putstr("Could not send command\n");
		free(command);
		read_response(server);
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