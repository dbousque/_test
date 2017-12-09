/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 17:45:17 by dbousque          #+#    #+#             */
/*   Updated: 2017/12/09 17:45:19 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_client.h"

void	update_connected_info(char connected)
{
	wmove(g_windows.info_win, 3, COLS - 37);
	wprintw(g_windows.info_win, "connection ");
	if (connected)
	{
		waddch(g_windows.info_win, ' ' | A_REVERSE | COLOR_PAIR(2));
		waddch(g_windows.info_win, ' ' | A_REVERSE | COLOR_PAIR(2));
	}
	else
	{
		waddch(g_windows.info_win, ' ' | A_REVERSE | COLOR_PAIR(1));
		waddch(g_windows.info_win, ' ' | A_REVERSE | COLOR_PAIR(1));
	}
}

void	update_nick_info(char *nick)
{
	wmove(g_windows.info_win, 3, 2);
	wprintw(g_windows.info_win, "nick : ");
	wwrite(g_windows.info_win, nick);
}

void	set_info(char *nick, char connected)
{
	update_nick_info("          ");
	update_nick_info(nick);
	update_connected_info(connected);
	wrefresh(g_windows.info_win);
	wrefresh(g_windows.input_win);
}

void	update_info_if_necessary(t_env *e, struct timeval *now)
{
	if (now->tv_sec - e->last_users_update.tv_sec > 4)
	{
		write(e->server_fd, "/users\r\n", 8);
		e->last_users_update = *now;
	}
	else if (now->tv_sec - e->last_nick_update.tv_sec > 4)
	{
		write(e->server_fd, "/mynick\r\n", 9);
		e->last_nick_update = *now;
	}
	else if (now->tv_sec - e->last_privuser_update.tv_sec > 4)
	{
		write(e->server_fd, "/privuser\r\n", 11);
		e->last_privuser_update = *now;
	}
}

void	update_info(t_env *e)
{
	struct timeval	now;

	if (!e->connected)
	{
		wclear(g_windows.users_win);
		wrefresh(g_windows.users_win);
		set_info("-", 0);
		return ;
	}
	update_connected_info(1);
	wrefresh(g_windows.info_win);
	wrefresh(g_windows.input_win);
	gettimeofday(&now, NULL);
	update_info_if_necessary(e, &now);
}
