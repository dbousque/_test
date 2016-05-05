

#include "minishell.h"

extern char	**environ;

void	print_prompt(void)
{
	ft_putstr("$> ");
}

void	malloc_error(void)
{
	ft_putstr("Could not allocate memory.\n");
	exit(1);
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
		if (command[start + x] == '\\' && (command[start + x + 1] == '"'
			|| command[start + x + 1] == '\'' || command[start + x + 1] == '\\'))
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

// "ls"cat  is reduced to -> lscat
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

void	handle_builtin(char **line, char ***env)
{
	if (ft_strcmp(line[0], "env") == 0)
		print_strstr(*env);
	else if (ft_strcmp(line[0], "setenv") == 0)
		set_env(line, env);
	else if (ft_strcmp(line[0], "unsetenv") == 0)
		unset_env(line, env);
	else if (ft_strcmp(line[0], "exit") == 0)
		exit(0);
	else if (ft_strcmp(line[0], "cd") == 0)
		change_dir(line, )
}

void	treat_command(char *command, char **env)
{
	pid_t	id;
	char	**line;
	char	*executable;

	line = split_command_in_args(command);
	if (!line)
		return ;
	if (ft_strcmp(line[0], "env") == 0 || ft_strcmp(line[0], "setenv") == 0
		|| ft_strcmp(line[0], "cd") == 0 || ft_strcmp(line[0], "unsetenv") == 0
		|| ft_strcmp(line[0], "exit") == 0)
	{
		handle_builtin(line, &env);
		return ;
	}
	executable = find_executable(line[0], env);
	if (!executable)
		return ;
	id = fork();
	if (id > 0)
		wait();
	if (id == 0)
		execve(executable, line, env);
	free(command);
}

void	launch_shell(void)
{
	char	**env;

	//env = NULL;
	//reload_env(&env);
	env = copy_environ();
	while (1)
	{
		print_prompt();
		treat_command(get_input(), env);
	}
	free_ptrptr((void**)env);
}

int		main(void)
{
	launch_shell();
	return (0);
}