/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_helpers2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 17:13:13 by dbousque          #+#    #+#             */
/*   Updated: 2018/04/28 17:13:18 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libjson.h"

double	get_double(t_value *value)
{
	if (value->type != DOUBLE)
		value_type_error();
	return (*((double*)value->data));
}

long	get_long(t_value *value)
{
	if (value->type != LONG)
		value_type_error();
	return (*((long*)value->data));
}

char	*get_string(t_value *value)
{
	if (!value)
		return (NULL);
	if (value->type != STRING)
		value_type_error();
	return ((char*)value->data);
}

char	get_bool(t_value *value)
{
	if (value->type != BOOLEAN)
		value_type_error();
	return (*((char*)value->data));
}
