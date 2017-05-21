/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared_ressources.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 15:11:47 by dbousque          #+#    #+#             */
/*   Updated: 2017/05/19 15:11:49 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared_ressources.h"

char	set_mutex(t_shared *shared, char *mutex_name)
{
	shared->mutex = sem_open(mutex_name, O_CREAT, 0644, 1);
	if(shared->mutex == SEM_FAILED)
	{
		printf("unable to create or get semaphore\n");
		sem_unlink(mutex_name);
		shared->mutex = NULL;
		return (0);
	}
	shared->is_locked = 0;
	shared->mutex_name = mutex_name;
	return (1);
}

char	init_shared(t_shared *shared, char *mutex_name)
{
	if (!(set_mutex(shared, mutex_name)))
		return (0);
	if (!(init_list(&(shared->ressources), sizeof(t_shared_ressource))))
		return (0);
	return (1);
}

char	add_shared_ressource(t_shared *shared, key_t key, size_t size,
																char *creation)
{
	t_shared_ressource	res;

	*creation = 1;
	res.key = key;
	res.size = size;
	res.shmid = shmget(key, size, IPC_CREAT | IPC_EXCL | 0666);
	if (res.shmid < 0)
	{
		*creation = 0;
		res.shmid = shmget(key, size, IPC_CREAT | 0666);
	}
	if (res.shmid < 0)
	{
		printf("failure in shmget\n");
		return (0);
	}
	res.data = shmat(res.shmid, NULL, 0);
	if (res.data < 0 || !(res.data))
		return (0);
	if (!(add_to_list(&(shared->ressources), &res)))
		return (0);
	return (1);
}

void	*get_shared_ressource(t_shared *shared, key_t key, char *error)
{
	size_t				i;
	t_list				*ressources;
	t_shared_ressource	*res;

	ressources = &(shared->ressources);
	i = 0;
	while (i < ressources->len)
	{
		res = &(((t_shared_ressource*)ressources->elts)[i]);
		if (res->key == key)
			return (res->data);
		i++;
	}
	*error = 1;
	return (NULL);
}
