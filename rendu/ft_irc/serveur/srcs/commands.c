/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 17:53:14 by dbousque          #+#    #+#             */
/*   Updated: 2017/12/09 17:53:16 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"

/*
** If a NICK message arrives at a server which already knows about an
** identical nickname for another client, a nickname collision occurs.
** As a result of a nickname collision, all instances of the nickname
** are removed from the server's database, and a KILL command is issued
** to remove the nickname from all other server's database. If the NICK
** message causing the collision was a nickname change, then the
** original (old) nick must be removed as well.
*/

void	nick(t_env *e, t_user *user, char **params, int nb_params)
{
	char	*new_nick;
	int		i;

	if (nb_params != 1)
		return (wrong_nb_params(user, "nick", nb_params, 1));
	new_nick = params[0];
	if (!valid_nickname(new_nick))
		return (log_user(user, "|x Invalid nickname"));
	i = 0;
	while (i < e->nb_users)
	{
		if (!e->users[i].free && ft_streq(new_nick, e->users[i].nickname))
		{
			remove_user(e, user);
			remove_user(e, &(e->users[i]));
			log_user(&(e->users[i]), "|x Someone tried to use your nickname");
			return (log_user(user, "|x Nick already taken, disconnecting"));
		}
		i++;
	}
	ft_strcpy(user->nickname, new_nick);
	log_user(user, "|> Successfully changed your nickname");
}

/*
** 8.13 Channel membership
**
** The current server allows any registered local user to join upto 10
** different channels.  There is no limit imposed on non-local users so
** that the server remains (reasonably) consistant with all others on a
** channel membership basis
**
** To create a new channel or become part of an existing channel, a user
** is required to JOIN the channel.  If the channel doesn't exist prior
** to joining, the channel is created and the creating user becomes a
** channel operator.
*/

void	join(t_env *e, t_user *user, char **params, int nb_params)
{
	char		*description;
	t_channel	*channel;
	int			i;

	if (nb_params < 1 || nb_params > 2)
		return (wrong_nb_params(user, "join", nb_params, 1));
	description = nb_params == 2 ? params[1] : "<give me a description>";
	if (!(channel = find_channel(e, params[0])))
	{
		if (!(channel = create_channel(e, params[0], description)))
			return (log_user(user, "|x Could not create channel"));
	}
	i = 0;
	while (user->channels[i] != -1)
	{
		if (user->channels[i] == channel->id)
			return (log_user(user, "|x Already a member of the channel"));
		i++;
	}
	if (i >= 10)
		return (log_user(user, "|x Already joined 10 channels, can't join"));
	user->channels[i] = channel->id;
	user->channels[i + 1] = -1;
	log_user(user, "|> Successfully joined the channel");
	welcome_user_to_channel(user, channel);
}

void	leave(t_env *e, t_user *user, char **params, int nb_params)
{
	t_channel	*channel;

	if (user->channels[0] == -1)
		return (log_user(user, "|x You are not a member of any channel"));
	if (user->channels[1] != -1 && nb_params != 1)
		return (wrong_nb_params(user, "leave", nb_params, 1));
	if (nb_params < 0 || nb_params > 1)
		return (wrong_nb_params(user, "leave", nb_params, 1));
	if (nb_params > 0)
		channel = find_channel(e, params[0]);
	else
		channel = find_channel_by_id(e, user->channels[0]);
	if (!channel)
		return (log_user(user, "|x Channel not found"));
	if (!remove_channel_from_user(e, user, channel))
		return (log_user(user, "|x Your are not registered to this channel"));
	log_user(user, "|> Successfully left the channel");
}

void	who(t_env *e, t_user *user, char **params, int nb_params)
{
	t_channel	*channel;
	t_user		*t;
	int			i;

	if (nb_params != 1)
		return (wrong_nb_params(user, "who", nb_params, 1));
	channel = find_channel(e, params[0]);
	if (!channel)
		return (log_user(user, "|x Channel not found"));
	i = 0;
	while (i < e->nb_users)
	{
		t = &(e->users[i]);
		if (!t->free && user_in_channel(t, channel->id))
		{
			if (t->id == user->id)
			{
				snprintf(g_tmp_buffer, USER_BUFFER_SIZE, "|> %s", t->nickname);
				log_user(user, g_tmp_buffer);
			}
			else
				log_user(user, t->nickname);
		}
		i++;
	}
}

void	msg(t_env *e, t_user *user, char **params, int nb_params)
{
	int			i;
	t_user		*tmp_user;
	char		msg[600];

	if (nb_params != 2)
		return (wrong_nb_params(user, "msg", nb_params, 2));
	i = 0;
	while (i < e->nb_users)
	{
		tmp_user = &(e->users[i]);
		if (!tmp_user->free && ft_streq(tmp_user->nickname, params[0]))
		{
			snprintf(msg, 600, "'%s' > %s", user->nickname, params[1]);
			log_user(tmp_user, msg);
			snprintf(msg, 600, "'%s' < %s", tmp_user->nickname, params[1]);
			log_user(user, msg);
			return ;
		}
		i++;
	}
	log_user(user, "|x User not found");
}
