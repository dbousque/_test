/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 17:13:03 by dbousque          #+#    #+#             */
/*   Updated: 2018/04/28 17:13:05 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libjson.h"

void	value_type_error(void)
{
	ft_putendl_fd("Value has wrong type.", 2);
	exit(0);
}

t_value	*get_val(t_value *dict_inp, char *key)
{
	int		i;
	t_dict	*dict;

	if (dict_inp->type != DICT)
		value_type_error();
	dict = (t_dict*)dict_inp->data;
	i = 0;
	while (dict->keys[i])
	{
		if (ft_strcmp(dict->keys[i], key) == 0)
			return (dict->values[i]);
		i++;
	}
	return (NULL);
}

t_dict	*get_dict(t_value *dict_val)
{
	if (dict_val->type != DICT)
		value_type_error();
	return ((t_dict*)dict_val->data);
}

t_value	**get_tab(t_value *value)
{
	if (value->type != ARRAY)
		value_type_error();
	return ((t_value**)value->data);
}

t_value	*get(t_value *array, int i)
{
	if (array->type != ARRAY)
		value_type_error();
	return (((t_value**)array->data)[i]);
}
