/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 18:41:12 by dbousque          #+#    #+#             */
/*   Updated: 2017/11/18 18:41:15 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_client.h"

void	close_windows(void)
{
	endwin();
}

void	init_windows2(t_window *inp_win_container, t_window *text_win_container,
												t_window *users_win_container)
{
	wrefresh(inp_win_container);
	wrefresh(text_win_container);
	wrefresh(users_win_container);
	wmove(g_windows.input_win, 0, 0);
	wrefresh(g_windows.users_win);
	wrefresh(g_windows.info_win);
	wrefresh(g_windows.text_win);
	wrefresh(g_windows.input_win);
}

void	init_screen(void)
{
	initscr();
	start_color();
	if (has_colors() == FALSE)
	{
		endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	curs_set(2);
}

void	init_windows(void)
{
	t_window	*inp_win_container;
	t_window	*text_win_container;
	t_window	*users_win_container;

	init_screen();
	refresh();
	text_win_container = newwin(LINES - 9, COLS - 21, 6, 0);
	inp_win_container = newwin(3, COLS, LINES - 3, 0);
	users_win_container = newwin(LINES - 3, 20, 0, COLS - 20);
	g_windows.users_win = newwin(LINES - 7, 17, 3, COLS - 18);
	g_windows.info_win = newwin(6, COLS - 21, 0, 0);
	g_windows.input_win = newwin(1, COLS - 3, LINES - 2, 2);
	g_windows.text_win = newwin(LINES - 13, COLS - 24, 9, 2);
	box(text_win_container, 0, 0);
	box(inp_win_container, 0, 0);
	box(users_win_container, 0, 0);
	box(g_windows.info_win, 0, 0);
	wmove(text_win_container, 1, 2);
	wwrite_chars(text_win_container, "SERVER OUTPUT", -1, 3);
	wmove(users_win_container, 1, 2);
	wwrite_chars(users_win_container, "USERS ON SERVER", -1, 3);
	wmove(g_windows.info_win, 1, 2);
	wwrite_chars(g_windows.info_win, "INFO", -1, 3);
	scrollok(g_windows.text_win, TRUE);
	init_windows2(inp_win_container, text_win_container, users_win_container);
}
