

#include "ft_irc.h"

void	init_commands_names(void)
{
	g_irc_commands[0] = "/nick";
	g_irc_commands[1] = "/join";
	g_irc_commands[2] = "/leave";
	g_irc_commands[3] = "/who";
	g_irc_commands[4] = "/msg";
	g_irc_commands[5] = "/connect";
	g_irc_commands[6] = NULL;
}

void	init_users(t_user *users)
{
	int		i;

	i = 0;
	while (i < MAX_NB_CONNECTIONS)
	{
		users[i].free = 1;
		i++;
	}
}

void	clear_removed_users(t_user *users, int *nb_users)
{
	int		i;
	int		decal;

	decal = 0;
	i = 0;
	while (i + decal < *nb_users)
	{
		while (users[i + decal].free && i + decal < *nb_users)
			decal++;
		if (decal > 0 && i + decal < *nb_users)
			users[i] = users[i + decal];
		i++;
	}
	*nb_users -= decal;
}

void	remove_user_from_friends(int *friends, int id)
{
	int		i;
	int		decal;

	decal = 0;
	i = 0;
	while (friends[i + decal] != -1)
	{
		while (friends[i + decal] == id)
			decal++;
		if (decal > 0)
			friends[i] = friends[i + decal];
		i++;
	}
	friends[i] = -1;
}

void	remove_user(t_user *users, int i, int nb_users)
{
	t_user	*user;

	user = &(users[i]);
	close(user->fd);
	i = 0;
	while (i < nb_users)
	{
		if (!users[i].free)
		{
			if (users[i].mode == PRIV_MSG && users[i].priv_msg_user == user->id)
			{
				users[i].mode = STD;
				users[i].priv_msg_user = -1;
			}
			remove_user_from_friends(users[i].friends, user->id);
		}
		i++;
	}
	user->free = 1;
	user->id = -1;
	user->nickname[0] = '\0';
}
