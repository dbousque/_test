

#include "minishell.h"

extern char	**environ;

void	malloc_error(void)
{
	ft_putstr("Could not allocate memory.\n");
	exit(1);
}

char	*get_env_var(char *key, char **env)
{
	size_t	i;

	i = 0;
	while (env[i])
	{
		if (startswith(key, env[i]))
			return (env[i] + ft_strlen(key) + 1);
		i++;
	}
	return (NULL);
}

char	*get_logname(char **env)
{
	char	*tmp;

	tmp = get_env_var("LOGNAME", env);
	if (!tmp)
		tmp = get_env_var("USER", env);
	return (tmp);
}

char	*get_current_path(void)
{
	char	*path;
	size_t	size;

	size = 1024;
	while (1)
	{
		if (!(path = (char*)malloc(sizeof(char) * size)))
			malloc_error();
		getcwd(path, size);
		if (path)
			break ;
		free(path);
		size *= 2;
	}
	return (path);
}

char	*get_current_dir(void)
{
	char	*path;
	char	*res;
	size_t	i;

	path = get_current_path();
	i = 0;
	while (path[i])
		i++;
	i--;
	while (i > 0 && path[i - 1] != '/')
		i--;
	res = ft_strdup(path + i);
	free(path);
	return (res);
}

void	print_prompt(char **env)
{
	char	*current_dir;

	ft_putstr(get_logname(env));
	ft_putstr(":");
	current_dir = get_current_dir();
	ft_putstr("[0;36;40m");
	ft_putstr(current_dir);
	ft_putstr("[0m");
	free(current_dir);
	ft_putstr("$> ");
}

int		getch(void)
{
	struct termios	oldtc;
	struct termios	newtc;
	int				ch;

	tcgetattr(STDIN_FILENO, &oldtc);
	newtc = oldtc;
	newtc.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newtc);
	ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldtc);
	return (ch);
}

char	*double_size(char *line, size_t *size)
{
	char	*new_line;
	size_t	i;

	*size *= 2;
	if (!(new_line = (char*)malloc(sizeof(char) * (*size + 1))))
		malloc_error();
	i = 0;
	while (line[i])
	{
		new_line[i] = line[i];
		i++;
	}
	new_line[i] = '\0';
	free(line);
	return (new_line);
}

void	add_char_at_pos(char *line, size_t current, size_t len, char c)
{
	size_t	i;

	i = len;
	while (i > current)
	{
		line[i] = line[i - 1];
		i--;
	}
	line[current] = c;
	line[len + 1] = '\0';
	ft_putstr(line + current);
	i = current;
	while (i < len)
	{
		write(1, "\b", 1);
		i++;
	}
}

void	clear_line(int nb)
{
	int		i;

	i = 0;
	while (i < nb)
	{
		write(1, " ", 1);
		i++;
	}
	i = 0;
	while (i < nb)
	{
		write(1, "\b", 1);
		i++;
	}
}

void	remove_char_at_pos(char *line, size_t current, size_t len)
{
	size_t	i;

	i = current;
	while (i < len)
	{
		line[i - 1] = line[i];
		i++;
	}
	line[i - 1] = '\0';
	clear_line((int)(len - current));
	write(1, "\b \b", 3);
	ft_putstr(line + current - 1);
	i = current;
	while (i < len)
	{
		write(1, "\b", 1);
		i++;
	}
}

char	arrow(char tmp_char)
{
	if (tmp_char == 27)
	{
		tmp_char = (char)getch();
		if (tmp_char == 91)
		{
			tmp_char = (char)getch();
			if (tmp_char == 68)
				return (1);
			if (tmp_char == 67)
				return (2);
			if (tmp_char == 65)
				return (3);
			if (tmp_char == 66)
				return (4);
		}
	}
	return (0);
}

void	place_cursor_start_of_line(size_t *current)
{
	while (*current > 0)
	{
		write(1, "\b", 1);
		(*current)--;
	}
}

char	*get_last_history(t_linked_list *history, char *line, size_t *len, int *history_ind)
{
	if (*history_ind == history->len)
	{
		free(history->elts[history->len - 1]);
		history->elts[history->len - 1] = ft_strdup(line);
	}
	(*history_ind)--;
	*len = ft_strlen(history->elts[*history_ind - 1]);
	return (ft_strdup(history->elts[*history_ind - 1]));
}

char	*get_next_history(t_linked_list *history, size_t *len, int *history_ind)
{
	(*history_ind)++;
	*len = ft_strlen(history->elts[*history_ind - 1]);
	return (ft_strdup(history->elts[*history_ind - 1]));
}

void	write_n_char(size_t n, char c)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		write(1, &c, 1);
		i++;
	}
}

size_t	strstrlen(char **strstr)
{
	size_t	i;

	i = 0;
	while (strstr[i])
		i++;
	return (i);
}

char	*get_dir_name(char *start)
{
	int		i;
	char	*res;
	int		x;

	i = ft_strlen(start);
	i--;
	while (i >= 0 && start[i] != '/')
		i--;
	if (!(res = (char*)malloc(sizeof(char) * (i + 2))))
		malloc_error();
	res[i + 1] = '\0';
	x = 0;
	while (x <= i)
	{
		res[x] = start[x];
		x++;
	}
	return (res);
}

void	look_for_matching_exec(char *start, t_linked_list *candidates, char **env)
{
	char	*tmp_dir;

	if (char_in_str(start, '/'))
	{
		tmp_dir = get_dir_name(start);
		get_files_in_dir(tmp_dir, candidates, 1, 0);
		free(tmp_dir);
	}
	else
		get_files_from_path2(env, candidates);
}

void	look_for_matching_dir(char *start, t_linked_list *candidates)
{
	char	*tmp_dir;

	if (char_in_str(start, '/'))
	{
		tmp_dir = get_dir_name(start);
		get_files_in_dir(tmp_dir, candidates, 2, 1);
		free(tmp_dir);
	}
	else
		get_files_in_dir("./", candidates, 2, 1);
}

char	*match(char *start, t_linked_list *candidates)
{
	int		i;
	size_t	x;
	char	*cand;
	int		count;

	count = 0;
	i = 0;
	while (i < candidates->len)
	{
		x = 0;
		while (start[x] && ((char*)candidates->elts[i])[x]
			&& start[x] == ((char*)candidates->elts[i])[x])
			x++;
		if (!start[x])
		{
			cand = candidates->elts[i];
			count++;
		}
		i++;
	}
	if (count != 1)
		return (NULL);
	return (ft_strdup(cand));
}

char	*get_end(char *start, int *nb_removed)
{
	int		i;

	if (!char_in_str(start, '/'))
	{
		*nb_removed = 0;
		return (start);
	}
	i = ft_strlen(start);
	i--;
	while (i >= 0)
	{
		if (start[i] == '/')
		{
			*nb_removed = i + 1;
			return (start + i + 1);
		}
		i--;
	}
	*nb_removed = 0;
	return (start);
}

char	*rebuild_res(char *res, char *line, int nb_removed)
{
	size_t	len;
	int		i;
	char	*final;

	len = ft_strlen(res) + nb_removed;
	if (!(final = (char*)malloc(sizeof(char) * (len + 1))))
		malloc_error();
	final[len] = '\0';
	i = 0;
	while (i < nb_removed)
	{
		final[i] = line[i];
		i++;
	}
	while (res[i - nb_removed])
	{
		final[i] = res[i - nb_removed];
		i++;
	}
	return (final);
}

void	look_for_matching_file(char *start, t_linked_list *candidates)
{
	char	*tmp_dir;

	if (char_in_str(start, '/'))
	{
		tmp_dir = get_dir_name(start);
		get_files_in_dir(tmp_dir, candidates, 1, 1);
		free(tmp_dir);
	}
	else
		get_files_in_dir("./", candidates, 1, 1);
}

size_t	get_len(char **parts)
{
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	while (parts[i] && parts[i + 1])
	{
		len += ft_strlen(parts[i]) + 1;
		i++;
	}
	return (len);
}

char	*append_replace(char *res, size_t len, char *replace)
{
	size_t	i;

	i = 0;
	while (replace[i])
	{
		res[len] = replace[i];
		len++;
		i++;
	}
	res[len] = ' ';
	return (res);
}

void	add_removed(char *res, char *last, int nb_removed, size_t len)
{
	int		i;

	i = 0;
	while (i < nb_removed)
	{
		res[len] = last[i];
		len++;
		i++;
	}
}

char	*replace_end(char **parts, char *replace, int nb_removed)
{
	size_t	len;
	size_t	i;
	size_t	x;
	char	*res;

	len = get_len(parts);
	if (!(res = (char*)malloc(sizeof(char) * (len + ft_strlen(replace) + nb_removed + 2))))
		malloc_error();
	res[len + ft_strlen(replace) + nb_removed + 1] = '\0';
	i = 0;
	len = 0;
	while (parts[i] && parts[i + 1])
	{
		x = 0;
		while (parts[i][x])
		{
			res[len] = parts[i][x];
			len++;
			x++;
		}
		res[len] = ' ';
		len++;
		i++;
	}
	add_removed(res, parts[i], nb_removed, len);
	return (append_replace(res, len + nb_removed, replace));
}

char	free_n_return_autocomplete(char **args, t_linked_list *candidates)
{
	free_ptrptr((void**)args);
	free(candidates->elts);
	free(candidates);
	return (0);	
}

void	write_completed_version(size_t *current, size_t *len, char *res)
{
	write_n_char(*current, '\b');
	write_n_char(*len, ' ');
	write_n_char(*len, '\b');
	ft_putstr(res);
}

char	autocomplete(char **line, size_t *current, size_t *len, char **env)
{
	t_linked_list	*candidates;
	char			**args;
	char			*res;
	int				nb_removed;

	candidates = new_list();
	args = split_command_in_args(*line);
	if (!args || strstrlen(args) == 0)
		return (0);
	if (strstrlen(args) == 1)
		look_for_matching_exec(args[0], candidates, env);
	else if (strstrlen(args) == 2 && ft_strcmp(args[0], "cd") == 0)
		look_for_matching_dir(args[1], candidates);
	else
		look_for_matching_file(args[strstrlen(args) - 1], candidates);
	res = match(get_end(args[strstrlen(args) - 1], &nb_removed), candidates);
	if (!res)
		return (free_n_return_autocomplete(args, candidates));
	res = replace_end(args, res, nb_removed);
	free_n_return_autocomplete(args, candidates);
	free(*line);
	*line = res;
	write_completed_version(current, len, res);
	*len = ft_strlen(res);
	*current = *len;
	return (0);
}

char	cursor_stuff_one(char tmp_char, char **line, size_t len_current_size[], char **env)
{
	size_t		*len;
	size_t		*current;
	size_t		*size;

	len = &(len_current_size[0]);
	current = &(len_current_size[1]);
	size = &(len_current_size[2]);
	if (tmp_char == 1)
		place_cursor_start_of_line(current);
	else if (tmp_char == '\t')
	{
		if (autocomplete(line, current, len, env))
			*size = *len;
	}
	else if (tmp_char == 5)
	{
		ft_putstr(*line + *current);
		*current = *len;
	}
	else
		return (0);
	return (1);
}

void	navigate_history(char tmp_char, char **line, t_linked_list *history,
												size_t len_current_size[])
{
	int			*history_ind;
	size_t		*len;
	size_t		*current;
	size_t		*size;

	history_ind = (int*)&(len_current_size[3]);
	len = &(len_current_size[0]);
	current = &(len_current_size[1]);
	size = &(len_current_size[2]);
	if ((tmp_char == 3 && history->len > 1 && *history_ind > 1)
		|| (tmp_char == 4 && history->len > 1 && *history_ind < history->len))
	{
		write_n_char(*current, '\b');
		write_n_char(*len, ' ');
		write_n_char(*len, '\b');
		if ((tmp_char == 3 && history->len > 1 && *history_ind > 1))
			*line = get_last_history(history, *line, len, history_ind);
		else
			*line = get_next_history(history, len, history_ind);
		ft_putstr(*line);
		*size = *len;
		*current = *len;
	}
}

void	arrows_management(char **line, t_linked_list *history,
											size_t len_current_size[])
{
	char		tmp_char;
	size_t		*len;
	size_t		*current;

	len = &(len_current_size[0]);
	current = &(len_current_size[1]);
	tmp_char = arrow(27);
	if (tmp_char == 1 && *current > 0)
	{
		write(1, "\b", 1);
		(*current)--;
	}
	else if (tmp_char == 2 && *current < *len)
	{
		write(1, *line + *current, 1);
		(*current)++;
	}
	else
		navigate_history(tmp_char, line, history, len_current_size);
}

char	remove_char(char tmp_char, char **line, size_t *current, size_t *len)
{
	if (tmp_char == 127)
	{
		if (*current > 0)
		{
			remove_char_at_pos(*line, *current, *len);
			(*len)--;
			(*current)--;
		}
		return (1);
	}
	return (0);
}

void	read_chars(char **env, t_linked_list *history, char **line,
											size_t len_current_size[])
{
	char		tmp_char;
	size_t		*len;
	size_t		*current;
	size_t		*size;

	len = &(len_current_size[0]);
	current = &(len_current_size[1]);
	size = &(len_current_size[2]);
	while ((tmp_char = (char)getch()) != '\n')
	{
		if (!cursor_stuff_one(tmp_char, line, len_current_size, env)
			&& !remove_char(tmp_char, line, current, len))
		{
			if (tmp_char == 27)
				arrows_management(line, history, len_current_size);
			else
			{
				if (*len == *size)
					*line = double_size(*line, size);
				add_char_at_pos(*line, *current, *len, tmp_char);
				(*len)++;
				(*current)++;
			}
		}
	}
}

char	*get_input(char **env, t_linked_list *history)
{
	char	*line;
	size_t	len_current_size[4];

	if (!(line = (char*)malloc(sizeof(char) * 6)))
		malloc_error();
	line[0] = '\0';
	len_current_size[0] = 0;
	len_current_size[1] = 0;
	len_current_size[2] = 5;
	len_current_size[3] = history->len;
	read_chars(env, history, &line, len_current_size);
	if (len_current_size[0] == len_current_size[2])
		line = double_size(line, &(len_current_size[2]));
	line[len_current_size[0]] = '\0';
	free(history->elts[history->len - 1]);
	if (history->len == 1 || ft_strcmp(history->elts[history->len - 2], line) != 0)
		history->elts[history->len - 1] = ft_strdup(line);
	else
		history->len--;
	write(1, "\n", 1);
	return (line);
}

size_t	ptrptrlen(void **ptrptr)
{
	size_t	i;

	i = 0;
	while (ptrptr[i])
		i++;
	return (i);
}

void	free_ptrptr(void **ptrptr)
{
	size_t	i;

	i = 0;
	while (ptrptr[i])
	{
		free(ptrptr[i]);
		i++;
	}
	free(ptrptr);
}

char	**copy_environ(void)
{
	size_t	len;
	char	**env;
	size_t	str_len;
	size_t	i;
	size_t	x;

	len = ptrptrlen((void**)environ);
	if (!(env = (char**)malloc(sizeof(char*) * (len + 1))))
		malloc_error();
	env[len] = NULL;
	i = 0;
	while (i < len)
	{
		str_len = ft_strlen(environ[i]);
		if (!(env[i] = (char*)malloc(sizeof(char) * (str_len + 1))))
			malloc_error();
		env[i][str_len] = '\0';
		x = 0;
		while (x < str_len)
		{
			env[i][x] = environ[i][x];
			x++;
		}
		i++;
	}
	return (env);
}

void	reload_env(char ***old_env)
{
	if (*old_env)
		free_ptrptr((void**)*old_env);
	*old_env = copy_environ();
}

void	print_strstr(char **strstr)
{
	size_t	i;

	i = 0;
	while (strstr[i])
	{
		ft_putstr(strstr[i]);
		ft_putstr("\n");
		i++;
	}
}

char	ignore_char(char c)
{
	if (c == ' ' || (c <= 31 && c >= 0) || c >= 127)
		return (1);
	return (0);
}

void	add_string_to_args2(char *command, char *to_add, t_vars *vars, char *in_str)
{
	if (!(command[vars->start + vars->x] == '"' || command[vars->start + vars->x] == '\''))
	{
		to_add[vars->i] = command[vars->start + vars->x];
		vars->i++;
	}
	else
	{
		if (!*in_str)
			*in_str = command[vars->start + vars->x];
		else
		{
			if (command[vars->start + vars->x] == *in_str)
				*in_str = 0;
			else
			{
				to_add[vars->i] = command[vars->start + vars->x];
				vars->i++;
			}
		}
	}
}

void	add_string_to_args(t_linked_list *args, char *command, size_t start, size_t end)
{
	char	*to_add;
	t_vars	vars;
	char	in_str;

	vars.start = start;
	in_str = 0;
	if (!(to_add = (char*)malloc(sizeof(char) * (end - vars.start + 1))))
		malloc_error();
	vars.i = 0;
	vars.x = 0;
	while (vars.x < end - vars.start)
	{
		if (command[vars.start + vars.x] == '\\')
		{
			to_add[vars.i] = command[vars.start + vars.x + 1];
			vars.x++;
			vars.i++;
		}
		else
			add_string_to_args2(command, to_add, &vars, &in_str);
		vars.x++;
	}
	to_add[vars.i] = '\0';
	add_to_list(args, to_add);
}

char	escaped_char(char *str, int i)
{
	int		nb;

	nb = 0;
	i--;
	while (i >= 0)
	{
		if (str[i] == '\\')
			nb++;
		else
			break ;
		i--;
	}
	if (nb % 2 == 1)
		return (1);
	return (0);
}

void	handle_quote(t_linked_list *args, char *command, t_ind *ind, char *in_str)
{
	if (*in_str)
	{
		if (*in_str == command[ind->i])
		{
			if (!escaped_char(command, ind->i))
			{
				*in_str = 0;
				if (ignore_char(command[ind->i + 1]))
				{
					add_string_to_args(args, command, ind->start, ind->i);
					ind->start = ind->i + 1;
				}
			}
		}
	}
	else
		*in_str = command[ind->i];
}

char	**list_to_args(t_linked_list *args)
{
	char	**res;
	int		i;

	if (!(res = (char**)malloc(sizeof(char*) * (args->len + 1))))
		malloc_error();
	res[args->len] = NULL;
	i = 0;
	while (i < args->len)
	{
		res[i] = args->elts[i];
		i++;
	}
	free(args->elts);
	free(args);
	return (res);
}

void	split_command_in_args2(char *command, t_linked_list *args, t_ind *ind, char *in_str)
{
	if (!*in_str && (ignore_char(command[ind->i]) || command[ind->i] == ';'))
	{
		if (ind->start != ind->i)
			add_string_to_args(args, command, ind->start, ind->i);
		if (command[ind->i] == ';')
			add_to_list(args, ft_strdup(";"));
		ind->start = ind->i + 1;
	}
	else if (command[ind->i] == '"' || command[ind->i] == '\'')
		handle_quote(args, command, ind, in_str);
}

char	**split_command_in_args(char *command)
{
	t_linked_list	*args;
	t_ind			ind;
	char			in_str;

	args = new_list();
	ind.i = 0;
	while (command[ind.i] && ignore_char(command[ind.i]))
		ind.i++;
	if (!command[ind.i])
		return (NULL);
	ind.start = ind.i;
	in_str = 0;
	while (command[ind.i])
	{
		split_command_in_args2(command, args, &ind, &in_str);
		ind.i++;
	}
	if (ind.start != ind.i)
		add_string_to_args(args, command, ind.start, ind.i);
	return (list_to_args(args));
}

char	startswith(char *str, char *env)
{
	size_t	i;

	i = 0;
	while (str[i] && env[i])
	{
		if (str[i] != env[i])
			return (0);
		i++;
	}
	if (env[i] == '=')
		return (1);
	return (0);
}

char	*build_env_var(char *part1, char *part2)
{
	size_t	len1;
	size_t	len2;
	char	*res;

	len1 = ft_strlen(part1);
	len2 = ft_strlen(part2);
	if (!(res = (char*)malloc(sizeof(char) * (len1 + len2 + 2))))
		malloc_error();
	res[len1 + len2 + 1] = '\0';
	len1 = 0;
	while (part1[len1])
	{
		res[len1] = part1[len1];
		len1++;
	}
	res[len1] = '=';
	len2 = 0;
	while (part2[len2])
	{
		res[len1 + 1 + len2] = part2[len2];
		len2++;
	}
	return (res);
}

char	set_env2(char **new_env, char **line, char ***env, size_t i)
{
	char	done;

	done = 0;
	if (startswith(line[1], (*env)[i]))
	{
		new_env[i] = build_env_var(line[1], line[2]);
		done = 1;
	}
	else
		new_env[i] = (*env)[i];
	return (done);
}

void	set_env(char **line, char ***env)
{
	char	**new_env;
	size_t	len;
	size_t	i;
	char 	done;

	done = 0;
	len = strstrlen(*env);
	if (!(new_env = (char**)malloc(sizeof(char*) * (len + 2))))
		malloc_error();
	new_env[len + 1] = NULL;
	i = 0;
	while ((*env)[i])
	{
		if (set_env2(new_env, line, env, i))
			done = 1;
		i++;
	}
	new_env[i] = NULL;
	if (!done)
		new_env[i] = build_env_var(line[1], line[2]);
	free(*env);
	*env = new_env;
}

char	get_found(char **line, char ***env, size_t *i)
{
	char	found;

	found = 0;
	*i = 0;
	while ((*env)[*i])
	{
		if (startswith(line[1], (*env)[*i]))
			found = 1;
		(*i)++;
	}
	return (found);
}

void	unset_env(char **line, char ***env)
{
	size_t	i;
	char	found;
	char	**new_env;

	found = get_found(line, env, &i);
	if (!found)
		return ;
	if (!(new_env = (char**)malloc(sizeof(char*) * i)))
		malloc_error();
	new_env[i - 1] = NULL;
	i = 0;
	found = 0;
	while ((*env)[i])
	{
		if (!(startswith(line[1], (*env)[i])))
			new_env[i - found] = (*env)[i];
		else
			found = 1;
		i++;
	}
	free(*env);
	*env = new_env;
}

char	*get_home(char **env)
{
	size_t	i;

	i = 0;
	while (env[i])
	{
		if (env[i][0] == 'H' && env[i][1] == 'O' && env[i][2] == 'M'
			&& env[i][3] == 'E' && env[i][4] == '=')
			return (ft_strdup(env[i] + 5));
		i++;
	}
	return (ft_strdup("/"));
}

void	set_old_pwd(char ***env)
{
	char	*path;
	char	**line;

	path = get_current_path();
	if (!(line = (char**)malloc(sizeof(char*) * 4)))
		malloc_error();
	line[3] = NULL;
	line[0] = ft_strdup("env");
	line[1] = ft_strdup("OLDPWD");
	line[2] = path;
	set_env(line, env);
	free(line[0]);
	free(line[1]);
	free(line[2]);
	free(line);
}

void	set_new_pwd(char ***env)
{
	char	*path;
	char	**line;

	path = get_current_path();
	if (!(line = (char**)malloc(sizeof(char*) * 4)))
		malloc_error();
	line[3] = NULL;
	line[0] = ft_strdup("env");
	line[1] = ft_strdup("PWD");
	line[2] = path;
	set_env(line, env);
	free(line[0]);
	free(line[1]);
	free(line[2]);
	free(line);
}

void	change_dir(char *dir_path, char ***env)
{
	struct stat	file;

	if (stat(dir_path, &file) == -1)
	{
		ft_putstr("minishell: ");
		ft_putstr(dir_path);
		ft_putstr(": No such file or directory\n");
	}
	else if (S_ISDIR(file.st_mode))
	{
		set_old_pwd(env);
		chdir(dir_path);
		set_new_pwd(env);
	}
	else
	{
		ft_putstr("minishell: ");
		ft_putstr(dir_path);
		ft_putstr(": Not a directory\n");
	}
}

void	handle_builtin(char **line, char ***env)
{
	if (ft_strcmp(line[0], "env") == 0)
		print_strstr(*env);
	else if (ft_strcmp(line[0], "setenv") == 0 && line[1]
		&& line[2] && !char_in_str(line[1], '='))
		set_env(line, env);
	else if (ft_strcmp(line[0], "unsetenv") == 0 && line[1]
		&& !char_in_str(line[1], '='))
		unset_env(line, env);
	else if (ft_strcmp(line[0], "exit") == 0)
	{
		ft_putstr("bye\n");
		exit(0);
	}
	else if (ft_strcmp(line[0], "cd") == 0)
	{
		if (!line[1])
			change_dir(get_home(*env), env);
		else
			change_dir(line[1], env);
	}
}

char	*replace_tilde_str(char *home, size_t home_len, char *line)
{
	size_t	line_len;
	size_t	i;
	char	*res;

	line_len = ft_strlen(line) - 1;
	if (!(res = (char*)malloc(sizeof(char) * (home_len + line_len + 1))))
		malloc_error();
	res[home_len + line_len] = '\0';
	i = 0;
	while (home[i])
	{
		res[i] = home[i];
		i++;
	}
	line_len = 1;
	while (line[line_len])
	{
		res[i + line_len - 1] = line[line_len];
		line_len++;
	}
	return (res);
}

void	handle_dollar(char **line, size_t i, char **env)
{
	char	*value;

	value = get_env_var(line[i] + 1, env);
	if (!value)
		return ;
	free(line[i]);
	line[i] = value;
}

void	replace_tilde(char **line, char **env)
{
	size_t	i;
	char	*tmp;
	char	*home;
	size_t	len;

	home = get_env_var("HOME", env);
	if (!home)
		return ;
	len = ft_strlen(home);
	if (home[len - 1] == '/')
		home[len - 1] = '\0';
	i = 0;
	while (line[i])
	{
		if (line[i][0] == '~' && (!line[i][1] || line[i][1] == '/'))
		{
			tmp = replace_tilde_str(home, len, line[i]);
			free(line[i]);
			line[i] = tmp;
		}
		else if (line[i][0] == '$')
			handle_dollar(line, i, env);
		i++;
	}
}

void	ctrl_c(int id)
{
	(void)id;
	ft_putstr("\n");
}

size_t	count_elts(char **elts)
{
	size_t	i;

	i = 0;
	while (elts[i] && ft_strcmp(elts[i], ";") != 0)
		i++;
	return (i);
}

char	***split_in_commands2(char ***commands, char **line, size_t count, size_t i)
{
	size_t	ind;
	size_t	x;
	size_t	count2;

	ind = 0;
	x = 0;
	while (ind < count + 1)
	{
		count2 = count_elts(line + x);
		if (!(commands[ind] = (char**)malloc(sizeof(char*) * (count2 + 1))))
			malloc_error();
		commands[ind][count2] = NULL;
		i = 0;
		while (i < count2)
		{
			commands[ind][i] = line[x];
			x++;
			i++;
		}
		x++;
		ind++;
	}
	return (commands);
}

char	***split_in_commands(char **line)
{
	size_t	i;
	int		count;
	char	***commands;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (ft_strcmp(line[i], ";") == 0)
			count++;
		i++;
	}
	if (!(commands = (char***)malloc(sizeof(char**) * (count + 2))))
		malloc_error();
	commands[count + 1] = NULL;
	return (split_in_commands2(commands, line, count, 0));
}

void	print_commands(char ***commands)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (commands[y])
	{
		ft_putstr("NEW INSTR\n\n");
		x = 0;
		while (commands[y][x])
		{
			ft_putstr(commands[y][x]);
			ft_putstr("|\n");
			x++;
		}
		y++;
	}
}

void	launch_command(char **line, char ***env, char *executable, pid_t id)
{
	if (ft_strcmp(line[0], "env") == 0 || ft_strcmp(line[0], "setenv") == 0
		|| ft_strcmp(line[0], "cd") == 0 || ft_strcmp(line[0], "unsetenv") == 0
		|| ft_strcmp(line[0], "exit") == 0)
	{
		handle_builtin(line, env);
		return ;
	}
	executable = find_executable(line[0], *env);
	if (!executable)
		return ;
	id = fork();
	if (id > 0)
		wait(NULL);
	if (id == 0)
	{
		if (execve(executable, line, *env) == -1)
		{
			ft_putstr("minishell: ");
			ft_putstr(line[0]);
			ft_putstr(": can't be executed.\n");
		}
		exit(0);
	}
}

void	treat_command(char *command, char ***env)
{
	char	**line;
	char	***commands;
	size_t	i;

	line = split_command_in_args(command);
	if (!line)
		return ;
	commands = split_in_commands(line);
	i = 0;
	while ((line = commands[i]))
	{
		if (line && line[0])
		{
			replace_tilde(line, *env);
			launch_command(line, env, NULL, 0);	
		}
		i++;
	}
	free(command);
}

void	launch_shell(void)
{
	char			**env;
	t_linked_list	*history;

	history = new_list();
	signal(SIGINT, ctrl_c);
	env = copy_environ();
	while (1)
	{
		print_prompt(env);
		add_to_list(history, ft_strdup(""));
		treat_command(get_input(env, history), &env);
	}
	free_ptrptr((void**)*env);
}

void	display_help(void)
{
	ft_putstr("  __ Welcome to the minishell __\n\n");
	ft_putstr("  builtins :\n");
	ft_putstr("    - env\n");
	ft_putstr("    - setenv\n");
	ft_putstr("    - unsetenv\n");
	ft_putstr("    - cd\n");
	ft_putstr("    - exit\n");
	ft_putstr("    - $<ENV_VAR>\n\n");
	ft_putstr("  special features :\n");
	ft_putstr("    - autocompletion\n");
	ft_putstr("    - line edition\n");
	ft_putstr("    - command history\n");
	ft_putstr("    - tilde\n");
	ft_putstr("    - go to start/end of line\n");
	ft_putstr("    - complex strings support\n");
	ft_putstr("    ...some more stuff...\n");
}

int		main(int argc, char **argv)
{
	if (argc == 2 && ft_strcmp(argv[1], "-h") == 0)
		display_help();
	else
		launch_shell();
	return (0);
}
