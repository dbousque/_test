/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_user_output.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 18:15:09 by dbousque          #+#    #+#             */
/*   Updated: 2017/12/09 18:15:12 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
