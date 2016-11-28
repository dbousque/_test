

#include "ft_p_server.h"

char	complete_command(t_client_data *client, unsigned char **data,
											int *len, uint32_t cmd_len)
{
	unsigned char	*tmp_data;
	unsigned char	*new_data;
	int				ret;
	int				i;

	if (!(tmp_data = (unsigned char*)malloc(READ_BUFF_LEN)))
	{
		ft_client_error(client, "malloc failed");
		return (0);
	}
	i = 0;
	while ((ret = read(client->fd, (void*)tmp_data, READ_BUFF_LEN - 1)) > 0)
	{
		tmp_data[ret] = '\0';
		new_data = (unsigned char*)ft_strconcat((char*)*data, (char*)tmp_data, *len, ret + 1);
		if (!new_data)
		{
			ft_client_error(client, "malloc failed");
			return (0);
		}
		if (i > 0)
			free(*data);
		*data = new_data;
		*len += ret;
		if (((size_t)*len) > cmd_len)
		{
			ft_client_error(client, "weird size error");
			return (0);
		}
		if ((size_t)(*len) == cmd_len)
			break ;
		i++;
	}
	free(tmp_data);
	if (ret == -1)
	{
		ft_client_error(client, "read failed");
		return (0);
	}
	return (1);
}

void	interpret_data(t_client_data *client, t_options *options,
											unsigned char *data, int len)
{
	t_packet_header	*header;

	header = (t_packet_header*)data;
	header->tot_data_len = ntohl(header->tot_data_len);
	if ((size_t)len > header->tot_data_len)
	{
		ft_client_error(client, "weird size error");
		return ;
	}
	if (header->type == CMD_PUT)
	{
		handle_put(client, options, data, len);
		return ;
	}
	if ((size_t)len < header->tot_data_len)
	{
		if (!complete_command(client, &data, &len, header->tot_data_len))
			return ;
	}
	interpret_command(client, options, data, len);
}

void	communicate(t_client_data *client, t_options *options)
{
	int				ret;
	unsigned char	*data;

	data = (unsigned char*)malloc(READ_BUFF_LEN);
	if (!data)
	{
		ft_client_error(client, "malloc failed");
		return ;
	}
	while ((ret = read(client->fd, (void*)data, READ_BUFF_LEN - 1)) > 0)
	{
		data[READ_BUFF_LEN] = '\0';
		interpret_data(client, options, data, ret);
		/*data[ret] = '\0';
		ft_putstr(" -> from ");
		ft_putstr(client->ip_name);
		ft_putstr(" : ");
		ft_putstr((char*)data);
		if (ret > 0 && data[ret - 1] != '\n')
			ft_putstr("\n");*/
	}
	if (ret == -1)
	{
		ft_client_error(client, "read failed");
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

void	launch_server(int server, t_options *options, char **env)
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
		client.env = env;
		client.ip_name = ft_strcpy(inet_ntoa(client.sockaddr.sin_addr));
		if (options->log)
			log_connection(&client);
		pid = fork();
		if (pid < 0)
		{
			ft_client_error(&client, "fork failed");
			continue ;
		}
		if (pid == 0)
			handle_client(&client, options);
	}
}