

#include "ft_irc.h"

/*
 * If a NICK message arrives at a server which already knows about an
 * identical nickname for another client, a nickname collision occurs.
 * As a result of a nickname collision, all instances of the nickname
 * are removed from the server's database, and a KILL command is issued
 * to remove the nickname from all other server's database. If the NICK
 * message causing the collision was a nickname change, then the
 * original (old) nick must be removed as well.
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
	i = 0;
	while (new_nick[i])
	{
		user->nickname[i] = new_nick[i];
		i++;
	}
	user->nickname[i] = '\0';
	log_user(user, "|> Successfully changed your nickname");
}

/*
 * 8.13 Channel membership
 *
 * The current server allows any registered local user to join upto 10
 * different channels.  There is no limit imposed on non-local users so
 * that the server remains (reasonably) consistant with all others on a
 * channel membership basis
 *
 * To create a new channel or become part of an existing channel, a user
 * is required to JOIN the channel.  If the channel doesn't exist prior
 * to joining, the channel is created and the creating user becomes a
 * channel operator.
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
	t_user		*tmp_user;
	int			i;

	if (nb_params != 1)
		return (wrong_nb_params(user, "who", nb_params, 1));
	channel = find_channel(e, params[0]);
	if (!channel)
		return (log_user(user, "|x Channel not found"));
	i = 0;
	while (i < e->nb_users)
	{
		tmp_user = &(e->users[i]);
		if (!tmp_user->free && user_in_channel(tmp_user, channel->id))
		{
			if (tmp_user->id == user->id)
			{
				snprintf(g_tmp_buffer, USER_BUFFER_SIZE,
												"|> %s", tmp_user->nickname);
				log_user(user, g_tmp_buffer);
			}
			else
				log_user(user, tmp_user->nickname);
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

void	channels(t_env *e, t_user *user, char **params, int nb_params)
{
	int			i;
	t_channel	*channel;

	(void)params;
	if (nb_params != 0)
		return (wrong_nb_params(user, "channels", nb_params, 0));
	i = 0;
	while (i < e->channels.len)
	{
		channel = &(((t_channel*)e->channels.elts)[i]);
		log_user(user, channel->name);
		i++;
	}
}

void	users(t_env *e, t_user *user, char **params, int nb_params)
{
	int			i;
	t_user		*tmp_user;
	char		tmp[30];

	(void)params;
	if (nb_params != 0)
		return (wrong_nb_params(user, "users", nb_params, 0));
	log_user(user, "[USERS]");
	i = 0;
	while (i < e->nb_users)
	{
		tmp_user = &(e->users[i]);
		if (!tmp_user->free)
		{
			if (tmp_user->id == user->id)
				snprintf(tmp, 30, "[USER] |x %s", tmp_user->nickname);
			else if (befriends(user, tmp_user))
				snprintf(tmp, 30, "[USER] |> %s", tmp_user->nickname);
			else
				snprintf(tmp, 30, "[USER] %s", tmp_user->nickname);
			log_user(user, tmp);
		}
		i++;
	}
}

void	ping(t_env *e, t_user *user, char **params, int nb_params)
{
	(void)e;
	(void)params;
	if (nb_params != 0)
		return (wrong_nb_params(user, "ping", nb_params, 0));
	log_user(user, "[PONG]");
}

void	mynick(t_env *e, t_user *user, char **params, int nb_params)
{
	char		tmp[30];

	(void)e;
	(void)params;
	if (nb_params != 0)
		return (wrong_nb_params(user, "mynick", nb_params, 0));
	snprintf(tmp, 30, "[NICK] |x %s", user->nickname);
	log_user(user, tmp);
}

void	befriend(t_env *e, t_user *user, char **params, int nb_params)
{
	int		i;
	t_user	*tmp_user;

	if (nb_params != 1)
		return (wrong_nb_params(user, "befriend", nb_params, 1));
	tmp_user = find_user_by_nick(e, params[0]);
	if (!tmp_user)
		return (log_user(user, "|x User not found"));
	i = 0;
	while (user->friends[i] != -1)
	{
		if (user->friends[i] == tmp_user->id)
			return (log_user(user, "|x Already friends"));
		i++;
	}
	if (i >= 10)
		return (log_user(user, "|x Too many friends"));
	user->friends[i] = tmp_user->id;
	user->friends[i + 1] = -1;
	log_user(user, "|> Successfully befriended");
}

void	unfriend(t_env *e, t_user *user, char **params, int nb_params)
{
	int		i;
	t_user	*tmp_user;

	if (nb_params != 1)
		return (wrong_nb_params(user, "unfriend", nb_params, 1));
	i = 0;
	while (i < e->nb_users)
	{
		tmp_user = &(e->users[i]);
		if (!tmp_user->free && ft_streq(tmp_user->nickname, params[0]))
			break ;
		tmp_user = NULL;
		i++;
	}
	if (!tmp_user)
		return (log_user(user, "|x User not found"));
	if (!remove_user_from_friends2(user, tmp_user))
		return (log_user(user, "|x Not befriended"));
	log_user(user, "|> Successfully unfriended");
}

void	msgchan(t_env *e, t_user *user, char **params, int nb_params)
{
	int			i;
	t_channel	*channel;
	t_user		*tmp_user;
	char		msg[600];

	if (nb_params != 2)
		return (wrong_nb_params(user, "msgchan", nb_params, 2));
	channel = find_channel(e, params[0]);
	if (!channel)
		return (log_user(user, "|x Channel not found"));
	i = 0;
	snprintf(msg, 600, "'%s' in %s > %s", user->nickname,
													channel->name, params[1]);
	while (i < e->nb_users)
	{
		tmp_user = &(e->users[i]);
		if (!tmp_user->free && user_in_channel(tmp_user, channel->id)
			&& tmp_user->id != user->id)
			log_user(tmp_user, msg);
		i++;
	}
	snprintf(msg, 600, "'%s' in %s < %s", user->nickname,
													channel->name, params[1]);
	log_user(user, msg);
}

void	privmode(t_env *e, t_user *user, char **params, int nb_params)
{
	int			i;
	t_user		*tmp_user;

	if (nb_params != 1)
		return (wrong_nb_params(user, "privmode", nb_params, 1));
	i = 0;
	while (i < e->nb_users)
	{
		tmp_user = &(e->users[i]);
		if (!tmp_user->free && ft_streq(tmp_user->nickname, params[0]))
			break ;
		tmp_user = NULL;
		i++;
	}
	if (!tmp_user)
		return (log_user(user, "|x User not found"));
	user->mode = PRIV_MSG;
	user->priv_msg_user = tmp_user->id;
	log_user(user, "|> Successfully entered private messaging mode");
}

void	stdmode(t_env *e, t_user *user, char **params, int nb_params)
{
	(void)e;
	(void)params;
	if (nb_params != 0)
		return (wrong_nb_params(user, "stdmode", nb_params, 0));
	user->mode = STD;
	user->priv_msg_user = 0;
	log_user(user, "|> Successfully entered standard mode");
}

void	privuser(t_env *e, t_user *user, char **params, int nb_params)
{
	int			i;
	t_user		*tmp_user;
	char		msg[50];

	(void)params;
	if (nb_params != 0)
		return (wrong_nb_params(user, "privuser", nb_params, 0));
	if (user->mode != PRIV_MSG)
		return (log_user(user, "[NOPRIVUSER]"));
	i = 0;
	while (i < e->nb_users)
	{
		tmp_user = &(e->users[i]);
		if (!tmp_user->free && tmp_user->id == user->priv_msg_user)
			break ;
		tmp_user = NULL;
		i++;
	}
	if (!tmp_user)
	{
		user->mode = STD;
		user->priv_msg_user = 0;
		return (log_user(user, "|x Unexpected error"));
	}
	snprintf(msg, 50, "[PRIVUSER] %s", tmp_user->nickname);
	log_user(user, msg);
}
