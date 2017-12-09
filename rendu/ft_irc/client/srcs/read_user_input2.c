/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_user_input2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 16:53:14 by dbousque          #+#    #+#             */
/*   Updated: 2017/12/09 16:53:15 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_client.h"

char	reconnect_if_connect_command(t_env *e, char *buffer, int len)
{
	t_msg					msg;
	t_parse_message_res		parse_res;

	if (!startswith(buffer, "/connect "))
		return (0);
	init_msg(&msg);
	parse_res = parse_message(buffer, len, &msg);
	if (parse_res != COMMAND_OK)
	{
		win_write("|x Invalid /connect command\n");
		return (1);
	}
	if (msg.command != CONNECT)
		return (1);
	return (handle_reconnect_command_parse_res(e, &msg));
}

void	ft_strcpy(char *dest, char *src)
{
	int		i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
}

void	prepend_privmsg(char *buffer, int len)
{
	int		i;

	i = len;
	while (i >= 0)
	{
		buffer[i + 16] = buffer[i];
		i--;
	}
	ft_strcpy(buffer, "/msg ");
	ft_strcpy(buffer + 5, g_priv_user);
	ft_strcpy(buffer + 14, " :");
}

char	remove_char(char *read_buffer, int *n_chars)
{
	char	tmp[2];

	if (*n_chars > 0)
		(*n_chars)--;
	read_buffer[*n_chars] = '\0';
	tmp[0] = ' ';
	tmp[1] = '\0';
	wmove(g_windows.input_win, 0, *n_chars);
	win_input_write(tmp);
	wmove(g_windows.input_win, 0, *n_chars);
	wrefresh(g_windows.input_win);
	return (1);
}

char	dont_send_to_server(t_env *e, char *read_buffer, int *n_chars,
															char connect_ret)
{
	*n_chars = 0;
	read_buffer[0] = '\0';
	if (connect_ret != 1 && !e->connected)
		win_write("Connect before sending commands\n");
	return (1);
}
