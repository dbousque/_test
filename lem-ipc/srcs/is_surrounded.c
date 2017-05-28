

#include "lem_ipc.h"

void	add_to_teams(unsigned int teams[], unsigned int nb_by_team[],
											int *team_ind, unsigned int val)
{
	int		i;

	i = 0;
	while (i < *team_ind)
	{
		if (teams[i] == val)
		{
			(nb_by_team[i])++;
			return ;
		}
		i++;
	}
	teams[*team_ind] = val;
	nb_by_team[*team_ind] = 1;
	(*team_ind)++;
}


#include <sys/time.h>

void	try_to_add_to_teams(int y, int x,
										unsigned int teams[], int *team_ind)
{
	unsigned int	val;

	if (y >= 0 && y < (int)g_game_data->board_size
		&& x >= 0 && x < (int)g_game_data->board_size)
	{
		//printf("inside if try : %d %d %p\n", y, x, g_game_data->board);
		//struct timeval my_time;
		//gettimeofday(&my_time, NULL);
		//printf("%d\n", my_time.tv_usec);
		//fflush(stdout);
		val = BOARD_GET(y, x);
		//printf("got val\n");
		//fflush(stdout);
		if (val != FREE_BOARD_TILE)
		{
			//printf("adding to teams\n");
			//fflush(stdout);
			add_to_teams(teams, teams + 8, team_ind, val);
		}
	}
}

char	is_surrounded(t_player *player, unsigned int *ennemy_id)
{
	unsigned int	teams[16];
	int				team_ind;
	int				i;

	//printf("inside if surrounded\n");
	//fflush(stdout);
	team_ind = 0;
	try_to_add_to_teams((int)player->y - 1, (int)player->x - 1, teams,
																	&team_ind);
	//printf("try1\n");
	//fflush(stdout);
	try_to_add_to_teams((int)player->y - 1, player->x, teams, &team_ind);
	//printf("try2\n");
	//fflush(stdout);
	try_to_add_to_teams((int)player->y - 1, player->x + 1, teams, &team_ind);
	try_to_add_to_teams(player->y, (int)player->x - 1, teams, &team_ind);
	try_to_add_to_teams(player->y, player->x + 1, teams, &team_ind);
	try_to_add_to_teams(player->y + 1, (int)player->x - 1, teams, &team_ind);
	try_to_add_to_teams(player->y + 1, player->x, teams, &team_ind);
	try_to_add_to_teams(player->y + 1, player->x + 1, teams, &team_ind);
	//printf("last try\n");
	//fflush(stdout);
	i = 8;
	while (i < 16)
	{
		//printf("loop\n");
		//fflush(stdout);
		if (i >= team_ind)
			break ;
		if (teams[i] >= 2 && teams[i - 8] != player->team_id)
		{
			//printf("got it !\n");
			//fflush(stdout);
			*ennemy_id = teams[i - 8];
			return (1);
		}
		i++;
	}
	//printf("exiting\n");
	//fflush(stdout);
	return (0);
}