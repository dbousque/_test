

#include "ft_p_server.h"

char	execute_command(t_client_data *client, t_options *options,
													wordexp_t *cmd_and_args)
{
	pid_t	pid;
	char	*executable;

	(void)options;
	pid = fork();
	if (pid < 0)
	{
		ft_client_error(client, "fork failed");
		return (0);
	}
	if (pid == 0)
	{
		executable = find_executable(cmd_and_args->we_wordv[0], client->env);
		if (!executable)
			ft_client_error(client, "command not found");
		else
		{
			dup2(client->fd, 1);
			dup2(client->fd, 2);
			if (execv(executable, cmd_and_args->we_wordv) == -1)
				ft_client_error(client, "command execution failed");
			else
				ft_client_success(client);
			free(executable);
		}
		exit(0);
	}
	else
		wait(NULL);
	return (1);
}

char	handle_raw_command(t_client_data *client, t_options *options,
											unsigned char *data, size_t len)
{
	char		*command;
	wordexp_t	cmd_and_args;

	(void)client;
	(void)options;
	(void)len;
	command = (char*)((void*)data) + sizeof(t_packet_header);
	if (wordexp(command, &cmd_and_args, 0) != 0)
	{
		ft_client_error(client, "invalid command");
		return (0);
	}
	execute_command(client, options, &cmd_and_args);
	wordfree(&cmd_and_args);
	return (1);
}

void	handle_put(t_client_data *client, t_options *options,
											unsigned char *data, size_t len)
{
	(void)client;
	(void)options;
	(void)data;
	(void)len;
}

void	handle_cd(t_client_data *client)
{
	(void)client;
}
#    include      <stdio.h>
void	interpret_command(t_client_data *client, t_options *options,
											unsigned char *data, size_t len)
{
	t_packet_header	*header;

	header = (t_packet_header*)data;
	printf("%d %lu", header->type, header->tot_data_len);
	if (header->type == CMD_RAW_COMMAND)
		handle_raw_command(client, options, data, len);
	else if (header->type == CMD_CD)
		handle_cd(client);
}