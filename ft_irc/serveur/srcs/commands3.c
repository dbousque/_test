/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 17:59:46 by dbousque          #+#    #+#             */
/*   Updated: 2017/12/09 17:59:47 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"

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
	t_user		*tmp_user;
	char		msg[50];

	(void)params;
	if (nb_params != 0)
		return (wrong_nb_params(user, "privuser", nb_params, 0));
	if (user->mode != PRIV_MSG)
		return (log_user(user, "[NOPRIVUSER]"));
	tmp_user = find_user_by_id(e, user->priv_msg_user);
	if (!tmp_user)
	{
		user->mode = STD;
		user->priv_msg_user = 0;
		return (log_user(user, "|x Unexpected error"));
	}
	snprintf(msg, 50, "[PRIVUSER] %s", tmp_user->nickname);
	log_user(user, msg);
}
