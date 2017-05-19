/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 18:46:22 by dbousque          #+#    #+#             */
/*   Updated: 2017/05/19 18:46:23 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_ipc.h"

char			get_team_players()
{
	char	error;
	char	creation;
	size_t	size;

	size = sizeof(unsigned int) * g_game_data->board_size *
													g_game_data->board_size;
	creation = 0;
	if (!(add_shared_ressource(shared, BOARD_KEY, size, &creation)))
	{
		printf("could not add board\n");
		return (0);
	}
	error = 0;
	g_game_data->board = (unsigned int*)get_shared_ressource(shared,
														BOARD_KEY, &error);
	if (error)
	{
		printf("could not get board\n");
		return (0);
	}
}

t_team_data		*make_team(t_shared *shared, unsigned int team_id, char *error)
{
	t_team_data		*team;

	if (g_game_data->team_data_len < g_game_data->team_data_size)
		team = &(g_game_data->team_data_elts[g_game_data->team_data_len]);
	else
	{

	}
	team->team_id = team_id;
	team->nb_killed_others = 0;
	team->nb_killed_self = 0;
	team->players_len = 0;
	team->players_size = 4;
	if (!(get_team_players()))
	{
		*error = 1;
		return (NULL);
	}
	g_game_data->team_data_len++;
}

t_team_data		*find_or_make_team(t_shared *shared, unsigned int team_id,
																char *error)
{
	size_t			i;
	t_team_data		*team;

	i = 0;
	while (i < g_game_data->team_data_len)
	{
		team = &(g_game_data->team_data_elts[i]);
		if (team->team_id == team_id)
			return (team);
		i++;
	}
	return (make_team(team_id, error));
}

char	add_player(t_shared *shared, t_params *params)
{
	t_team_data		*team;
	char			error;

	if (!(lock_ressources(shared)))
	{
		printf("could not lock ressources\n");
		return (0);
	}
	update_ressources(shared);
	error = 0;
	team = find_or_make_team(shared, params->team_id, &error);
	if (error)
		return (0);
	unlock_ressources(shared);
}
