

#include "ft_p_server.h"

void	redirect_output(int link[2])
{
	close(link[0]);
	dup2(link[1], 1);
	dup2(link[1], 0);
	close(link[1]);
}

void	execute_command2(char *executable, wordexp_t *cmd_and_args)
{
	if (execv(executable, cmd_and_args->we_wordv) == -1)
		ft_putstr("command execution failed");
}
  #    include <stdio.h>
void	handle_output_from_parent(t_client_data *client, t_options *options,
												int link[2])
{
	char	buffer[512];
	char	*output;
	int		ret;
	int		size;

	close(link[1]);
	(void)options;
	size = 0;
	if (!(output = (char*)malloc(sizeof(char))))
	{
		ft_client_error(client, "malloc error");
		return ;
	}
	output[0] = '\0';
	while ((ret = read(link[0], buffer, 511)) > 0)
	{
		buffer[ret] = '\0';
		output = ft_strconcat(output, buffer, size, ret + 1);
		if (!output)
		{
			ft_client_error(client, "malloc error");
			return ;
		}
		size += ret;
	}
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

char	execute_command(t_client_data *client, t_options *options,
													wordexp_t *cmd_and_args)
{
	pid_t	pid;
	char	*executable;
	int		link[2];

	(void)options;
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
	{
		redirect_output(link);
		executable = find_executable(cmd_and_args->we_wordv[0], client->env);
		if (!executable)
			ft_putstr("command not found");
		else
		{
			execute_command2(executable, cmd_and_args);
			free(executable);
		}
		exit(0);
	}
	else
		handle_output_from_parent(client, options, link);
	return (1);
}

char	handle_raw_command(t_client_data *client, t_options *options,
											unsigned char *data, int len)
{
	char			*command;
	wordexp_t		cmd_and_args;

	(void)client;
	(void)options;
	(void)len;
	command = (char*)((void*)data) + sizeof(t_packet_header);
	if ((size_t)len > sizeof(t_packet_header)
		&& command[len - sizeof(t_packet_header) - 1] == '\n')
		command[len - sizeof(t_packet_header) - 1] = '\0';
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
											unsigned char *data, int len)
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

void	interpret_command(t_client_data *client, t_options *options,
											unsigned char *data, int len)
{
	t_packet_header	*header;

	header = (t_packet_header*)data;
	if (header->type == CMD_RAW_COMMAND)
		handle_raw_command(client, options, data, len);
	else if (header->type == CMD_CD)
		handle_cd(client);
}