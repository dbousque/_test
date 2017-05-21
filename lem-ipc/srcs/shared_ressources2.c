

#include "shared_ressources.h"

char	lock_ressources(t_shared *shared)
{
	if (shared->is_locked)
	{
		printf("locking already locked ressources\n");
		return (0);
	}
	if (sem_wait(shared->mutex) == -1)
		return (0);
	shared->is_locked = 1;
	return (1);
}

void	unlock_ressources(t_shared *shared)
{
	if (shared->is_locked)
		sem_post(shared->mutex);
	shared->is_locked = 0;
}

void	free_ressources(t_shared *shared)
{
	size_t				i;
	t_list				*ressources;
	t_shared_ressource	*res;

	sem_close(shared->mutex);
	sem_unlink(shared->mutex_name);
	ressources = &(shared->ressources);
	i = 0;
	while (i < ressources->len)
	{
		res = &(((t_shared_ressource*)ressources->elts)[i]);
		shmctl(res->shmid, IPC_RMID, 0);
		i++;
	}
}