/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ressources.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 18:11:10 by dbousque          #+#    #+#             */
/*   Updated: 2017/05/19 18:11:13 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_ipc.h"

void	init_game_data(t_params *params)
{
	g_game_data->board_size = params->board_size;
	g_game_data->nb_moves = 0;
	g_game_data->nb_alive_players = 0;
	g_game_data->player_counter = 0;
	g_game_data->team_data_len = 0;
	g_game_data->team_data_size = 4;
}

char	get_ressources(t_shared *shared)
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
	return (update_ressources(shared));
}

char	init_ressources2(t_params *params, t_shared *shared, char error,
																char creation)
{
	init_shared(shared, MUTEX_NAME);
	if (!(lock_ressources(shared)))
	{
		printf("could not lock ressources\n");
		return (0);
	}
	creation = 0;
	if (!(add_shared_ressource(shared, GAME_DATA_KEY, sizeof(t_game_data),
																&creation)))
	{
		printf("could not add game_data\n");
		return (0);
	}
	error = 0;
	g_game_data = (t_game_data*)get_shared_ressource(shared, GAME_DATA_KEY,
																	&error);
	if (error)
	{
		printf("could not get game_data\n");
		return (0);
	}
	printf("board_size : %u\n", g_game_data->board_size);
	if (creation)
		init_game_data(params);
	printf("board_size : %u\n", g_game_data->board_size);
	unlock_ressources(shared);
	return (get_ressources(shared));
}

char	init_ressources(t_params *params, t_shared *shared)
{
	return (init_ressources2(params, shared, 0, 0));
}
