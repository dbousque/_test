

#ifndef SHARED_RESSOURCES_H
# define SHARED_RESSOURCES_H

# include "list.h"

typedef struct	s_shared
{
	sem_t		*mutex;
	t_list		ressources;
}				t_shared;

typedef struct	s_shared_ressource
{
	key_t		key;
	int			shmid;
	void		*data;
	size_t		size;
}				t_shared_ressource

#endif