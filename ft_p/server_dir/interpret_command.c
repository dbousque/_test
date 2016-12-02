

#include "ft_p_server.h"

char	return_client_error(t_client_data *client, char *error)
{
	ft_client_error(client, error);
	return (0);
}

char	return_cd_error(t_client_data *client, char *dir, char *current_dir,
																char *error)
{
	chdir(current_dir);
	free(dir);
	free(current_dir);
	return (return_client_error(client, error));
}

char	handle_cd(t_client_data *client, t_options *options, char **args)
{
	char	*dir;
	char	*current_dir;

	(void)options;
	if (!args[1])
		return (return_client_error(client, "cd requires an argument"));
	current_dir = NULL;
	get_current_dir(&current_dir);
	if (!current_dir)
		return (return_client_error(client, "malloc error"));
	dir = args[1];
	if (chdir(dir) == -1)
		return (return_client_error(client, "bad dir"));
	get_current_dir(&dir);
	if (!dir)
		return (return_cd_error(client, dir, current_dir, "malloc error"));
	if (!ft_startswith(dir, client->launch_dir))
		return (return_cd_error(client, dir, current_dir, "no rights"));
	free(dir);
	free(current_dir);
	ft_client_success(client, "changed dir", ft_strlen("changed dir"));
	return (1);
}

char	handle_raw_command(t_client_data *client, t_options *options,
											unsigned char *data, int len)
{
	char			*command;
	wordexp_t		cmd_and_args;
	char			to_ret;

	command = (char*)((void*)data) + sizeof(t_packet_header);
	if ((size_t)len > sizeof(t_packet_header)
		&& command[len - sizeof(t_packet_header) - 1] == '\n')
		command[len - sizeof(t_packet_header) - 1] = '\0';
	if (wordexp(command, &cmd_and_args, 0) != 0)
	{
		ft_client_error(client, "invalid command");
		return (0);
	}
	to_ret = 1;
	if (ft_strcmp(cmd_and_args.we_wordv[0], "cd") == 0)
		to_ret = handle_cd(client, options, cmd_and_args.we_wordv);
	else
		execute_command(client, options, &cmd_and_args);
	wordfree(&cmd_and_args);
	return (to_ret);
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
	else if (header->type == CMD_GET)
		handle_get(client, options, (char*)data, len);
}