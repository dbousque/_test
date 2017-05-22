

#include "lem_ipc.h"

char	make_team_players(t_shared *shared, t_team_data *team)
{
	char	error;
	char	creation;
	size_t	size;

	size = sizeof(t_player) * 4;
	creation = 0;
	if (!(add_shared_ressource(shared, team->team_id, size, &creation)))
	{
		printf("could not add team %u\n", team->team_id);
		return (0);
	}
	if (!creation)
	{
		printf("team players already existed %u\n", team->team_id);
		return (0);
	}
	error = 0;
	team->players_elts = (t_player*)get_shared_ressource(shared,
														team->team_id, &error);
	if (error)
	{
		printf("could not get team %u\n", team->team_id);
		return (0);
	}
	return (1);
}

void	make_new_players_size(t_shared *shared, t_team_data *team, char *error)
{
	char	creation;
	size_t	size;

	if (!(remove_shared_ressource(shared, team->team_id, team->players_elts)))
	{
		printf("could not remove players on team %u\n", team->team_id);
		*error = 1;
		return ;
	}
	size = sizeof(t_player) * (team->players_size * 2);
	creation = 0;
	if (!(add_shared_ressource(shared, team->team_id, size, &creation)))
	{
		printf("could not add players for team %u\n", team->team_id);
		*error = 1;
		return ;
	}
	if (creation)
	{
		printf("players for team %u did not already exist\n", team->team_id);
		*error = 1;
		return ;
	}
	team->players_elts = (t_player*)get_shared_ressource(shared,
														team->team_id, error);
	if (*error)
	{
		printf("could not get players for team %u\n", team->team_id);
		return ;
	}
}

void	double_players_size(t_shared *shared, t_team_data *team, char *error)
{
	t_player	*existing_players;
	size_t		i;

	if (!(existing_players = (t_player*)malloc(
						sizeof(t_player) * team->players_len)))
	{
		*error = 1;
		return ;
	}
	i = 0;
	while (i < team->players_len)
	{
		existing_players[i] = team->players_elts[i];
		i++;
	}
	make_new_players_size(shared, team, error);
	if (*error)
		return ;
	i = 0;
	while (i < team->players_len)
	{
		team->players_elts[i] = existing_players[i];
		i++;
	}
	team->players_size = team->players_size * 2;
	free(existing_players);
}

void	make_new_teams_size(t_shared *shared, char *error)
{
	char	creation;
	size_t	size;

	if (!(remove_shared_ressource(shared, TEAM_DATA_KEY,
												g_game_data->team_data_elts)))
	{
		printf("could not remove teams_elts\n");
		*error = 1;
		return ;
	}
	size = sizeof(t_team_data) * (g_game_data->team_data_size * 2);
	creation = 0;
	if (!(add_shared_ressource(shared, TEAM_DATA_KEY, size, &creation)))
	{
		printf("could not add team_data\n");
		*error = 1;
		return ;
	}
	g_game_data->team_data_elts = (t_team_data*)get_shared_ressource(shared,
														TEAM_DATA_KEY, error);
	if (*error)
	{
		printf("could not get team_data\n");
		return ;
	}
}

void	double_teams_size(t_shared *shared, char *error)
{
	t_team_data		*existing_teams;
	size_t			i;

	if (!(existing_teams = (t_team_data*)malloc(
						sizeof(t_team_data) * g_game_data->team_data_len)))
	{
		*error = 1;
		return ;
	}
	i = 0;
	while (i < g_game_data->team_data_len)
	{
		existing_teams[i] = g_game_data->team_data_elts[i];
		i++;
	}
	make_new_teams_size(shared, error);
	if (*error)
		return ;
	i = 0;
	while (i < g_game_data->team_data_len)
	{
		g_game_data->team_data_elts[i] = existing_teams[i];
		i++;
	}
	g_game_data->team_data_size = g_game_data->team_data_size * 2;
	free(existing_teams);
}