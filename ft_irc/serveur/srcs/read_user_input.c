/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_user_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 17:57:09 by dbousque          #+#    #+#             */
/*   Updated: 2017/12/09 17:57:11 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"

void	dispatch_command2(t_env *e, t_user *user, t_msg *parsed_msg,
																int nb_params)
{
	if (parsed_msg->command == MYNICK)
		return (mynick(e, user, parsed_msg->params, nb_params));
	if (parsed_msg->command == BEFRIEND)
		return (befriend(e, user, parsed_msg->params, nb_params));
	if (parsed_msg->command == UNFRIEND)
		return (unfriend(e, user, parsed_msg->params, nb_params));
	if (parsed_msg->command == MSGCHAN)
		return (msgchan(e, user, parsed_msg->params, nb_params));
	if (parsed_msg->command == PRIVMODE)
		return (privmode(e, user, parsed_msg->params, nb_params));
	if (parsed_msg->command == STDMODE)
		return (stdmode(e, user, parsed_msg->params, nb_params));
	if (parsed_msg->command == PRIVUSER)
		return (privuser(e, user, parsed_msg->params, nb_params));
	LOG(ERROR, "Unimplemented command");
}

void	dispatch_command(t_env *e, t_user *user, t_msg *parsed_msg,
																int nb_params)
{
	if (parsed_msg->command == NICK)
		return (nick(e, user, parsed_msg->params, nb_params));
	if (parsed_msg->command == JOIN)
		return (join(e, user, parsed_msg->params, nb_params));
	if (parsed_msg->command == LEAVE)
		return (leave(e, user, parsed_msg->params, nb_params));
	if (parsed_msg->command == WHO)
		return (who(e, user, parsed_msg->params, nb_params));
	if (parsed_msg->command == MSG)
		return (msg(e, user, parsed_msg->params, nb_params));
	if (parsed_msg->command == CHANNELS)
		return (channels(e, user, parsed_msg->params, nb_params));
	if (parsed_msg->command == USERS)
		return (users(e, user, parsed_msg->params, nb_params));
	if (parsed_msg->command == PING)
		return (ping(e, user, parsed_msg->params, nb_params));
	dispatch_command2(e, user, parsed_msg, nb_params);
}

void	interpret_message(t_env *e, t_user *user, int len)
{
	t_parse_message_res		res;
	t_msg					parsed_msg;
	int						nb_params;
	struct timeval			start;
	struct timeval			end;

	gettimeofday(&start, NULL);
	init_msg(&parsed_msg);
	res = parse_message(g_tmp_buffer, len, &parsed_msg);
	if (res != OK)
		return (print_parse_message_error(res, user));
	print_msg(&parsed_msg);
	nb_params = 0;
	while (parsed_msg.params[nb_params])
		nb_params++;
	if (nb_params > 0 && parsed_msg.params[nb_params - 1][0] == '\0')
		nb_params--;
	dispatch_command(e, user, &parsed_msg, nb_params);
	gettimeofday(&end, NULL);
	LOG(INFO, "Command handled in %.2f ms",
		(end.tv_sec * 1000.0 + end.tv_usec / 1000.0) -
		(start.tv_sec * 1000.0 + start.tv_usec / 1000.0));
}

void	read_user_input_error(t_env *e, int ret, t_user *user)
{
	if (ret != 0)
		LOG(ERROR, "Error while reading '%s' input", user->nickname);
	LOG(INFO, "User '%s' exiting", user->nickname);
	remove_user(e, user);
}

void	read_user_input(t_env *e, int i)
{
	t_user	*user;
	int		ret;

	user = &((e->users)[i]);
	ret = read(user->fd, g_tmp_buffer, 512);
	if (ret <= 0)
		return (read_user_input_error(e, ret, user));
	circular_buffer_write(&(user->read_buffer), g_tmp_buffer, ret);
	ret = circular_buffer_cpy(&(user->read_buffer), g_tmp_buffer);
	g_tmp_buffer[ret] = '\0';
	if (ret >= 2 && g_tmp_buffer[ret - 2] == '\r'
		&& g_tmp_buffer[ret - 1] == '\n')
	{
		user->read_buffer.start = 0;
		user->read_buffer.end = 0;
		g_tmp_buffer[ret - 2] = '\0';
		LOG(INFO, "-> ('%s') %s", user->nickname, g_tmp_buffer);
		g_tmp_buffer[ret - 2] = '\r';
		interpret_message(e, user, ret);
	}
	else
		LOG(INFO, "-> ('%s') (unfinished) %s", user->nickname, g_tmp_buffer);
}
