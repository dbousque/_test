

#include "ft_irc.h"

void	write_user_output(t_env *e, int i)
{
	t_user	*user;
	int		n;

	user = &(e->users[i]);
	n = circular_buffer_read(&(user->write_buffer), g_tmp_buffer);
	if (write(user->fd, g_tmp_buffer, n) == -1)
	{
		LOG(ERROR, "error while writing to '%s' output", user->nickname);
		remove_user(e, user);
	}
}
