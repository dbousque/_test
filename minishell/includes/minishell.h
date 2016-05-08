/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/08 15:50:43 by dbousque          #+#    #+#             */
/*   Updated: 2016/05/08 15:50:46 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
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

char				**g_environ;

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
void				get_files_in_dir(char *path, t_linked_list *files,
												char dirs, char not_exec);
void				get_files_from_path2(char **env, t_linked_list *files);
char				**split_command_in_args(char *command);
char				*find_exec_from_path(char *prog, t_linked_list *dirs);
char				*get_path(char **env);
void				command_not_found(char *command);
char				file_in_list(char *file, t_linked_list *files);
size_t				strstrlen(char **strstr);
char				*get_current_path(void);
void				print_prompt(char **env);
char				*get_input(char **env, t_linked_list *history);
char				*get_logname(char **env);
void				read_chars(char **env, t_linked_list *history, char **line,
											size_t len_current_size[]);
void				place_cursor_start_of_line(size_t *current);
char				autocomplete(char **line, size_t *current, size_t *len,
																char **env);
void				write_n_char(size_t n, char c);
char				*get_last_history(t_linked_list *history, char *line,
											size_t *len, int *history_ind);
char				*get_next_history(t_linked_list *history, size_t *len,
															int *history_ind);
char				arrow(char tmp_char);
void				remove_char_at_pos(char *line, size_t current, size_t len);
void				add_char_at_pos(char *line, size_t current, size_t len,
																	char c);
int					getch(void);
char				*double_size(char *line, size_t *size);
void				clear_line(int nb);
size_t				get_len(char **parts);
void				look_for_matching_exec(char *start,
									t_linked_list *candidates, char **env);
void				look_for_matching_dir(char *start,
												t_linked_list *candidates);
char				*get_end(char *start, int *nb_removed);
char				*get_dir_name(char *start);
char				*get_current_dir(void);
void				look_for_matching_file(char *start,
												t_linked_list *candidates);
char				*match(char *start, t_linked_list *candidates);
void				handle_builtin(char **line, char ***env);
char				***split_in_commands(char **line);
void				replace_tilde(char **line, char **env);
void				ctrl_c(int id);
char				**copy_environ(void);
char				get_found(char **line, char ***env, size_t *i);
void				set_env(char **line, char ***env);
void				print_strstr(char **strstr);
char				*get_home(char **env);
char				*get_env_var(char *key, char **env);
char				ignore_char(char c);
void				add_string_to_args(t_linked_list *args, char *command,
													size_t start, size_t end);

#endif
