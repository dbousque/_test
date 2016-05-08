/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/08 16:06:41 by dbousque          #+#    #+#             */
/*   Updated: 2016/05/08 16:06:44 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**g_environ;

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
	ft_putstr("\n  __ Welcome to the minishell __\n\n");
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
	ft_putstr("    ...some more stuff...\n\n");
}

int		main(int argc, char **argv, char **environ)
{
	g_environ = environ;
	if (argc == 2 && ft_strcmp(argv[1], "-h") == 0)
		display_help();
	else
		launch_shell();
	return (0);
}
