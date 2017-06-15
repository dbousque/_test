

#include "shared_ressources.h"



  #include <sys/time.h>

char	lock_ressources(t_shared *shared)
{
	int		r;
	if (shared->is_locked)
	{
		printf("locking already locked ressources\n");
		return (0);
	}
	//int		sem_val;
	struct timeval my_time;
	//sem_getvalue(shared->mutex, &sem_val);
	//printf("semaphore value : %d\n", sem_val);
	gettimeofday(&my_time, NULL);
	printf("at : %d\n", my_time.tv_usec);
	printf("LOCKING!\n");
	while ((r = sem_wait(shared->mutex)) == -1 && errno == EINTR)
	{
		printf("LOCCCCIINGGG EERRRORR!\n");
	}
	if (r == -1)
	{
		return (0);
	}
	shared->is_locked = 1;
	//sem_getvalue(shared->mutex, &sem_val);
	//printf("semaphore value : %d\n", sem_val);
	gettimeofday(&my_time, NULL);
	printf("received lock at : %d\n", my_time.tv_usec);
	return (1);
}

void	unlock_ressources(t_shared *shared)
{
	//int		sem_val;
	struct timeval my_time;
	//sem_getvalue(shared->mutex, &sem_val);
	//printf("semaphore value : %d\n", sem_val);
	gettimeofday(&my_time, NULL);
	printf("at : %d\n", my_time.tv_usec);
	if (shared->is_locked)
	{
		printf("UNLOCKING!\n");
		if (sem_post(shared->mutex) == -1)
		{
			printf("ERROR WHILE UNLOCKING!\n");
			return ;
		}
	}
	else
	{
		printf("UNLOCKING BUT ALREADY UNLOCKED\n");
		fflush(stdout);
		if (sem_post(shared->mutex) == -1)
			return ;
	}
	shared->is_locked = 0;
	//sem_getvalue(shared->mutex, &sem_val);
	//printf("semaphore value : %d\n", sem_val);
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