

#include "ft_p_server.h"

void	ft_respond_to_client(t_client_data *client, char type, char *msg,
																size_t len)
{
	char				*data;
	t_ret_packet_header	*header;
	size_t				i;

	if (!(data = (char*)malloc(sizeof(t_ret_packet_header)
										+ (sizeof(char) * len))))
	{
		ft_putstr("malloc error\n");
		return ;
	}
	header = (t_ret_packet_header*)data;
	header->status = type;
	header->tot_data_len = sizeof(t_ret_packet_header) + len;
	header->tot_data_len = htonl(header->tot_data_len);
	i = 0;
	while (i < len)
	{
		data[sizeof(t_ret_packet_header) + i] = msg[i];
		i++;
	}
	write(client->fd, data, sizeof(t_ret_packet_header) + len);
	free(data);
}

void	ft_client_error(t_client_data *client, char *msg)
{
	ft_putstr("CLIENT ERROR\n");
	char	*to_ret;
	char	*expl;
	int		i;
	int		x;

	expl = "An error occured : ";
	to_ret = (char*)malloc(sizeof(char)
									* (ft_strlen(expl) + ft_strlen(msg) + 1));
	if (!to_ret)
	{
		ft_putstr("malloc error\n");
		return ;
	}
	i = 0;
	while (expl[i])
	{
		to_ret[i] = expl[i];
		i++;
	}
	x = 0;
	while (msg[x])
	{
		to_ret[i + x] = msg[x];
		x++;
	}
	to_ret[i + x] = '\0';
	ft_respond_to_client(client, RET_ERROR, to_ret, i + x);
	free(to_ret);
}

void	ft_client_success(t_client_data *client, char *msg, size_t len)
{
	ft_putstr("CLIENT SUCCESS\n");
	ft_respond_to_client(client, RET_SUCCESS, msg, len);
}