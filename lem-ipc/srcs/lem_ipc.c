/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_ipc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 18:25:56 by dbousque          #+#    #+#             */
/*   Updated: 2017/05/15 18:25:59 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_ipc.h"

/*
void	test_msq_queue(int argc, t_params *params)
{
	t_player		player;
	t_lemipc_msg	msg;
  t_lemipc_msg  msg2;

	player.team_id = params->team_id;
	player.player_id = 2;
	msg.attack_target = 4;
	if (argc == 4)
  {
    if (!(send_message(&player, &msg)))
    {
      printf("could not send message\n");
      return ;
    }
  }
  else
  {
    if (!(receive_message(&player, &msg2)))
    {
      printf("could not receive message\n");
      return ;
    }
    printf("received target : %d\n", msg2.attack_target);
  }
}
*/

void	exit_if_necessary(void)
{
	struct timespec		req;

	req.tv_sec = 0;
	req.tv_nsec = 1 * 1000000;
	while (g_exiting)
	{
		if (g_exit)
		{
			printf("it's over\n");
			fflush(stdout);
			exit(0);
		}
		nanosleep(&req, &req);
	}
}

void	remove_player_from_team(t_team_data *team, unsigned int player_id)
{
	unsigned int	i;
	char			decal;

	decal = 0;
	i = 0;
	while (i < team->players_len)
	{
		if (team->players_elts[i].player_id == player_id)
			decal = 1;
		if (i < team->players_len - 1)
			team->players_elts[i] = team->players_elts[i + decal];
		i++;
	}
	team->players_len--;
	team->nb_killed_self++;
}


#include <sys/time.h>

void	exit_player(t_shared *shared, unsigned int team_id,
											unsigned int player_id, char quit)
{
	t_team_data		*team;
	t_player		*player;

	team = NULL;
	player = NULL;
	//unlock_ressources(shared);
	printf("exiting player %u in team %u...\n", player_id, team_id);
	//struct timeval my_time;
	//gettimeofday(&my_time, NULL);
	//printf("%d\n", my_time.tv_usec);
	/*if (!(lock_ressources(shared)))
	{
		printf("could not lock ressources during player %u exit\n", player_id);
		if (g_game_data->nb_alive_players == 0)
			free_ressources(shared);
		exit(0);
		return ;
	}*/
	//gettimeofday(&my_time, NULL);
	//printf("%d\n", my_time.tv_usec);
	/*if (!(update_ressources(shared)))
	{
		printf("could not update ressources while exiting\n");
		unlock_ressources(shared);
		if (g_game_data->nb_alive_players == 0)
			free_ressources(shared);
		exit(0);
		return ;
	}
	printf("updated\n");
	gettimeofday(&my_time, NULL);
	printf("%d\n", my_time.tv_usec);*/
	if (!(get_player_and_team(team_id, player_id, &team, &player)))
	{
		printf("could not find player %u while exiting\n", player_id);
		//unlock_ressources(shared);
		//if (g_game_data->nb_alive_players == 0)
		//	free_ressources(shared);
		//exit(0);
		return ;
	}
	printf("got player and team\n");
	//gettimeofday(&my_time, NULL);
	//printf("%d\n", my_time.tv_usec);
	remove_player_from_team(team, player_id);
	//unlock_ressources(shared);
	//if (g_game_data->nb_alive_players == 0)
	//{
	//	printf("last player, freeing ressources...\n");
	//	free_ressources(shared);
	//}
	printf("done.\n");
	if (quit)
	{
		unlock_ressources(shared);
		exit(0);
	}
	//exit(0);
}

void	could_not_lock(t_shared *shared, unsigned int team_id,
														unsigned int player_id)
{
	printf("player %u could not lock ressources, exiting...\n", player_id);
	exit_player(shared, team_id, player_id, 1);
}

void	remove_queues(void)
{
	size_t	i;

	remove_queue(REMOVE_PLAYER_KEY);
	i = 0;
	while (i < g_game_data->team_data_len)
	{
		remove_queue((((t_team_data*)g_game_data->team_data_elts))[i].team_id);
		i++;
	}
}

void	signal_handler(int dummy)
{
	t_player		mock_player;
	t_lemipc_msg	msg;

	g_exiting = 1;
	(void)dummy;
	if (!g_shared)
	{
		printf("CTRL-C catched but no data\n");
		exit(0);
		return ;
	}
	printf("locked ? %d\n", g_shared->is_locked);
	printf("catched CTRL-C\n");
	printf("exiting...\n");
	g_game_data->nb_alive_players--;
	if (g_game_data->nb_alive_players <= 0) {
		printf("last player, freeing ressources and exiting\n");
		remove_queues();
		free_ressources(g_shared);
		exit(0);
	}
	mock_player.team_id = REMOVE_PLAYER_KEY;
	mock_player.player_id = 1;
	msg.team_id = g_team_id;
	msg.player_id = g_player_id;
	send_message(&mock_player, &msg);
	printf("done\n");
	unlock_ressources(g_shared);
	g_exit = 1;
	exit(0);
	//exit_player(g_shared, g_team_id, g_player_id);
}

void	remove_dead_players(t_shared *shared)
{
	t_player		mock_player;
	t_lemipc_msg	msg;

	mock_player.team_id = REMOVE_PLAYER_KEY;
	mock_player.player_id = 1;
	while (receive_message(&mock_player, &msg))
	{
		if (g_exiting)
		{
			send_message(&mock_player, &msg);
			exit_if_necessary();
		}
		exit_player(shared, msg.team_id, msg.player_id, 0);
	}
}

void	update_leader_if_necessary(t_team_data *team, t_player *player)
{
	unsigned int	i;

	i = 0;
	while (i < team->players_len)
	{
		exit_if_necessary();
		if (team->players_elts[i].is_team_leader)
			return ;
		i++;
	}
	player->is_team_leader = 1;
}

void	print_player(t_player *player)
{
	exit_if_necessary();
	printf("\n  is_team_leader: %d\n  x: %u\n  y: %u\n  team_id: %u\n  player_id: %u\n", player->is_team_leader, player->x, player->y, player->team_id, player->player_id);
}

void	print_team(t_team_data *team)
{
	size_t	i;

	printf("before print team\n");
	printf("\nteam_id: %u\nnb_killed_others: %u\nnb_killed_self: %u\n", team->team_id, team->nb_killed_others, team->nb_killed_self);
	printf("players_elts: %p\nplayers_len: %lu\nplayers_size: %lu\n", team->players_elts, team->players_len, team->players_size);
	i = 0;
	exit_if_necessary();
	while (i < team->players_len)
	{
		printf("printing player %lu\n", i);
		fflush(stdout);
		exit_if_necessary();
		print_player(&(team->players_elts[i]));
		printf("after printing player %lu\n", i);
		fflush(stdout);
		i++;
	}
}

void	print_data(t_shared *shared)
{
	size_t	i;

	(void)shared;
	printf("\nboard_size: %u\nboard: %p\nnb_moves: %lu\nnb_alive_players: %u\n", g_game_data->board_size, g_game_data->board, g_game_data->nb_moves, g_game_data->nb_alive_players);
	printf("  first team len : %lu\n", g_game_data->team_data_elts[0].players_len);
	printf("player_counter: %u\nteam_data_elts: %p\nteam_data_len: %lu\nteam_data_size: %lu\n", g_game_data->player_counter, g_game_data->team_data_elts, g_game_data->team_data_len, g_game_data->team_data_size);
	exit_if_necessary();
	i = 0;
	while (i < g_game_data->team_data_len)
	{
		exit_if_necessary();
		print_team(&(g_game_data->team_data_elts[i]));
		i++;
	}
}

void	launch(t_params *params, t_shared *shared)
{
	t_team_data		*team;
	t_player		*player;
	unsigned int	player_id;
	unsigned int	team_id;

	team = NULL;
	player = NULL;
	if (!(add_player(shared, params, &player_id)))
		return ;
	team_id = params->team_id;
	g_exit = 0;
	g_exiting = 0;
	g_shared = shared;
	g_team_id = team_id;
	g_player_id = player_id;
	int i = 0;
	while (1)
	{
		i++;
		//printf("enter loop\n");
		//fflush(stdout);
		//sleep(2);
		exit_if_necessary();
		if (!(lock_ressources(shared)))
		{
			exit_if_necessary();
			return (could_not_lock(shared, team_id, player_id));
		}
		exit_if_necessary();
		printf("LOCKED\n");
		//sleep(1);
		//printf("END SLEEP\n");
		fflush(stdout);
		if (!(update_ressources(shared)))
		{
			printf("could not update ressources. exiting...\n");
			return (exit_player(shared, team_id, player_id, 1));
		}
		//print_data(shared);
		exit_if_necessary();
		//printf("removing\n");
		//fflush(stdout);
		remove_dead_players(shared);
		exit_if_necessary();
		//printf("updated\n");
		//fflush(stdout);
		g_game_data->nb_moves++;
		if (!(get_player_and_team(team_id, player_id, &team, &player)))
			return (exit_player(shared, team_id, player_id, 1));
		exit_if_necessary();
		//printf("got player and team\n");
		//fflush(stdout);
		update_leader_if_necessary(team, player);
		exit_if_necessary();
		//printf("updated leader\n");
		//fflush(stdout);
		if (!(make_move(shared, team, player)))
			return (exit_player(shared, team_id, player_id, 1));
		exit_if_necessary();
		//printf("made move\n");
		//fflush(stdout);
		unlock_ressources(shared);
		exit_if_necessary();
		printf("UNLOCKED\n");
		fflush(stdout);
	}
}

int		main(int argc, char **argv)
{
	t_params	params;
	t_shared	shared;

	srand(time(NULL));
	g_shared = NULL;
	g_team_id = 0;
	g_player_id = 0;
	signal(SIGINT, signal_handler);
	if (!(parse_params(argc, argv, &params)))
		return (0);
	printf("before init\n");
	if (!(init_ressources(&params, &shared)))
		return (0);
	printf("INITED\n");
	fflush(stdout);
	launch(&params, &shared);
	return (0);
}
