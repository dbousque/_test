

#ifndef LEM_IPC_H
# define LEM_IPC_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <time.h>
# include "list.h"
# include "msg_queue.h"
# include "shared_ressources.h"

# define DEFAULT_BOARD_SIZE 20
# define MUTEX_NAME "_sem_lemipc_"
# define GAME_DATA_KEY -4242
# define BOARD_KEY -4243
# define TEAM_DATA_KEY -4244

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
	char			attack_or_take_team_lead;
	unsigned int	attack_target;
}					t_lemipc_msg;

t_game_data			*g_game_data;

size_t				ft_strlen(char *str);
void				millis_sleep(unsigned int millis);
char				parse_params(int argc, char **argv, t_params *params);
char				send_message(t_player *player, t_lemipc_msg *msg);
char				receive_message(t_player *player, t_lemipc_msg *msg);
char				update_ressources(t_shared *shared);
char				init_ressources(t_params *params, t_shared *shared);
char				add_player(t_shared *shared, t_params *params);

#endif