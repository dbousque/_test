

#include "ft_irc.h"

void		init_commands_names(void)
{
	g_irc_commands[0] = "/nick";
	g_irc_commands[1] = "/join";
	g_irc_commands[2] = "/leave";
	g_irc_commands[3] = "/who";
	g_irc_commands[4] = "/msg";
	g_irc_commands[5] = NULL;
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

t_channel	*create_channel(t_env *e, char *channel_name, char *description)
{
	t_channel	*channel;
	int			i;

	if (!valid_channel_name(channel_name) || ft_strlen(description) >= 300)
		return (NULL);
	channel = new_elt(&(e->channels));
	if (!channel)
		return (NULL);
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

void	remove_channel_if_empty(t_env *e, t_channel *channel)
{
	int		i;
	int		x;
	t_user	*user;
	char	mentioned;

	mentioned = 0;
	i = 0;
	while (i < e->nb_users)
	{
		user = &(e->users[i]);
		if (!user->free)
		{
			x = 0;
			while (user->channels[x] != -1)
			{
				if (user->channels[x] == channel->id)
				{
					mentioned = 1;
					break ;
				}
				x++;
			}
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

char	remove_channel_from_user(t_env *e, t_user *user, t_channel *channel)
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

void	remove_channels_from_user(t_env *e, t_user *user)
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

char	user_in_channel(t_user *user, int channel_id)
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
