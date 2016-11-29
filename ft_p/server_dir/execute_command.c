

#include "ft_p_server.h"

int		get_command_output(t_client_data *client, char **output, int *size,
																int link[2])
{
	int		ret;
	char	buffer[512];

	if (!(*output = (char*)malloc(sizeof(char))))
	{
		ft_client_error(client, "malloc error");
		return (-2);
	}
	(*output)[0] = '\0';
	while ((ret = read(link[0], buffer, 511)) > 0)
	{
		buffer[ret] = '\0';
		*output = ft_strconcat(*output, buffer, *size, ret + 1);
		if (!*output)
		{
			ft_client_error(client, "malloc error");
			return (-2);
		}
		*size += ret;
	}
	return (ret);
}

void	handle_output_from_parent(t_client_data *client, t_options *options,
												int link[2])
{
	char	*output;
	int		size;
	int		ret;

	close(link[1]);
	(void)options;
	output = NULL;
	size = 0;
	ret = get_command_output(client, &output, &size, link);
	if (ret == -2)
		return ;
	if (ret == -1)
	{
		ft_client_error(client, "read error");
		return ;
	}
	wait(NULL);
	if (ft_strcmp("command execution failed", output) == 0
		|| ft_strcmp("command not found", output) == 0)
		ft_client_error(client, output);
	else
		ft_client_success(client, output, size);
}

void	execute_command3(char *executable, wordexp_t *cmd_and_args)
{
	if (execv(executable, cmd_and_args->we_wordv) == -1)
		ft_putstr("command execution failed");
}

void	execute_command2(t_client_data *client, t_options *options,
									wordexp_t *cmd_and_args, int link[2])
{
	char	*executable;

	(void)options;
	redirect_output(link);
	executable = find_executable(cmd_and_args->we_wordv[0], client->env);
	if (!executable)
		ft_putstr("command not found");
	else
	{
		execute_command3(executable, cmd_and_args);
		free(executable);
	}
	exit(0);
}

char	execute_command(t_client_data *client, t_options *options,
													wordexp_t *cmd_and_args)
{
	pid_t	pid;
	int		link[2];

	if (pipe(link) == -1)
	{
		ft_client_error(client, "error");
		return (0);
	}
	pid = fork();
	if (pid < 0)
	{
		ft_client_error(client, "fork failed");
		return (0);
	}
	if (pid == 0)
		execute_command2(client, options, cmd_and_args, link);
	else
		handle_output_from_parent(client, options, link);
	return (1);
}