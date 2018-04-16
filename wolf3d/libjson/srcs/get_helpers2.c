

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