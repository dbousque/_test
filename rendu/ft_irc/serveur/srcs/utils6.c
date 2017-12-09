/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 17:57:51 by dbousque          #+#    #+#             */
/*   Updated: 2017/12/09 17:57:52 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"

char		user_in_channel(t_user *user, int channel_id)
{
	int		i;

	i = 0;
	while (user->channels[i] != -1)
	{
		if (user->channels[i] == channel_id)
			return (1);
		i++;
	}
	return (0);
}

void		remove_channel_if_empty(t_env *e, t_channel *channel)
{
	int		i;
	t_user	*user;
	char	mentioned;

	mentioned = 0;
	i = 0;
	while (i < e->nb_users)
	{
		user = &(e->users[i]);
		if (!user->free)
		{
			mentioned = user_in_channel(user, channel->id);
			if (mentioned)
				break ;
		}
		i++;
	}
	if (!mentioned)
	{
		LOG(DEBUG, "No user left in channel '%s', removing it", channel->name);
		remove_elt(&(e->channels), (char*)channel);
	}
}

char		remove_channel_from_user(t_env *e, t_user *user,
															t_channel *channel)
{
	int		i;
	int		decal;

	i = 0;
	decal = 0;
	while (user->channels[i] != -1)
	{
		if (user->channels[i] == channel->id)
			decal = 1;
		if (i - decal >= 0)
			user->channels[i - decal] = user->channels[i];
		i++;
	}
	user->channels[i - decal] = -1;
	if (decal == 0)
		return (0);
	remove_channel_if_empty(e, channel);
	return (1);
}

t_channel	*find_channel_by_id(t_env *e, int id)
{
	int			i;
	t_channel	*channel;

	i = 0;
	while (i < e->channels.len)
	{
		channel = &(((t_channel*)e->channels.elts)[i]);
		if (channel->id == id)
			return (channel);
		i++;
	}
	return (NULL);
}

void		remove_channels_from_user(t_env *e, t_user *user)
{
	int			i;
	t_channel	*channel;

	i = 0;
	while (user->channels[i] != -1)
	{
		channel = find_channel_by_id(e, user->channels[i]);
		if (!channel)
		{
			LOG(ERROR, "Channel with id '%d' not found !", user->channels[i]);
			i++;
			continue ;
		}
		remove_channel_from_user(e, user, channel);
		i++;
	}
}
