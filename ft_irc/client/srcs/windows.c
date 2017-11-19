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

void	wwrite_chars(t_window *window, char *str, int len, char color)
{
	int		i;
	char	ori;

	if (startswith(str, "[USERS]"))
	{
		wclear(g_windows.users_win);
		wrefresh(g_windows.users_win);
		wrefresh(g_windows.input_win);
		return ;
	}
	if (startswith(str, "[USER] "))
	{
		ori = str[len];
		str[len] = '\0';
		wwrite(g_windows.users_win, str + 7);
		str[len] = ori;
		wrefresh(g_windows.users_win);
		wrefresh(g_windows.input_win);
		return ;
	}
	if (startswith(str, "[NICK] "))
	{
		update_nick_info("          ");
		update_nick_info(str + 7);
		wrefresh(g_windows.info_win);
		wrefresh(g_windows.input_win);
		return ;
	}
	if (startswith(str, "[NOPRIVUSER]"))
	{
		g_priv_user_mode = 0;
		return ;
	}
	if (startswith(str, "[PRIVUSER] "))
	{
		g_priv_user_mode = 1;
		i = 0;
		str += 11;
		while (str[i] && str[i] != '\r' && str[i] != '\n')
		{
			g_priv_user[i] = str[i];
			i++;
		}
		while (i < 9)
		{
			g_priv_user[i] = ' ';
			i++;
		}
		g_priv_user[i] = '\0';
		return ;
	}
	i = 0;
	while (i < len || (len == -1 && str[i]))
	{
		if (len == -1)
			waddch(window, str[i] | COLOR_PAIR(color) | A_BOLD);
		else
			waddch(window, str[i] | COLOR_PAIR(color));
		i++;
	}
}

char	green_instruction(char *str, int ind)
{
	if (str[ind] == '|' && str[ind + 1] == '>' && str[ind + 2] == ' ')
		return (1);
	return (0);
}

char	red_instruction(char *str, int ind)
{
	if (str[ind] == '|' && str[ind + 1] == 'x' && str[ind + 2] == ' ')
		return (1);
	return (0);
}

void	maybe_green_or_red_instruction(char *str, int *start, char *color)
{
	if (green_instruction(str, *start))
	{
		*color = 2;
		*start += 3;
	}
	else if (red_instruction(str, *start))
	{
		*color = 1;
		*start += 3;
	}
}

void	wwrite(t_window *window, char *str)
{
	int		start;
	int		i;
	int		len;
	char	color;

	color = 0;
	len = ft_strlen(str);
	if (len < 4)
	{
		wwrite_chars(window, str, len, color);
		wrefresh(window);
		wrefresh(g_windows.input_win);
		return;
	}
	start = 0;
	maybe_green_or_red_instruction(str, &start, &color);
	i = start;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			wwrite_chars(window, str + start, i - start + 1, color);
			color = 0;
			start = i + 1;
			maybe_green_or_red_instruction(str, &start, &color);
		}
		i++;
	}
	if (i - start > 1)
		wwrite_chars(window, str + start, i - start, color);
	wrefresh(window);
	wrefresh(g_windows.input_win);
}

void	win_write(char *str)
{
	wwrite(g_windows.text_win, str);
}

void	win_input_write(char *str)
{
	wwrite(g_windows.input_win, str);
}

void	close_windows(void)
{
	endwin();
}

void	init_windows2(void)
{
	wmove(g_windows.input_win, 0, 0);
	wrefresh(g_windows.users_win);
	wrefresh(g_windows.info_win);
	wrefresh(g_windows.text_win);
	wrefresh(g_windows.input_win);
}

void	init_windows(void)
{
	t_window	*input_win_container;
	t_window	*text_win_container;
	t_window	*users_win_container;

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
	refresh();
	text_win_container = newwin(LINES - 9, COLS - 21, 6, 0);
	input_win_container = newwin(3, COLS, LINES - 3, 0);
	users_win_container = newwin(LINES - 3, 20, 0, COLS - 20);
	g_windows.users_win = newwin(LINES - 7, 17, 3, COLS - 18);
	g_windows.info_win = newwin(6, COLS - 21, 0, 0);
	g_windows.input_win = newwin(1, COLS - 3, LINES - 2, 2);
	g_windows.text_win = newwin(LINES - 13, COLS - 24, 9, 2);
	box(text_win_container, 0, 0);
	box(input_win_container, 0, 0);
	box(users_win_container, 0, 0);
	box(g_windows.info_win, 0, 0);
	wmove(text_win_container, 1, 2);
	wwrite_chars(text_win_container, "SERVER OUTPUT", -1, 3);
	wmove(users_win_container, 1, 2);
	wwrite_chars(users_win_container, "USERS ON SERVER", -1, 3);
	wmove(g_windows.info_win, 1, 2);
	wwrite_chars(g_windows.info_win, "INFO", -1, 3);
	scrollok(g_windows.text_win, TRUE);
	wrefresh(input_win_container);
	wrefresh(text_win_container);
	wrefresh(users_win_container);
	init_windows2();
}
