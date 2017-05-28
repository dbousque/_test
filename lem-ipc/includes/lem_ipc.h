

#ifndef LEM_IPC_H
# define LEM_IPC_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <time.h>
# include <signal.h>
# include "list.h"
# include "msg_queue.h"
# include "shared_ressources.h"

# define DEFAULT_BOARD_SIZE 20
# define MUTEX_NAME "_sem_lemipc_"
# define GAME_DATA_KEY -4242
# define BOARD_KEY -4243
# define TEAM_DATA_KEY -4244
# define REMOVE_PLAYER_KEY -4245
# define FREE_BOARD_TILE (((unsigned int)INT_MAX) + 1)
# define BOARD_GET(y, x) (g_game_data->board[y * g_game_data->board_size + x])

typedef struct		s_params
{
	unsigned int	team_id;
	unsigned int	move_sleep_millis;
	unsigned int	initial_sleep;
	unsigned int	board_size;
}					t_params;

typedef struct		s_player
{
	char			is_team_leader;
	unsigned int	x;
	unsigned int	y;
	unsigned int	team_id;
	unsigned int	player_id;
}					t_player;

typedef struct		s_team_data
{
	unsigned int	team_id;
	t_player		*players_elts;
	size_t			players_len;
	size_t			players_size;
	unsigned int	nb_killed_others;
	unsigned int	nb_killed_self;
}					t_team_data;

typedef struct		s_game_data
{
	unsigned int	board_size;
	unsigned int	*board;
	size_t			nb_moves;
	unsigned int	nb_alive_players;
	unsigned int	player_counter;
	t_team_data		*team_data_elts;
	size_t			team_data_len;
	size_t			team_data_size;
}					t_game_data;

typedef struct		s_lemipc_msg
{
	unsigned int	attack_target;
	unsigned int	team_id;
	unsigned int	player_id;
}					t_lemipc_msg;

t_game_data			*g_game_data;
unsigned int		g_team_id;
unsigned int		g_player_id;
t_shared			*g_shared;

size_t				ft_strlen(char *str);
void				millis_sleep(unsigned int millis);
unsigned int		board_get(unsigned int y, unsigned int x);
char				parse_params(int argc, char **argv, t_params *params);
char				send_message(t_player *player, t_lemipc_msg *msg);
char				receive_message(t_player *player, t_lemipc_msg *msg);
char				update_ressources(t_shared *shared);
char				init_ressources(t_params *params, t_shared *shared);
char				add_player(t_shared *shared, t_params *params,
													unsigned int *player_id);
char				make_team_players(t_shared *shared, t_team_data *team);
void				double_teams_size(t_shared *shared, char *error);
void				double_players_size(t_shared *shared, t_team_data *team,
																char *error);
char				set_location_for_player(t_player *player, unsigned int n);
char				make_move(t_shared *shared, t_team_data *team,
															t_player *player);
char				is_surrounded(t_player *player, unsigned int *ennemy_id);
char				get_player_and_team(unsigned int team_id,
				unsigned int player_id, t_team_data **team, t_player **player);
char				find_player(unsigned int player_id, t_player **player);
char				find_team(unsigned int team_id, t_team_data **team);
void				make_attack_strategy(t_team_data *team, t_player *player,
									unsigned int *attack_target, char *set);
void				exit_player(t_shared *shared, unsigned int team_id,
										unsigned int player_id, char quit);

#endif