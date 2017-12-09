/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 17:57:25 by dbousque          #+#    #+#             */
/*   Updated: 2017/12/09 17:57:27 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"

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
		{
			close(users[i + decal].fd);
			decal++;
		}
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

void	remove_user(t_env *e, t_user *user)
{
	int		i;

	i = 0;
	while (i < e->nb_users)
	{
		if (!e->users[i].free)
		{
			if (e->users[i].mode == PRIV_MSG
				&& e->users[i].priv_msg_user == user->id)
			{
				e->users[i].mode = STD;
				e->users[i].priv_msg_user = -1;
			}
			remove_user_from_friends(e->users[i].friends, user->id);
		}
		i++;
	}
	remove_channels_from_user(e, user);
	user->free = 1;
	user->id = -1;
	user->nickname[0] = '\0';
}

void	remove_user_ind(t_env *e, int i)
{
	t_user	*user;

	user = &(e->users[i]);
	remove_user(e, user);
}
