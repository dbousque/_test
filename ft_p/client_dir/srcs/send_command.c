/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 16:28:58 by dbousque          #+#    #+#             */
/*   Updated: 2016/12/08 16:55:16 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	send_put_command2(int server, char *buffer, char *command_plus_i,
																		int fd)
{
	int				file_sta;
	int				already_read;
	t_packet_header	*header;
	struct stat		st;
	int				ret;

	if (fstat(fd, &st) == -1)
		return (return_error("fstat failed\n"));
	file_sta = sizeof(t_packet_header) + ft_strlen(command_plus_i) + 1;
	if ((ret = read(fd, buffer + file_sta, READ_BUFF_LEN - file_sta)) == -1)
		return (return_error("read failed\n"));
	header = (t_packet_header*)buffer;
	header->type = CMD_PUT;
	header->tot_data_len = htonl(file_sta + st.st_size);
	write(server, buffer, file_sta + ret);
	already_read = ret;
	while ((ret = read(fd, buffer, READ_BUFF_LEN)) > 0)
	{
		already_read += ret;
		write(server, buffer, ret);
	}
	if (ret == -1 || already_read != st.st_size)
		return (return_error("read error\n"));
	return (1);
}

char	send_put_command(int server, char *command)
{
	int		fd;
	int		i;
	char	*buffer;

	if (command[ft_strlen(command) - 1] == '\n')
		command[ft_strlen(command) - 1] = '\0';
	i = 3;
	while (is_space(command[i]))
		i++;
	if ((fd = open(command + i, O_RDONLY)) == -1)
		return (return_error("could not open file\n"));
	if (!(buffer = (char*)malloc(sizeof(char) * READ_BUFF_LEN)))
		return (return_error("malloc error\n"));
	ft_strcpy(buffer + sizeof(t_packet_header), command + i,
												ft_strlen(command + i) + 1);
	return (send_put_command2(server, buffer, command + i, fd));
}

char	send_get_command(int server, char *command)
{
	char			*to_send;
	t_packet_header	*header;
	int				tot_len;
	int				i;

	if (command[ft_strlen(command) - 1] == '\n')
		command[ft_strlen(command) - 1] = '\0';
	i = 3;
	while (is_space(command[i]))
		i++;
	tot_len = sizeof(t_packet_header)
							+ (sizeof(char) * (ft_strlen(command + i) + 1));
	if (!(to_send = (char*)malloc(tot_len)))
		return (return_error("malloc error\n"));
	header = (t_packet_header*)to_send;
	header->type = CMD_GET;
	header->tot_data_len = htonl(tot_len);
	ft_strcpy(to_send + sizeof(t_packet_header), command + i,
												ft_strlen(command + i) + 1);
	write(server, to_send, tot_len);
	free(to_send);
	return (1);
}

char	send_command(int server, t_options *options, char *command)
{
	(void)options;
	if (command_is(command, "put"))
		return (send_put_command(server, command));
	else if (command_is(command, "get"))
		return (send_get_command(server, command));
	else
		return (send_raw_command(server, CMD_RAW_COMMAND, command));
}
