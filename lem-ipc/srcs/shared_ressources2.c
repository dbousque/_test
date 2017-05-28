

#include "shared_ressources.h"



  #include <sys/time.h>

char	lock_ressources(t_shared *shared)
{
	if (shared->is_locked)
	{
		printf("locking already locked ressources\n");
		return (0);
	}
	struct timeval my_time;
	gettimeofday(&my_time, NULL);
	printf("at : %d\n", my_time.tv_usec);
	printf("LOCKING!\n");
	if (sem_wait(shared->mutex) == -1)
	{
		printf("LOCCCCIINGGG EERRRORR!\n");
		shared->is_locked = 0;
		return (0);
	}
	shared->is_locked = 1;
	gettimeofday(&my_time, NULL);
	printf("received lock at : %d\n", my_time.tv_usec);
	return (1);
}

void	unlock_ressources(t_shared *shared)
{
	struct timeval my_time;
	gettimeofday(&my_time, NULL);
	printf("at : %d\n", my_time.tv_usec);
	if (shared->is_locked)
	{
		printf("UNLOCKING!\n");
		if (sem_post(shared->mutex) == -1)
			printf("ERROR WHILE UNLOCKING!\n");
	}
	else
	{
		printf("UNLOCKING BUT ALREADY UNLOCKED\n");
		fflush(stdout);
		sem_post(shared->mutex);
	}
	shared->is_locked = 0;
}

void	free_ressources(t_shared *shared)
{
	size_t				i;
	t_list				*ressources;
	t_shared_ressource	*res;

	ressources = &(shared->ressources);
	i = 0;
	while (i < ressources->len)
	{
		res = &(((t_shared_ressource*)ressources->elts)[i]);
		shmctl(res->shmid, IPC_RMID, 0);
		i++;
	}
	free(shared->ressources.elts);
	shared->ressources.len = 0;
	shared->ressources.size = 0;
	unlock_ressources(shared);
	sem_close(shared->mutex);
	sem_unlink(shared->mutex_name);
}