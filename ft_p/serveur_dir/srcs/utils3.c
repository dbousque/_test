/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 15:55:38 by dbousque          #+#    #+#             */
/*   Updated: 2016/12/08 16:03:16 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	char	*to_ret;
	char	*expl;
	int		i;
	int		x;

	expl = "An error occured : ";
	if (!(to_ret = (char*)malloc(sizeof(char)
									* (ft_strlen(expl) + ft_strlen(msg) + 1))))
		return (ft_putstr("malloc error\n"));
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
	ft_respond_to_client(client, RET_SUCCESS, msg, len);
}

void	redirect_output(int link[2])
{
	close(link[0]);
	dup2(link[1], 2);
	dup2(link[1], 1);
	dup2(link[1], 0);
	close(link[1]);
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
