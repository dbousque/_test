

#include "lem_ipc.h"

char			set_location_for_player(t_player *player, unsigned int n)
{
	unsigned int	x;
	unsigned int	i;

	i = 0;
	x = 0;
	while (i < g_game_data->board_size * g_game_data->board_size)
	{
		if (g_game_data->board[i] == FREE_BOARD_TILE)
		{
			x++;
			if (x == n)
			{
				player->x = i % g_game_data->board_size;
				player->y = i / g_game_data->board_size;
				g_game_data->board[i] = player->team_id;
				return (1);
			}
		}
		i++;
	}
	printf("should not happen\n");
	return (0);
}