

#include "ft_p_client.h"

char	return_get_error(char *error)
{
	ft_putstr(error);
	return (0);
}

char	find_start_of_file(int server, char **data,
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
	ret = read(server, buffer, 511);
	if (ret == -1 || (size_t)*len > header->tot_data_len)
		return (return_get_error("read error"));
	buffer[ret] = '\0';
	if (!(*data = ft_strconcat(*data, buffer, *len, ret + 1)))
		return (return_get_error("malloc error"));
	*len += ret;
	return (find_start_of_file(server, data, len, start_of_file));
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

char	get_file2(int server, int fd, int to_read_len)
{
	char	*buffer;
	int		ret;

	if (!(buffer = (char*)malloc(sizeof(char) * READ_BUFF_LEN)))
		return (return_get_error("malloc error"));
	while ((ret = read(server, buffer, READ_BUFF_LEN)) > 0)
	{
		to_read_len -= ret;
		if (to_read_len < 0)
			return (return_get_error("weird size error"));
		write(fd, buffer, ret);
		if (to_read_len == 0)
			break ;
	}
	close(fd);
	if (ret == -1)
		return (return_get_error("read error"));
	return (1);
}

char	get_file(int server, char *data_filename_file[3], int file_len)
{
	t_packet_header	*header;
	char	*data;
	char	*file;
	int		fd;
	int		to_read_len;

	data = data_filename_file[0];
	file = data_filename_file[2];
	header = (t_packet_header*)data;
	to_read_len = header->tot_data_len - (file - data) - file_len;
	if ((fd = open(data_filename_file[1], O_CREAT | O_RDWR, 0644)) == -1)
		return (return_get_error("could not open res file"));
	if (file_len > 0)
		write(fd, file, file_len);
	if (to_read_len < 0)
		return (return_get_error("weird size error"));
	if (to_read_len > 0)
		return (get_file2(server, fd, to_read_len));
	close(fd);
	return (1);
}

void	handle_get(int server, char *data, int len)
{
	char	*start_of_file;
	char	*filename;
	char	*res_filename;
	char	*data_filename_file[3];

	start_of_file = NULL;
	if (!(find_start_of_file(server, &data, &len, &start_of_file)))
		return ;
	filename = data + sizeof(t_packet_header);
	res_filename = make_res_filename(filename);
	data_filename_file[0] = data;
	data_filename_file[1] = res_filename;
	data_filename_file[2] = start_of_file;
	if (get_file(server, data_filename_file, len - (start_of_file - data)))
		ft_putstr("file saved\nSUCCESS\n");
	else
		ft_putstr("\nERROR\n");
}