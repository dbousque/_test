/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_queue.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 18:06:17 by dbousque          #+#    #+#             */
/*   Updated: 2017/05/18 18:06:20 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msg_queue.h"

void	remove_msq_queue(int id)
{
	msgctl(id, IPC_RMID, NULL);
}

int		get_msq_queue(int key, char *error)
{
	int		id;

	id = msgget(key, IPC_CREAT | 0600);
	if (id == -1)
	{
		printf("msgget failed for key %d\n", key);
		*error = 1;
		return (0);
	}
	return (id);
}

char	receive_msq_queue(int id, size_t len, long type, char *res)
{
	t_msg	msg;
	size_t	i;

	if (msgrcv(id, &msg, MAX_MSG_LENGTH, type, IPC_NOWAIT) == -1)
		return (0);
	i = 0;
	while (i < len)
	{
		res[i] = msg.mtext[i];
		i++;
	}
	return (1);
}

char	send_msq_queue(int id, char *data, size_t len, long type)
{
	t_msg	msg;
	size_t	i;

	msg.mtype = type;
	i = 0;
	while (i < len)
	{
		msg.mtext[i] = data[i];
		i++;
	}
	if (msgsnd(id, &msg, len, IPC_NOWAIT))
	{
		printf("msgsnd failed\n");
		return (0);
	}
	return (1);
}
