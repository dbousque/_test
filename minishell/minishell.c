

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

char	*get_current_dir(void)
{
	char	*path;
	size_t	size;
	char	*res;
	size_t	i;

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
	ft_putstr(current_dir);
	free(current_dir);
	ft_putstr("$> ");
}

char	*get_input(void)
{
	char	*line;

	get_next_line(0, &line);
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
	if (c == ' ' || c <= 31 || c >= 127)
		return (1);
	return (0);
}

void	add_string_to_args(t_linked_list *args, char *command, size_t start, size_t end)
{
	char	*to_add;
	size_t	i;
	size_t	x;
	char	in_str;

	in_str = 0;
	if (!(to_add = (char*)malloc(sizeof(char) * (end - start + 1))))
		malloc_error();
	i = 0;
	x = 0;
	while (x < end - start)
	{
		if (command[start + x] == '\\')
		{
			to_add[i] = command[start + x + 1];
			x++;
			i++;
		}
		else if (!(command[start + x] == '"' || command[start + x] == '\''))
		{
			to_add[i] = command[start + x];
			i++;
		}
		else
		{
			if (!in_str)
				in_str = command[start + x];
			else
			{
				if (command[start + x] == in_str)
					in_str = 0;
				else
				{
					to_add[i] = command[start + x];
					i++;
				}
			}
		}
		x++;
	}
	to_add[i] = '\0';
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

typedef struct	s_ind
{
	size_t		start;
	size_t		i;
}				t_ind;

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
		if (!in_str && ignore_char(command[ind.i]))
		{
			if (ind.start != ind.i)
				add_string_to_args(args, command, ind.start, ind.i);
			ind.start = ind.i + 1;
		}
		else if (command[ind.i] == '"' || command[ind.i] == '\'')
			handle_quote(args, command, &ind, &in_str);
		ind.i++;
	}
	if (ind.start != ind.i)
		add_string_to_args(args, command, ind.start, ind.i);
	return (list_to_args(args));
}

size_t	strstrlen(char **env)
{
	size_t	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
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
		if (startswith(line[1], (*env)[i]))
		{
			new_env[i] = build_env_var(line[1], line[2]);
			done = 1;
		}
		else
			new_env[i] = (*env)[i];
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

void	change_dir(char *dir_path)
{
	struct stat	file;

	if (stat(dir_path, &file) == -1)
	{
		ft_putstr("minishell: ");
		ft_putstr(dir_path);
		ft_putstr(": No such file or directory\n");
	}
	else if (S_ISDIR(file.st_mode))
		chdir(dir_path);
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
		exit(0);
	else if (ft_strcmp(line[0], "cd") == 0)
	{
		if (!line[1])
			change_dir(get_home(*env));
		else
			change_dir(line[1]);
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
		i++;
	}
}

void	ctrl_c(int id)
{
	(void)id;
	ft_putstr("\n");
}

void	treat_command(char *command, char ***env)
{
	pid_t	id;
	char	**line;
	char	*executable;

	line = split_command_in_args(command);
	if (!line)
		return ;
	replace_tilde(line, *env);
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
		execve(executable, line, *env);
		exit(0);
	}
	free(command);
}

void	launch_shell(void)
{
	char	**env;

	//env = NULL;
	//reload_env(&env);
	signal(SIGINT, ctrl_c);
	env = copy_environ();
	while (1)
	{
		print_prompt(env);
		treat_command(get_input(), &env);
	}
	free_ptrptr((void**)*env);
}

int		main(void)
{
	launch_shell();
	return (0);
}