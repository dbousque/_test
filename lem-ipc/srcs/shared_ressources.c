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

char	find_shared_ressource(t_shared *shared, key_t key,
												t_shared_ressource **existing)
{
	size_t				i;
	t_shared_ressource	*tmp;

	i = 0;
	while (i < shared->ressources.len)
	{
		tmp = &(((t_shared_ressource*)shared->ressources.elts)[i]);
		if (tmp->key == key)
		{
			*existing = tmp;
			return (1);
		}
		i++;
	}
	return (0);
}

char	add_shared_ressource(t_shared *shared, key_t key, size_t size,
																char *creation)
{
	t_shared_ressource	res;
	t_shared_ressource	*existing;
	char				already_set_in_process;

	//printf("adding %d of size %lu\n", key, size);
	already_set_in_process = find_shared_ressource(shared, key, &existing);
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
	//printf("shmid : %d\n", res.shmid);
	if (already_set_in_process)
	{
		if (shmdt(existing->data) == -1)
			return (0);
	}
	res.data = shmat(res.shmid, NULL, 0);
	if (res.data == (void*)-1 || !(res.data))
	{
		//perror("la");
		printf("shmat failed\n");
		return (0);
	}
	if (!already_set_in_process)
	{
		if (!(add_to_list(&(shared->ressources), &res)))
			return (0);
	}
	else
		*existing = res;
	return (1);
}

char	remove_shared_ressource(t_shared *shared, key_t key, void *addr)
{
	t_shared_ressource	*res;
	size_t				i;
	char				found;
	int					decal;

	//printf("removing %d\n", key);
	decal = 0;
	found = 0;
	i = 0;
	while (i < shared->ressources.len)
	{
		res = &(((t_shared_ressource*)shared->ressources.elts)[i]);
		if (res->key == key)
		{
			//printf("shmid : %d\n", res->shmid);
			decal = 1;
			found = 1;
			if (shmctl(res->shmid, IPC_RMID, 0) == -1 || shmdt(addr) == -1)
			{
				printf("could not remove ressource\n");
				return (0);
			}
		}
		if (i < shared->ressources.len - 1)
			*res = ((t_shared_ressource*)shared->ressources.elts)[i + decal];
		i++;
	}
	if (found)
		shared->ressources.len--;
	return (found);
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
