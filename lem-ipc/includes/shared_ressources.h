

#ifndef SHARED_RESSOURCES_H
# define SHARED_RESSOURCES_H

# include <semaphore.h>
# include <sys/shm.h>
# include <fcntl.h>
# include <stdio.h>
# include "list.h"

typedef struct	s_shared
{
	sem_t		*mutex;
	char		*mutex_name;
	t_list		ressources;
}				t_shared;

typedef struct	s_shared_ressource
{
	key_t		key;
	int			shmid;
	void		*data;
	size_t		size;
}				t_shared_ressource;

char			init_shared(t_shared *shared, char *mutex_name);
char			add_shared_ressource(t_shared *shared, key_t key, size_t size);
void			*get_shared_ressource(t_shared *shared, key_t key,
																char *error);
char			lock_ressources(t_shared *shared);
void			unlock_ressources(t_shared *shared);
void			free_ressources(t_shared *shared);

#endif