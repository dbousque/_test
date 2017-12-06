

#include "irc_client.h"

char	read_error_or_ctrl_d(t_env *e, char character, int *n_chars, int ret)
{
	if (ret != -1 && character == 4 && *n_chars)
		return (1);
	close_windows();
	printf(ret == -1 ? "Error while reading input\n" : "Bye\n");
	close(e->server_fd);
	return (0);
}

char	read_user_input2(t_env *e, char *read_buffer, int *n_chars)
{
	char	connect_ret;

	wclear(g_windows.input_win);
	wmove(g_windows.input_win, 0, 0);
	wrefresh(g_windows.input_win);
	if (g_priv_user_mode && !startswith(read_buffer, "/stdmode")
		&& *n_chars + 16 < READ_BUFFER_SIZE - 2)
	{
		prepend_privmsg(read_buffer, *n_chars);
		*n_chars += 16;
	}
	connect_ret = reconnect_if_connect_command(e, read_buffer, *n_chars);
	if (connect_ret == 1 || !e->connected)
		return (dont_send_to_server(e, read_buffer, n_chars, connect_ret));
	if (!connect_ret && (write(e->server_fd, read_buffer, *n_chars)) == -1)
	{
		*n_chars = 0;
		read_buffer[0] = '\0';
		close_windows();
		printf("Error while sending input to server\n");
		close(e->server_fd);
		return (0);
	}
	*n_chars = 0;
	read_buffer[0] = '\0';
	return (1);
}

char	user_input_too_long(char *read_buffer, int *n_chars)
{
	win_write("|x Input too long, flushing it\n");
	read_buffer[0] = '\0';
	*n_chars = 0;
	return (1);
}

char	read_user_input_put_to_window(char character)
{
	char	tmp[2];

	tmp[0] = character;
	tmp[1] = '\0';
	win_input_write(tmp);
	return (1);
}

char	read_user_input(t_env *e, char *read_buffer, int *n_chars)
{
	int		ret;
	char	character;

	if (*n_chars > READ_BUFFER_SIZE - 3)
		return (user_input_too_long(read_buffer, n_chars));
	ret = read(0, &character, 1);
	if (ret == -1 || ret == 0 || character == 4)
		return (read_error_or_ctrl_d(e, character, n_chars, ret));
	if (character == 127)
		return (remove_char(read_buffer, n_chars));
	read_buffer[*n_chars] = character;
	(*n_chars)++;
	if (character == '\r')
	{
		read_buffer[*n_chars] = '\n';
		(*n_chars)++;
	}
	read_buffer[*n_chars] = '\0';
	if (character != '\r')
		return (read_user_input_put_to_window(character));
	return (read_user_input2(e, read_buffer, n_chars));
}
