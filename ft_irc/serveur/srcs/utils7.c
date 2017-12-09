/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 18:10:39 by dbousque          #+#    #+#             */
/*   Updated: 2017/12/09 18:10:42 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"

void	ft_strcpy(char *dest, char *src)
{
	int		i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

t_user	*find_user_by_id(t_env *e, int id)
{
	t_user	*tmp_user;
	int		i;

	i = 0;
	while (i < e->nb_users)
	{
		tmp_user = &(e->users[i]);
		if (!tmp_user->free && tmp_user->id == id)
			return (tmp_user);
		i++;
	}
	return (NULL);
}
