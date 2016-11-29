

#include "ft_p_server.h"

char	ret_client_error(t_client_data *client, char *msg)
{
	ft_client_error(client, msg);
	return (0);
}

char	complete_command(t_client_data *client, unsigned char **data,
											int *len, uint32_t cmd_len)
{
	unsigned char	*tmp_data;
	unsigned char	*new_data;
	int				ret;
	int				i;

	if (!(tmp_data = (unsigned char*)malloc(READ_BUFF_LEN)))
		return (ret_client_error(client, "malloc failed"));
	i = 0;
	while ((ret = read(client->fd, (void*)tmp_data, READ_BUFF_LEN - 1)) > 0)
	{
		tmp_data[ret] = '\0';
		if (!(new_data = (unsigned char*)ft_strconcat((char*)*data,
											(char*)tmp_data, *len, ret + 1)))
			return (ret_client_error(client, "malloc failed"));
		if (i > 0)
			free(*data);
		*data = new_data;
		*len += ret;
		if (((size_t)*len) > cmd_len)
			return (ret_client_error(client, "weird size error"));
		if ((size_t)(*len) == cmd_len)
			break ;
		i++;
	}
	free(tmp_data);
	if (ret == -1)
		return (ret_client_error(client, "read failed"));
	return (1);
}