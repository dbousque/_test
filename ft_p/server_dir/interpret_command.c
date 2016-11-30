

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

char	find_start_of_file(t_client_data *client, char **data,
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
		*start_of_file = *data + sizeof(t_packet_header) + ind + 1;
		return (1);
	}
	ret = read(client->fd, buffer, 511);
	if (ret == -1 || (size_t)*len > header->tot_data_len)
	{
		ft_client_error(client, "read error");
		return (0);
	}
	buffer[ret] = '\0';
	if (!(*data = ft_strconcat(*data, buffer, *len, ret + 1)))
	{
		ft_client_error(client, "malloc error");
		return (0);
	}
	*len += ret;
	return (find_start_of_file(client, data, len, start_of_file));
}

char	*make_res_filename(char *filename)
{
	int		len;
	int		i;

	len = ft_strlen(filename);
	i = len - 1;
	while (i >= 0)
	{
		if (filename[i] == '/')
		{
			if (i == len - 1)
				filename[i] = '\0';
			else
				return (filename + i + 1);
		}
		i--;
	}
	return (filename);
}

void	put_file(t_client_data *client, t_options *options,
									char *data_filename_file[3], int file_len)
{
	t_packet_header	*header;
	char	*filename;
	char	*data;
	char	*file;
	int		ret;
	int		fd;
	char	*buffer;
	int		to_read_len;

	(void)options;
	if (!(buffer = (char*)malloc(sizeof(char) * READ_BUFF_LEN)))
	{
		ft_client_error(client, "malloc error");
		return ;
	}
	data = data_filename_file[0];
	filename = data_filename_file[1];
	file = data_filename_file[2];
	header = (t_packet_header*)data;
	to_read_len = header->tot_data_len - (file - data) - file_len;
	if ((fd = open(filename, O_CREAT | O_RDWR, 0644)) == -1)
	{
		ft_client_error(client, "could not open res file");
		return ;
	}
	if (file_len > 0)
		write(fd, file, file_len);
	if (to_read_len < 0)
	{
		ft_client_error(client, "weird size error");
			return ;
	}
	if (to_read_len > 0)
	{
		while ((ret = read(client->fd, buffer, READ_BUFF_LEN)) > 0)
		{
			to_read_len -= ret;
			if (to_read_len < 0)
			{
				ft_client_error(client, "weird size error");
				return ;
			}
			write(fd, buffer, ret);
			if (to_read_len == 0)
				break ;
		}
		if (ret == -1)
		{
			ft_client_error(client, "read error");
			return ;
		}
	}
	close(fd);
	ft_client_success(client, "file saved", ft_strlen("file saved"));
}

void	handle_put(t_client_data *client, t_options *options,
											char *data, int len)
{
	char	*start_of_file;
	char	*filename;
	char	*res_filename;
	char	*data_filename_file[3];

	(void)options;
	start_of_file = NULL;
	if (!(find_start_of_file(client, &data, &len, &start_of_file)))
		return ;
	filename = data + sizeof(t_packet_header);
	res_filename = make_res_filename(filename);
	data_filename_file[0] = data;
	data_filename_file[1] = res_filename;
	data_filename_file[2] = start_of_file;
	put_file(client, options, data_filename_file,
												len - (start_of_file - data));
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