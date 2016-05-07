

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libdodo/libdodo.h"
# include <unistd.h>
# include <dirent.h>
# include <sys/stat.h>
# include <signal.h>
# include <stdio.h>
# include <termios.h>

typedef struct	s_linked_list
{
	void		**elts;
	int			len;
	int			size;
}				t_linked_list;

t_linked_list	*new_list(void);
void			add_to_list(t_linked_list *list, void *elt);
char			*find_executable(char *prog, char **env);
char			char_in_str(char *str, char c);
char			*build_file_path(char *dir_path, char *file_name);
char			startswith(char *str, char *env);
void			launch_shell(void);
void			free_ptrptr(void **ptrptr);
void			malloc_error(void);

#endif