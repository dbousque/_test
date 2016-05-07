

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libdodo/libdodo.h"
# include <unistd.h>
# include <dirent.h>
# include <sys/stat.h>
# include <signal.h>
# include <stdio.h>
# include <termios.h>

typedef struct		s_linked_list
{
	void			**elts;
	int				len;
	int				size;
}					t_linked_list;

typedef struct		s_dir
{
	char			*path;
	t_linked_list	*files;
}					t_dir;

typedef struct		s_ind
{
	size_t			start;
	size_t			i;
}					t_ind;

typedef struct		s_vars
{
	size_t			start;
	size_t			i;
	size_t			x;
}					t_vars;

t_linked_list		*new_list(void);
void				add_to_list(t_linked_list *list, void *elt);
char				*find_executable(char *prog, char **env);
char				char_in_str(char *str, char c);
char				*build_file_path(char *dir_path, char *file_name);
char				startswith(char *str, char *env);
void				launch_shell(void);
void				free_ptrptr(void **ptrptr);
void				malloc_error(void);
t_linked_list		*get_files_from_path(char **env);
void				get_files_in_dir(char *path, t_linked_list *files, char dirs, char not_exec);
void				get_files_from_path2(char **env, t_linked_list *files);
char				**split_command_in_args(char *command);

#endif