

#include "ft_p_server.h"


char	handle_raw_command(t_client_data *client, t_options *options,
											unsigned char *data, int len)
{
	char			*command;
	wordexp_t		cmd_and_args;

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

int		ind_of_char(char *str, char c, int len)
{
	int		i;

	i = 0;
	while (i < len)
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	find_start_of_file(t_client_data *client, unsigned char **data,
											int *len, char **start_of_file)
{
	t_packet_header	*header;
	int				ind;
	char			buffer[512];
	int				ret;

	header = (t_packet_header*)data;
	if ((ind = ind_of_char(*data + sizeof(t_packet_header), '\0',
			*len - sizeof(t_packet_header))) != -1)
	{
		*start_of_file = sizeof(t_packet_header) + ind + 1;
		return (1);
	}
	ret = read(client->fd, buffer, 511);
	if (ret == -1 || *len > header->tot_data_len)
	{
		ft_client_error(client, "read error");
		return (0);
	}
	buffer[ret] = '\0';
	if (!(*data = ft_strconcat((char*)*data, buffer, *len, ret + 1)))
	{
		ft_client_error(client, "malloc error");
		return (0);
	}
	*len += ret;
	return (find_start_of_file(client, data, len, start_of_file));
}

void	handle_put(t_client_data *client, t_options *options,
											unsigned char *data, int len)
{
	char	*start_of_file;
	char	*filename;
	char	*res_filename;

	(void)options;
	start_of_file = NULL;
	if (!(find_start_of_file(client, &data, &len, &start_of_file)))
		return ;
	filename = data + sizeof(t_packet_header);
	res_filename = make_res_filename(filename);
	put_file(client, start_of_file, len - (start_of_file - data),
															res_filename);
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