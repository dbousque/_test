/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 17:59:41 by dbousque          #+#    #+#             */
/*   Updated: 2017/12/09 17:59:43 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"

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
