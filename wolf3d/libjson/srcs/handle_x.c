

#include "libjson.h"

char	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

t_value	*handle_number_end(t_value *res, char *tmp, char floating_point,
																char negative)
{
	long	res1;
	double	res2;

	if (!floating_point)
	{
		res1 = negative ? -(ft_atol(tmp)) : ft_atol(tmp);
		if (!(res->data = (void*)malloc(sizeof(long))))
			malloc_error();
		*((long*)res->data) = res1;
		res->type = LONG;
		free(tmp);
		return (res);
	}
	res2 = negative ? -(ft_atod(tmp)) : ft_atod(tmp);
	if (!(res->data = (void*)malloc(sizeof(double))))
		malloc_error();
	*((double*)res->data) = res2;
	res->type = DOUBLE;
	free(tmp);
	return (res);
}

t_value	*handle_number(char *buf, int *i)
{
	int		start;
	char	floating_point;
	char	*tmp;
	t_value	*res;
	char	negative;

	negative = 0;
	if (!(res = (t_value*)malloc(sizeof(t_value))))
		malloc_error();
	floating_point = 0;
	if (buf[*i] == '-')
	{
		negative = 1;
		(*i)++;
	}
	start = *i;
	while (buf[*i] && (is_digit(buf[*i]) || buf[*i] == '.'))
	{
		if (buf[*i] == '.')
			floating_point = 1;
		(*i)++;
	}
	if (!(tmp = (char*)malloc(sizeof(char) * (*i - start + 1))))
		malloc_error();
	tmp[*i - start] = '\0';
	ft_strncpy(tmp, buf + start, *i - start);
	return (handle_number_end(res, tmp, floating_point, negative));
}

t_value	*handle_boolean(char *buf, int *i)
{
	t_value	*res;

	if (!(res = (t_value*)malloc(sizeof(t_value))))
		malloc_error();
	if (!(res->data = (void*)malloc(sizeof(char))))
		malloc_error();
	res->type = BOOLEAN;
	if (buf[*i] == 't')
	{
		*((char*)res->data) = 1;
		*i += 4;
	}
	else
	{
		*((char*)res->data) = 0;
		*i += 5;
	}
	return (res);
}

t_value	*handle_buf(char *buf, int *i)
{
	while (buf[*i])
	{
		if (buf[*i] == '{')
			return (handle_dict(buf, i));
		if (buf[*i] == '"')
			return (string_value(buf, i));
		if (buf[*i] == '[')
			return (handle_array(buf, i));
		if (is_digit(buf[*i]) || buf[*i] == '-')
			return (handle_number(buf, i));
		if (
			(buf[*i] == 't' && buf[*i + 1] && buf[*i + 1] == 'r'
				&& buf[*i + 2] && buf[*i + 2] == 'u'
				&& buf[*i + 3] && buf[*i + 3] == 'e'
			) || (buf[*i] == 'f' && buf[*i + 1] && buf[*i + 1] == 'a'
				&& buf[*i + 2] && buf[*i + 2] == 'l'
				&& buf[*i + 3] && buf[*i + 3] == 's'
				&& buf[*i + 4] && buf[*i + 4] == 'e'
			)
		)
		{
			return (handle_boolean(buf, i));
		}
		(*i)++;
	}
	return (void_value());
}