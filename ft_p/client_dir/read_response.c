

#include "ft_p_client.h"

void	handle_ret(int server, char *resp, int len,
												t_response_type *resp_type)
{
	t_ret_packet_header	*header;

	header = (t_ret_packet_header*)resp;
	if (header->status == RET_SUCCESS && resp_type->type == CMD_GET)
	{
		handle_get(server, resp, len);
		return ;
	}
	write(1, resp + sizeof(t_ret_packet_header),
										len - sizeof(t_ret_packet_header));
	ft_putstr("\n");
	if (header->status == RET_ERROR)
		ft_putstr("ERROR\n");
	else
		ft_putstr("SUCCESS\n");
}

char	complete_ret(int server, char **to_complete, int *size)
{
	t_ret_packet_header	*header;
	int					ret;
	char				*buffer;
	char				*tmp;

	if (!(buffer = (char*)malloc(sizeof(char) * READ_BUFF_LEN)))
	{
		ft_putstr("malloc error\n");
		return (0);
	}
	header = (t_ret_packet_header*)*to_complete;
	while ((ret = read(server, buffer, READ_BUFF_LEN - 1)))
	{
		buffer[ret] = '\0';
		tmp = ft_strconcat(*to_complete, buffer, *size, ret + 1);
		if (!tmp)
		{
			ft_putstr("malloc error\n");
			return (0);
		}
		free(*to_complete);
		*to_complete = tmp;
		header = (t_ret_packet_header*)*to_complete;
		*size += ret;
		if ((size_t)(*size) > header->tot_data_len)
		{
			ft_putstr("weird size error\n");
			return (0);
		}
		if ((size_t)(*size) == header->tot_data_len)
			break ;
	}
	if (ret == -1)
	{
		ft_putstr("read error\n");
		return (0);
	}
	return (1);
}

void	interpret_ret(int server, char *buffer, int ret,
												t_response_type *resp_type)
{
	t_ret_packet_header	*header;

	header = (t_ret_packet_header*)buffer;
	header->tot_data_len = ntohl(header->tot_data_len);
	if ((size_t)ret > header->tot_data_len)
	{
		ft_putstr("weird size error\nERROR\n");
		return ;
	}
	if ((size_t)ret < header->tot_data_len && resp_type->type != CMD_GET)
	{
		if (!(complete_ret(server, &buffer, &ret)))
			return ;
	}
	handle_ret(server, buffer, ret, resp_type);
}

void	read_response(int server, char type, char *filename)
{
	char			*buffer;
	int				ret;
	t_response_type	resp_type;

	resp_type.type = type;
	resp_type.filename = filename;
	if (!(buffer = (char*)malloc(sizeof(char) * READ_BUFF_LEN)))
	{
		ft_putstr("malloc error\n");
		return ;
	}
	ret = read(server, buffer, READ_BUFF_LEN - 1);
	if (ret == -1)
	{
		ft_putstr("read error\n");
		return ;
	}
	buffer[ret] = '\0';
	interpret_ret(server, buffer, ret, &resp_type);
}