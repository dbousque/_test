

#include "lem_ipc.h"

void	find_opponent(t_team_data *team, t_player *player,
										unsigned int *attack_target, char *set)
{
	unsigned int	i;
	unsigned int	y;
	t_team_data		*tmp_team;

	(void)player;
	i = 0;
	while (i < g_game_data->team_data_len)
	{
		tmp_team = &(g_game_data->team_data_elts[i]);
		if (tmp_team->team_id != team->team_id)
		{
			y = 0;
			while (y < tmp_team->players_len)
			{
				*attack_target = tmp_team->players_elts[y].player_id;
				*set = 1;
				return ;
				y++;
			}
		}
		i++;
	}
	*set = 0;
}

void	make_attack_strategy(t_team_data *team, t_player *player,
										unsigned int *attack_target, char *set)
{
	unsigned int	i;
	t_lemipc_msg	msg;

	find_opponent(team, player, attack_target, set);
	if (*set)
	{
		msg.attack_target = *attack_target;
		i = 0;
		while (i < team->players_len)
		{
			if (team->players_elts[i].player_id != player->player_id)
				send_message(&(team->players_elts[i]), &msg);
			i++;
		}
	}
}