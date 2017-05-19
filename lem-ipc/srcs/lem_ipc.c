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

int		main(int argc, char **argv)
{
	t_params		params;
	t_shared		shared;
	unsigned int	*board_size;
	char			error;

	error = 0;
	if (!(parse_params(argc, argv, &params)))
		return (0);
	init_shared(&shared, MUTEX_NAME);
	if (!(add_shared_ressource(&shared, BOARD_SIZE_KEY, sizeof(unsigned int))))
	{
		printf("could not add board_size\n");
		return (0);
	}
	board_size = (unsigned int*)get_shared_ressource(&shared, BOARD_SIZE_KEY,
																	&error);
	if (error)
	{
		printf("could not get board_size\n");
		return (0);
	}
	printf("board_size : %u\n", *board_size);
	if (!(lock_ressources(&shared)))
	{
		printf("could not lock ressources\n");
		return (0);
	}
	*board_size = params.board_size;
	unlock_ressources(&shared);
	board_size = (unsigned int*)get_shared_ressource(&shared, BOARD_SIZE_KEY,
																	&error);
	if (error)
	{
		printf("could not get board_size\n");
		return (0);
	}
	printf("board_size : %u\n", *board_size);
	free_ressources(&shared);
	return (0);
}
