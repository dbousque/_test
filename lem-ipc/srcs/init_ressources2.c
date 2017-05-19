/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ressources2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 18:19:14 by dbousque          #+#    #+#             */
/*   Updated: 2017/05/19 18:19:16 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_ipc.h"

char	get_team_ressource(t_shared *shared, size_t i)
{
	char			error;
	char			creation;
	size_t			size;
	t_team_data		*team;

	team = &(g_game_data->team_data_elts[i]);
	size = sizeof(t_player) * team->players_size;
	creation = 0;
	if (!(add_shared_ressource(shared, team->team_id, size, &creation)))
	{
		printf("could not add team_data_elts\n");
		return (0);
	}
	error = 0;
	team->players_elts = (t_player*)get_shared_ressource(shared,
														team->team_id, &error);
	if (error)
	{
		printf("could not get team_data_elts\n");
		return (0);
	}
	return (1);
}

char	update_ressources2(t_shared *shared, char error, char creation)
{
	size_t	size;
	size_t	i;

	size = sizeof(t_team_data) * g_game_data->team_data_size;
	if (!(add_shared_ressource(shared, TEAM_DATA_KEY, size, &creation)))
	{
		printf("could not add team_data_elts\n");
		return (0);
	}
	g_game_data->team_data_elts = (t_team_data*)get_shared_ressource(shared,
														TEAM_DATA_KEY, &error);
	if (error)
	{
		printf("could not get team_data_elts\n");
		return (0);
	}
	i = 0;
	while (i < g_game_data->team_data_len)
	{
		if (!(get_team_ressource(shared, i)))
			return (0);
		i++;
	}
	return (1);
}

char	update_ressources(t_shared *shared)
{
	return (update_ressources2(shared, 0, 0));
}
