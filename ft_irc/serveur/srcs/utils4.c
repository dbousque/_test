/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 17:57:40 by dbousque          #+#    #+#             */
/*   Updated: 2017/12/09 17:57:42 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"

void		init_commands_names(void)
{
	g_irc_commands[0] = "/nick";
	g_irc_commands[1] = "/join";
	g_irc_commands[2] = "/leave";
	g_irc_commands[3] = "/who";
	g_irc_commands[4] = "/msg";
	g_irc_commands[5] = "/channels";
	g_irc_commands[6] = "/users";
	g_irc_commands[7] = "/ping";
	g_irc_commands[8] = "/mynick";
	g_irc_commands[9] = "/befriend";
	g_irc_commands[10] = "/unfriend";
	g_irc_commands[11] = "/msgchan";
	g_irc_commands[12] = "/privmode";
	g_irc_commands[13] = "/stdmode";
	g_irc_commands[14] = "/privuser";
	g_irc_commands[15] = NULL;
}

t_channel	*find_channel(t_env *e, char *channel_name)
{
	int			i;
	t_channel	*channel;

	i = 0;
	while (i < e->channels.len)
	{
		channel = &(((t_channel*)e->channels.elts)[i]);
		if (ft_streq(channel->name, channel_name))
			return (channel);
		i++;
	}
	return (NULL);
}

int			unique_channel_id(t_list *channels)
{
	int			i;
	int			id;
	t_channel	*channel;

	id = -1;
	while (1)
	{
		id = rand();
		if (id < 1)
			continue ;
		i = 0;
		while (i < channels->len)
		{
			channel = &(((t_channel*)channels->elts)[i]);
			if (channel->id == id)
			{
				id = -1;
				break ;
			}
			i++;
		}
		if (id != -1)
			break ;
	}
	return (id);
}

t_channel	*create_channel(t_env *e, char *channel_name, char *description)
{
	t_channel	*channel;
	int			i;

	if (!valid_channel_name(channel_name) || ft_strlen(description) >= 300)
		return (NULL);
	channel = new_elt(&(e->channels));
	if (!channel)
		return (NULL);
	channel->id = unique_channel_id(&(e->channels));
	i = 0;
	while (channel_name[i])
	{
		channel->name[i] = channel_name[i];
		i++;
	}
	channel->name[i] = '\0';
	i = 0;
	while (description[i])
	{
		channel->description[i] = description[i];
		i++;
	}
	channel->description[i] = '\0';
	return (channel);
}

char		remove_user_from_friends2(t_user *user, t_user *friend)
{
	int		i;
	int		decal;

	i = 0;
	decal = 0;
	while (user->friends[i] != -1)
	{
		if (user->friends[i] == friend->id)
			decal = 1;
		if (i - decal >= 0)
			user->friends[i - decal] = user->friends[i];
		i++;
	}
	user->friends[i - decal] = -1;
	if (decal == 0)
		return (0);
	return (1);
}
