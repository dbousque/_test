

#include "ft_p_server.h"

void	communicate(t_client_data *client, t_options *options)
{
	size_t					ret;
	unsigned char			*data;

	(void)options;
	data = (unsigned char*)malloc(READ_BUFF_LEN);
	if (!data)
	{
		ft_error("malloc failed");
		return ;
	}
	while ((ret = read(client->fd, (void*)data, READ_BUFF_LEN)) > 0)
	{
		data[ret] = '\0';
		ft_putstr(" -> from ");
		ft_putstr(client->ip_name);
		ft_putstr(" : ");
		ft_putstr((char*)data);
		if (ret > 0 && data[ret - 1] != '\n')
			ft_putstr("\n");
	}
	if (ret == (size_t)-1)
	{
		ft_error("read failed");
		return ;
	}
}

void	handle_client(t_client_data *client, t_options *options)
{
	communicate(client, options);
	if (options->log)
		log_closing(client);
	close(client->fd);
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