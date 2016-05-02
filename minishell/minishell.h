

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libdodo/libdodo.h"
# include <unistd.h>
# include <stdio.h>

typedef struct	s_linked_list
{
	void		**elts;
	int			len;
	int			size;
}				t_linked_list;

t_linked_list	*new_list(void);
void			add_to_list(t_linked_list *list, void *elt);

#endif