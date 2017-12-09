/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 16:52:31 by dbousque          #+#    #+#             */
/*   Updated: 2017/12/09 16:52:33 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_client.h"

char	read_server_input(t_env *e, char *buffer)
{
	int		ret;

	ret = read(e->server_fd, buffer, READ_BUFFER_SIZE - 1);
	if (ret == 0)
	{
		win_write("|x Server disconnected\n");
		e->connected = 0;
		e->server_fd = -1;
	}
	if (ret == -1)
	{
		close_windows();
		printf("Error while reading server input\n");
		close(e->server_fd);
		return (0);
	}
	buffer[ret] = '\0';
	if (ret < 4)
		win_write(buffer);
	else
		win_write(buffer);
	return (1);
}

char	read_input(t_env *e, int nb_ready, int *n_chars,
											char buffers[2][READ_BUFFER_SIZE])
{
	if (nb_ready > 0)
	{
		if (e->connected && FD_ISSET(e->server_fd, &(e->read_fds)))
		{
			if (!read_server_input(e, buffers[0]))
				return (0);
			nb_ready--;
		}
		if (nb_ready > 0 && FD_ISSET(0, &(e->read_fds)))
		{
			if (!read_user_input(e, buffers[1], n_chars))
				return (0);
			nb_ready--;
		}
	}
	return (1);
}

void	main_loop(t_env *e, struct timeval *timeout)
{
	char	buffers[2][READ_BUFFER_SIZE];
	int		n_chars;
	int		highest_fd;
	int		nb_ready;

	n_chars = 0;
	while (1)
	{
		update_info(e);
		FD_ZERO(&(e->read_fds));
		FD_SET(0, &(e->read_fds));
		if (e->connected)
			FD_SET(e->server_fd, &(e->read_fds));
		highest_fd = e->server_fd > 0 ? e->server_fd : 0;
		timeout->tv_sec = 2;
		timeout->tv_usec = 0;
		nb_ready = select(highest_fd + 1, &(e->read_fds), NULL, NULL, timeout);
		if (nb_ready == -1)
			continue ;
		if (!read_input(e, nb_ready, &n_chars, buffers))
			return ;
	}
}

int		main(int argc, char **argv)
{
	t_opts			opts;
	t_env			e;
	struct timeval	timeout;

	g_priv_user_mode = 0;
	init_commands_names();
	init_env(&e);
	if (!parse_options(&opts, argc, argv))
		return (0);
	init_windows();
	if (opts.host && opts.port && !connect_to_server(&e, &opts))
		win_write("|x Could not connect to server\n");
	main_loop(&e, &timeout);
	close_windows();
	return (1);
}
