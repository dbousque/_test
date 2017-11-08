

#include "ft_irc.h"

void	interpret_message(t_env *e, t_user *user, int len)
{
	t_parse_message_res		res;
	t_msg					parsed_msg;

	init_msg(&parsed_msg);
	res = parse_message(g_tmp_buffer, len, &parsed_msg);
	if (res != OK)
		return print_parse_message_error(res);
	print_msg(&parsed_msg);
}

void	read_user_input(t_env *e, int i)
{
	t_user	*user;
	int		ret;

	user = &((e->users)[i]);
	ret = read(user->fd, g_tmp_buffer, 512);
	if (ret <= 0)
	{
		if (ret == 0)
			LOG(INFO, "user '%s' exiting", user->nickname);
		else
			LOG(ERROR, "error while reading '%s' input", user->nickname);
		remove_user(e->users, i, e->nb_users);
		return ;
	}
	circular_buffer_write(&(user->read_buffer), g_tmp_buffer, ret);
	ret = circular_buffer_cpy(&(user->read_buffer), g_tmp_buffer);
	g_tmp_buffer[ret] = '\0';
	if (ret >= 2 && g_tmp_buffer[ret - 2] == '\r'
		&& g_tmp_buffer[ret - 1] == '\n')
	{
		user->read_buffer.start = 0;
		user->read_buffer.end = 0;
		g_tmp_buffer[ret - 2] = '\0';
		LOG(INFO, "user '%s' sent : %s", user->nickname, g_tmp_buffer);
		g_tmp_buffer[ret - 2] = '\r';
		interpret_message(e, user, ret);
	}
	else
		LOG(INFO, "user '%s' sent : %s", user->nickname, g_tmp_buffer);
}
