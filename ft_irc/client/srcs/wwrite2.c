

#include "irc_client.h"

char	server_info(char *str, int len, char ori)
{
	if (startswith(str, "[USERS]"))
	{
		wclear(g_windows.users_win);
		wrefresh(g_windows.users_win);
		wrefresh(g_windows.input_win);
		return (1);
	}
	if (startswith(str, "[USER] "))
	{
		ori = str[len];
		str[len] = '\0';
		wwrite(g_windows.users_win, str + 7);
		str[len] = ori;
		wrefresh(g_windows.users_win);
		wrefresh(g_windows.input_win);
		return (1);
	}
	if (startswith(str, "[NICK] "))
	{
		update_nick_info("          ");
		update_nick_info(str + 7);
		wrefresh(g_windows.info_win);
		wrefresh(g_windows.input_win);
		return (1);
	}
	return (0);
}

char	server_info2(char *str, int i)
{
	if (startswith(str, "[NOPRIVUSER]"))
	{
		g_priv_user_mode = 0;
		return (1);
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
		return (1);
	}
	return (0);
}

void	wwrite_chars(t_window *window, char *str, int len, char color)
{
	int		i;

	i = 0;
	if (server_info(str, len, 0) || server_info2(str, i))
		return ;
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

void	win_write(char *str)
{
	wwrite(g_windows.text_win, str);
}

void	win_input_write(char *str)
{
	wwrite(g_windows.input_win, str);
}
