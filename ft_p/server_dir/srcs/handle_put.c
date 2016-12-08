/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_put.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 15:54:36 by dbousque          #+#    #+#             */
/*   Updated: 2016/12/08 15:56:20 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p_server.h"

char	return_put_error(t_client_data *client, char *error)
{
	ft_client_error(client, error);
	return (0);
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
		return (return_put_error(client, "read error"));
	buffer[ret] = '\0';
	if (!(*data = ft_strconcat(*data, buffer, *len, ret + 1)))
		return (return_put_error(client, "malloc error"));
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

char	put_file2(t_client_data *client, int fd, int to_read_len)
{
	char	*buffer;
	int		ret;

	if (!(buffer = (char*)malloc(sizeof(char) * READ_BUFF_LEN)))
		return (return_put_error(client, "malloc error"));
	while ((ret = read(client->fd, buffer, READ_BUFF_LEN)) > 0)
	{
		to_read_len -= ret;
		if (to_read_len < 0)
			return (return_put_error(client, "weird size error"));
		write(fd, buffer, ret);
		if (to_read_len == 0)
			break ;
	}
	close(fd);
	if (ret == -1)
		return (return_put_error(client, "read error"));
	return (1);
}

char	put_file(t_client_data *client, t_options *options,
									char *data_filename_file[3], int file_len)
{
	t_packet_header	*header;
	char			*data;
	char			*file;
	int				fd;
	int				to_read_len;

	(void)options;
	data = data_filename_file[0];
	file = data_filename_file[2];
	header = (t_packet_header*)data;
	to_read_len = header->tot_data_len - (file - data) - file_len;
	if ((fd = open(data_filename_file[1], O_CREAT | O_RDWR, 0644)) == -1)
		return (return_put_error(client, "could not open res file"));
	if (file_len > 0)
		write(fd, file, file_len);
	if (to_read_len < 0)
		return (return_put_error(client, "weird size error"));
	if (to_read_len > 0)
		return (put_file2(client, fd, to_read_len));
	close(fd);
	return (1);
}
