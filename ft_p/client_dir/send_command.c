

#include "ft_p_client.h"

char	send_raw_command(int server, char type, char *command)
{
	t_packet_header	*header;
	unsigned char	*to_send;
	uint32_t		size;

	size = (sizeof(char) * ft_strlen(command)) + sizeof(t_packet_header);
	if (!(to_send = (unsigned char*)malloc(size)))
	{
		ft_putstr("malloc error\n");
		return (0);
	}
	header = (t_packet_header*)to_send;
	header->type = type;
	header->tot_data_len = htonl(size);
	ft_strcat((char*)to_send, command, sizeof(t_packet_header),
														ft_strlen(command));
	write(server, to_send, size);
	return (1);
}

char	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\r' || c == '\f');
}

char	command_is(char *command, char *is)
{
	int		i;

	i = 0;
	while (command[i] && is[i] && command[i] == is[i])
		i++;
	return ((size_t)i == ft_strlen(is) && is_space(command[i]));
}

char	send_put_command(int server, char *command)
{
	int				fd;
	int				i;
	char			*buffer;
	struct stat		st;
	t_packet_header	*header;
	int				ret;
	int				file_start_at;
	int				already_read;

	if (command[ft_strlen(command) - 1] == '\n')
		command[ft_strlen(command) - 1] = '\0';
	i = 3;
	while (is_space(command[i]))
		i++;
	if ((fd = open(command + i, O_RDONLY)) == -1)
	{
		ft_putstr("could not open file\n");
		return (0);
	}
	if (!(buffer = (char*)malloc(sizeof(char) * READ_BUFF_LEN)))
	{
		ft_putstr("malloc error\n");
		return (0);
	}
	if (fstat(fd, &st) == -1)
	{
		ft_putstr("fstat failed\n");
		return (0);
	}
	ft_strcpy(buffer + sizeof(t_packet_header), command + i,
												ft_strlen(command + i) + 1);
	file_start_at = sizeof(t_packet_header) + ft_strlen(command + i) + 1;
	if ((ret = read(fd, buffer + file_start_at, READ_BUFF_LEN
													- file_start_at)) == -1)
	{
		ft_putstr("read failed\n");
		return (0);
	}
	header = (t_packet_header*)buffer;
	header->type = CMD_PUT;
	header->tot_data_len = htonl(file_start_at + st.st_size);
	write(server, buffer, file_start_at + ret);
	already_read = ret;
	while ((ret = read(fd, buffer, READ_BUFF_LEN)) > 0)
	{
		already_read += ret;
		write(server, buffer, ret);
	}
	if (ret == -1)
	{
		ft_putstr("read error\n");
		return (0);
	}
	if (already_read != st.st_size)
	{
		ft_putstr("weird size error\n");
		return (0);
	}
	return (1);
}

char	send_command(int server, t_options *options, char *command)
{
	(void)options;
	if (command_is(command, "put"))
		return (send_put_command(server, command));
	else
		return (send_raw_command(server, CMD_RAW_COMMAND, command));
}