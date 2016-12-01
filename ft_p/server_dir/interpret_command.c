

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
	if (put_file(client, options, data_filename_file,
												len - (start_of_file - data)))
		ft_client_success(client, "file saved", ft_strlen("file saved"));
}

void	handle_cd(t_client_data *client)
{
	(void)client;
}

char	return_client_error(t_client_data *client, char *error)
{
	ft_client_error(client, error);
	return (0);
}

char	handle_get2(t_client_data *client, char *buffer, char *filename,
																		int fd)
{
	int					file_start_at;
	int					already_read;
	t_ret_packet_header	*header;
	struct stat			st;
	int					ret;

	if (fstat(fd, &st) == -1)
		return (return_client_error(client, "fstat failed\n"));
	file_start_at = sizeof(t_ret_packet_header) + ft_strlen(filename) + 1;
	if ((ret = read(fd, buffer + file_start_at, READ_BUFF_LEN
													- file_start_at)) == -1)
		return (return_client_error(client, "read failed\n"));
	header = (t_ret_packet_header*)buffer;
	header->status = RET_SUCCESS;
	header->tot_data_len = htonl(file_start_at + st.st_size);
	write(client->fd, buffer, file_start_at + ret);
	already_read = ret;
	while ((ret = read(fd, buffer, READ_BUFF_LEN)) > 0)
	{
		already_read += ret;
		write(client->fd, buffer, ret);
	}
	if (ret == -1)
		return (return_client_error(client, "read error\n"));
	if (already_read != st.st_size)
		return (return_client_error(client, "weird size error\n"));
	return (1);
}

char	handle_get(t_client_data *client, t_options *options,
												char *data, int len)
{
	int		fd;
	char	*buffer;
	char	*start_of_file;
	char	*filename;

	(void)options;
	start_of_file = NULL;
	find_start_of_file(client, &data, &len, &start_of_file);
	filename = data + sizeof(t_ret_packet_header);
	if (ind_of_char(filename, '/', ft_strlen(filename)) != -1)
		return (return_client_error(client,
										"file must be in current directory"));
	if ((fd = open(filename, O_RDONLY)) == -1)
		return (return_client_error(client, "could not open file"));
	if (!(buffer = (char*)malloc(sizeof(char) * READ_BUFF_LEN)))
		return (return_client_error(client, "malloc error"));
	ft_strcpy2(buffer + sizeof(t_ret_packet_header), filename,
												ft_strlen(filename) + 1);
	return (handle_get2(client, buffer, filename, fd));
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
	else if (header->type == CMD_GET)
		handle_get(client, options, (char*)data, len);
}