

#include "ft_p_server.h"





void	handle_raw_command(t_client_data *client, t_options *options,
											unsigned char *data, size_t len)
{
	char		*command;
	wordexp_t	cmd_and_args;
	pid_t		pid;

	(void)client;
	(void)options;
	(void)len;
	command = ((char*)data) + sizeof(t_packet_header);


	// WE NEED TO PUT a \0 AT THE END OF DATA, AND THINK ABOUT HOW TO FREE
	// (dont't free if complete_command not called)

	wordexp(command, &cmd_and_args, 0);
	pid = fork();
	if (pid < 0)
	{
		ft_error("fork failed");
		return ;
	}
	if (pid == 0)
	{
		execv(cmd_and_args.we_wordv[0], cmd_and_args.we_wordv);
		exit(0);
	}
	else
		wait(NULL);
	wordfree(&cmd_and_args);
}

void	handle_put(t_client_data *client, t_options *options,
											unsigned char *data, size_t len)
{
	(void)client;
	(void)options;
	(void)data;
	(void)len;
}

void	handle_cd(t_client_data *client)
{
	(void)client;
}

void	interpret_command(t_client_data *client, t_options *options,
											unsigned char *data, size_t len)
{
	t_packet_header	*header;

	header = (t_packet_header*)data;
	if (header->type == CMD_RAW_COMMAND)
		handle_raw_command(client, options, data, len);
	else if (header->type == CMD_CD)
		handle_cd(client);
}

char	complete_command(t_client_data *client, unsigned char **data,
											size_t *len, uint64_t cmd_len)
{
	unsigned char	*tmp_data;
	size_t			ret;

	if (!(tmp_data = (unsigned char*)malloc(READ_BUFF_LEN)))
	{
		ft_error("malloc failed");
		return (0);
	}
	while ((ret = read(client->fd, (void*)tmp_data, READ_BUFF_LEN)) > 0)
	{
		*data = (unsigned char*)ft_strconcat((char*)*data, (char*)tmp_data, *len, ret);
		if (!*data)
		{
			ft_error("malloc failed");
			return (0);
		}
		*len += ret;
		if (*len > cmd_len)
		{
			ft_error("weird size error");
			return (0);
		}
		if (*len == cmd_len)
			break ;
	}
	if (ret == (size_t)-1)
	{
		ft_error("read failed");
		return (0);
	}
	return (1);
}

void	interpret_data(t_client_data *client, t_options *options,
											unsigned char *data, size_t len)
{
	t_packet_header	*header;

	header = (t_packet_header*)data;
	if (len > header->tot_data_len)
	{
		ft_error("weird size error");
		return ;
	}
	if (header->type == CMD_PUT)
	{
		handle_put(client, options, data, len);
		return ;
	}
	if (len < header->tot_data_len)
	{
		if (!complete_command(client, &data, &len, header->tot_data_len))
			return ;
	}
	interpret_command(client, options, data, len);
}

void	communicate(t_client_data *client, t_options *options)
{
	size_t					ret;
	unsigned char			*data;

	data = (unsigned char*)malloc(READ_BUFF_LEN);
	if (!data)
	{
		ft_error("malloc failed");
		return ;
	}
	while ((ret = read(client->fd, (void*)data, READ_BUFF_LEN)) > 0)
	{
		interpret_data(client, options, data, ret);
		/*data[ret] = '\0';
		ft_putstr(" -> from ");
		ft_putstr(client->ip_name);
		ft_putstr(" : ");
		ft_putstr((char*)data);
		if (ret > 0 && data[ret - 1] != '\n')
			ft_putstr("\n");*/
	}
	if (ret == (size_t)-1)
	{
		ft_error("read failed");
		return ;
	}
}

void	handle_client(t_client_data *client, t_options *options)
{
	size_t	size;

	size = 256;
	client->launch_dir = (char*)malloc(sizeof(char) * size);
	while (!(getcwd(client->launch_dir, size)))
	{
		free(client->launch_dir);
		size *= 2;
		client->launch_dir = (char*)malloc(sizeof(char) * size);
	}
	communicate(client, options);
	if (options->log)
		log_closing(client);
	close(client->fd);
	free(client->launch_dir);
	free(client->ip_name);
	exit(0);
}

void	launch_server(int server, t_options *options)
{
	t_client_data	client;
	pid_t			pid;

	while (1)
	{
		client.fd = accept(server, (struct sockaddr*)&(client.sockaddr),
															&(client.len));
		if (client.fd == -1)
		{
			ft_error("accept failed");
			continue ;
		}
		client.ip_name = ft_strcpy(inet_ntoa(client.sockaddr.sin_addr));
		if (options->log)
			log_connection(&client);
		pid = fork();
		if (pid < 0)
		{
			ft_error("fork failed");
			continue ;
		}
		if (pid == 0)
			handle_client(&client, options);
	}
}