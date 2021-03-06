/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_ipc_msg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 18:33:41 by dbousque          #+#    #+#             */
/*   Updated: 2017/05/18 18:33:43 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_ipc.h"

char	send_message(t_player *player, t_lemipc_msg *msg)
{
	int		queue_id;
	char	error;

	error = 0;
	queue_id = get_msq_queue(player->team_id, &error);
	if (error)
	{
		printf("could not get msg queue\n");
		return (0);
	}
	if (!(send_msq_queue(queue_id, (char*)msg, sizeof(t_lemipc_msg),
														player->player_id)))
	{
		printf("could not send msg\n");
		return (0);
	}
	return (1);
}

char	receive_message(t_player *player, t_lemipc_msg *msg)
{
	int		queue_id;
	char	error;

	error = 0;
	queue_id = get_msq_queue(player->team_id, &error);
	if (error)
	{
		printf("could not get msg queue\n");
		return (0);
	}
	if (!(receive_msq_queue(queue_id, sizeof(t_lemipc_msg), player->player_id,
																(char*)msg)))
	{
		return (0);
	}
	return (1);
}

void	remove_queue(int key)
{
	remove_msq_queue(key);
}
