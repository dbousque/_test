

#ifndef LEM_IPC_H
# define LEM_IPC_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include "list.h"

typedef struct		s_params
{
	unsigned int	team_id;
	unsigned int	board_size;
}					t_params;

typedef struct		s_game_data
{
	unsigned int	board_size;
	unsigned int	**board;
	size_t			nb_moves;
	unsigned int	nb_players;
	t_list			kills_by_team;
}					t_game_data;

typedef struct		s_team_kills
{
	unsigned int	nb_killed_others;
	unsigned int	nb_killed_self;
}					t_team_kills;

typedef struct		s_player
{
	unsigned int	x;
	unsigned int	y;
	unsigned int	team_id;
}					t_player;

# define DEFAULT_BOARD_SIZE 20

size_t				ft_strlen(char *str);
char				parse_params(int argc, char **argv, t_params *params);

#endif