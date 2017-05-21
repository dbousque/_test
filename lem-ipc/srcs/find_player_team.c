

#include "lem_ipc.h"

char	find_player(unsigned int player_id, t_player **player)
{
	unsigned int	i;
	unsigned int	y;
	t_team_data		*team;

	i = 0;
	while (i < g_game_data->team_data_len)
	{
		team = &(g_game_data->team_data_elts[i]);
		y = 0;
		while (y < team->players_len)
		{
			if (team->players_elts[y].player_id == player_id)
			{
				*player = &(team->players_elts[y]);
				return (1);
			}
			y++;
		}
		i++;
	}
	return (0);
}

char	find_team(unsigned int team_id, t_team_data **team)
{
	unsigned int	i;

	i = 0;
	while (i < g_game_data->team_data_len)
	{
		*team = &(g_game_data->team_data_elts[i]);
		if ((*team)->team_id == team_id)
			return (1);
		i++;
	}
	printf("could not find team %u\n", team_id);
	return (0);
}

char	get_player_and_team(unsigned int team_id, unsigned int player_id,
										t_team_data **team, t_player **player)
{
	unsigned int	i;

	i = 0;
	while (i < g_game_data->team_data_len)
	{
		if (g_game_data->team_data_elts[i].team_id == team_id)
		{
			*team = &(g_game_data->team_data_elts[i]);
			i = 0;
			while (i < (*team)->players_len)
			{
				if ((*team)->players_elts[i].player_id == player_id)
				{
					*player = &((*team)->players_elts[i]);
					return (1);
				}
				i++;
			}
			printf("could not find player %u\n", player_id);
			return (0);
		}
		i++;
	}
	printf("could not find team %u\n", team_id);
	return (0);
}