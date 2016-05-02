

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

// "ls"cat  is reduced to -> lscat
char	**split_command_in_args(char *command)
{
	t_linked_list	*args;
	size_t			i;
	size_t			start;
	char			in_str;

	args = new_list();
	i = 0;
	while (command[i] && ignore_char(command[i]))
		i++;
	if (!command[i])
		return (NULL);
	start = i;
	in_str = 0;
	while (command[i])
	{
		if ()
		i++;
	}
}

void	treat_command(char *command, char **env)
{
	pid_t	id;
	char	**line;
	char	*executable;
	//print_strstr(env);
	(void)env;
	ft_putstr(command);
	ft_putstr("\n");
	line = split_command_in_args(command);
	if (!line)
		return ;
	print_strstr(line);
	//executable = find_executable(line[0], env);
	id = fork();
	if (id > 0)
	{
		wait();
		ft_putstr("FATHER\n");
	}
	if (id == 0)
	{
		execve("/bin/ls", line, NULL);
	}
	free(command);
}

void	launch_shell(void)
{
	char	**env;

	env = NULL;
	while (1)
	{
		reload_env(&env);
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