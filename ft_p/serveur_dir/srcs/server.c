/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 15:55:15 by dbousque          #+#    #+#             */
/*   Updated: 2016/12/08 15:55:17 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p_server.h"

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
		handle_put(client, options, (char*)data, len);
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
	}
	if (ret == -1)
	{
		ft_client_error(client, "read failed");
		return ;
	}
}

void	handle_client(t_client_data *client, t_options *options)
{
	client->launch_dir = NULL;
	get_current_dir(&(client->launch_dir));
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
