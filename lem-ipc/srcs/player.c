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

t_team_data		*make_team(t_shared *shared, unsigned int team_id, char *error)
{
	t_team_data		*team;

	if (g_game_data->team_data_len >= g_game_data->team_data_size)
		double_teams_size(shared, error);
	if (*error)
		return (NULL);
	team = &(g_game_data->team_data_elts[g_game_data->team_data_len]);
	team->team_id = team_id;
	team->nb_killed_others = 0;
	team->nb_killed_self = 0;
	team->players_len = 0;
	team->players_size = 4;
	if (!(make_team_players(shared, team)))
	{
		*error = 1;
		return (NULL);
	}
	g_game_data->team_data_len++;
	return (team);
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
	return (make_team(shared, team_id, error));
}

char			set_random_location_for_player(t_player *player)
{
	unsigned int	i;
	unsigned int	nb_free;
	unsigned int	n;

	nb_free = 0;
	i = 0;
	while (i < g_game_data->board_size * g_game_data->board_size)
	{
		if (g_game_data->board[i] == FREE_BOARD_TILE)
			nb_free++;
		i++;
	}
	if (nb_free == 0)
	{
		printf("no available tile in board, cannot place player\n");
		return (0);
	}
	n = rand() % nb_free;
	return (set_location_for_player(player, n));
}

char			add_player_to_team(t_shared *shared, t_params *params,
									t_team_data *team, unsigned int *player_id)
{
	char		error;
	t_player	*player;

	(void)params;
	error = 0;
	if (team->players_len >= team->players_size)
		double_players_size(shared, team, &error);
	if (error)
		return (0);
	*player_id = g_game_data->player_counter;
	player = &(team->players_elts[team->players_len]);
	player->player_id = g_game_data->player_counter;
	player->team_id = team->team_id;
	player->is_team_leader = (team->players_len == 0 ? 1 : 0);
	if (!(set_random_location_for_player(player)))
		return (0);
	team->players_len++;
	g_game_data->player_counter++;
	g_game_data->nb_alive_players++;
	return (1);
}

char			add_player(t_shared *shared, t_params *params,
													unsigned int *player_id)
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
	{
		unlock_ressources(shared);
		return (0);
	}
	if (!(add_player_to_team(shared, params, team, player_id)))
	{
		unlock_ressources(shared);
		return (0);
	}
	unlock_ressources(shared);
	return (1);
}
