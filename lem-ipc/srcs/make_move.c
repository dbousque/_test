

#include "lem_ipc.h"

char	navigate_towards(t_team_data *team, t_player *player,
													unsigned int attack_target)
{
	t_player		*target;
	int				x_decal;
	int				y_decal;

	(void)team;
	target = NULL;
	if (!(find_player(attack_target, &target)))
		return (0);
	x_decal = target->x > player->x ? 1 : 0;
	x_decal = target->x < player->x ? -1 : x_decal;
	y_decal = target->y > player->y ? 1 : 0;
	y_decal = target->y < player->y ? -1 : y_decal;
	if (y_decal != 0 && x_decal != 0)
	{
		if (abs((int)target->y - (int)player->y) >
										abs((int)target->x - (int)player->x))
		{
			x_decal = 0;
		}
		else
			y_decal = 0;
	}
	BOARD_GET(player->y, player->x) = FREE_BOARD_TILE;
	player->x += x_decal;
	player->y += y_decal;
	BOARD_GET(player->y, player->x) = player->team_id;
	return (1);
}

char	receive_messages(t_player *player, unsigned int *attack_target)
{
	t_lemipc_msg	msg;
	char			set;

	set = 0;
	while (1)
	{
		if (!(receive_message(player, &msg)))
			break ;
		set = 1;
		*attack_target = msg.attack_target;
	}
	return (set);
}

char	make_move(t_shared *shared, t_team_data *team, t_player *player)
{
	unsigned int	attack_target;
	char			set;
	unsigned int	ennemy_id;
	t_team_data		*ennemy_team;

	ennemy_team = NULL;
	set = receive_messages(player, &attack_target);
	if (is_surrounded(player, &ennemy_id))
	{
		if (!(find_team(ennemy_id, &ennemy_team)))
			return (0);
		ennemy_team->nb_killed_others++;
		exit_player(shared, player->team_id, player->player_id);
	}
	if (player->is_team_leader)
		make_attack_strategy(team, player, &attack_target, &set);
	if (set)
	{
		if (!(navigate_towards(team, player, attack_target)))
			return (1);
	}
	return (1);
}