

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
	uint32_t		size;

	size = (sizeof(char) * ft_strlen(command)) + sizeof(t_packet_header);
	if (!(to_send = (unsigned char*)malloc(size)))
		return (0);
	header = (t_packet_header*)to_send;
	header->type = type;
	header->tot_data_len = htonl(size);
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

void	handle_ret(int server, char *resp, int len,
												t_response_type *resp_type)
{
	t_ret_packet_header	*header;

	(void)server;
	(void)resp_type;
	header = (t_ret_packet_header*)resp;
	write(1, resp + sizeof(t_ret_packet_header),
										len - sizeof(t_ret_packet_header));
	ft_putstr("\n");
	if (header->status == RET_ERROR)
		ft_putstr("ERROR\n");
	else
		ft_putstr("SUCCESS\n");
}

char	complete_ret(int server, char **to_complete, int *size)
{
	t_ret_packet_header	*header;
	int					ret;
	char				*buffer;
	char				*tmp;

	if (!(buffer = (char*)malloc(sizeof(char) * READ_BUFF_LEN)))
	{
		ft_putstr("malloc error\n");
		return (0);
	}
	header = (t_ret_packet_header*)*to_complete;
	while ((ret = read(server, buffer, READ_BUFF_LEN - 1)))
	{
		buffer[ret] = '\0';
		tmp = ft_strconcat(*to_complete, buffer, *size, ret + 1);
		if (!tmp)
		{
			ft_putstr("malloc error\n");
			return (0);
		}
		free(*to_complete);
		*to_complete = tmp;
		header = (t_ret_packet_header*)*to_complete;
		*size += ret;
		if ((size_t)(*size) > header->tot_data_len)
		{
			ft_putstr("weird size error\n");
			return (0);
		}
		if ((size_t)(*size) == header->tot_data_len)
			break ;
	}
	if (ret == -1)
	{
		ft_putstr("read error\n");
		return (0);
	}
	return (1);
}

void	interpret_ret(int server, char *buffer, int ret,
												t_response_type *resp_type)
{
	t_ret_packet_header	*header;

	header = (t_ret_packet_header*)buffer;
	header->tot_data_len = ntohl(header->tot_data_len);
	if ((size_t)ret > header->tot_data_len)
	{
		ft_putstr("weird size error\nERROR\n");
		return ;
	}
	if ((size_t)ret < header->tot_data_len && resp_type->type != CMD_GET)
	{
		if (!(complete_ret(server, &buffer, &ret)))
			return ;
	}
	handle_ret(server, buffer, ret, resp_type);
}

void	read_response(int server, char type, char *filename)
{
	char			*buffer;
	int				ret;
	t_response_type	resp_type;

	resp_type.type = type;
	resp_type.filename = filename;
	if (!(buffer = (char*)malloc(sizeof(char) * READ_BUFF_LEN)))
	{
		ft_putstr("malloc error\n");
		return ;
	}
	ret = read(server, buffer, READ_BUFF_LEN - 1);
	if (ret == -1)
	{
		ft_putstr("read error\n");
		return ;
	}
	buffer[ret] = '\0';
	interpret_ret(server, buffer, ret, &resp_type);
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
		if (!(send_raw_command(server, CMD_RAW_COMMAND, command)))
			ft_putstr("Could not send command\n");
		free(command);
		read_response(server, CMD_RAW_COMMAND, NULL);
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