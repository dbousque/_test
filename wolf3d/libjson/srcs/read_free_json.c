/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_free_json.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 17:14:24 by dbousque          #+#    #+#             */
/*   Updated: 2018/04/28 17:14:26 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libjson.h"

void	free_dict(t_value *value)
{
	int		i;

	i = 0;
	while (((t_dict*)value->data)->keys[i])
	{
		free(((t_dict*)value->data)->keys[i]);
		free_value(((t_dict*)value->data)->values[i]);
		i++;
	}
	free(((t_dict*)value->data)->keys);
	free(((t_dict*)value->data)->values);
}

void	free_value(t_value *value)
{
	int		i;

	if (value == (void*)DELETED_VALUE)
		return ;
	if (value->type == ARRAY)
	{
		i = 0;
		while (((t_value**)value->data)[i])
		{
			free_value(((t_value**)value->data)[i]);
			i++;
		}
	}
	else if (value->type == DICT)
		free_dict(value);
	free(value->data);
	free(value);
}

t_value	*read_json(char *filename, int max_size)
{
	char	*buf;
	t_value	*json;
	int		i;
	char	err;
	int		file_size;

	i = 0;
	buf = read_whole_file(filename, &err, max_size, &file_size);
	if (err == 1)
		return (open_failed());
	if (err == 2)
		malloc_error();
	if (err == 3)
		return (max_size_exceeded(filename, max_size));
	if (!buf)
		return (NULL);
	json = handle_buf(buf, &i);
	free(buf);
	return (json);
}

t_value	*read_json_str(char *content)
{
	t_value	*json;
	int		i;

	i = 0;
	json = handle_buf(content, &i);
	return (json);
}
