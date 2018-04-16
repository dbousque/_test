

#include "libjson.h"

void	init_key_values(t_list **key_values)
{
	key_values[0] = NULL;
	key_values[1] = NULL;
	key_values[2] = NULL;
	key_values[3] = NULL;
}

t_value	*handle_dict(char *buf, int *i)
{
	t_list	*key_values[4];
	char	*tmp_key;
	t_value	*tmp_value;
	int		len;

	init_key_values(key_values);
	while (1)
	{
		go_to_next_char(buf, i, '"');
		(*i)++;
		tmp_key = take_up_to_char(buf, i, '"', '\\', &len);
		(*i)++;
		ft_lstaddend(&(key_values[1]), new_list_elt(tmp_key, (len + 1) * sizeof(char)));
		if (!key_values[0])
			key_values[0] = key_values[1];
		if (buf[*i] != ':')
			no_colon();
		tmp_value = handle_buf(buf, i);
		ft_lstaddend(&(key_values[3]), new_list_elt(tmp_value, sizeof(t_value)));
		if (!key_values[2])
			key_values[2] = key_values[3];
		if (buf[*i] != ',')
			break ;
	}
	go_to_next_char_not_in_string(buf, i, '}');
	(*i)++;
	return (keys_n_values_to_value(key_values[0], key_values[2]));
}

t_value	*values_list_to_array(t_list *values, int nb)
{
	t_value	*res;
	t_value	**data;
	t_list	*tmp;

	if (!(data = (t_value**)malloc(sizeof(t_value*) * (nb + 1))))
		malloc_error();
	data[nb] = NULL;
	nb = 0;
	while (values)
	{
		data[nb] = (t_value*)values->content;
		tmp = values;
		values = values->next;
		free(tmp);
		nb++;
	}
	if (!(res = (t_value*)malloc(sizeof(t_value))))
		malloc_error();
	res->data = data;
	res->type = ARRAY;
	return (res);
}

t_value	*handle_array(char *buf, int *i)
{
	int		ret;
	t_list	*values;
	t_list	*values_end;
	t_value	*tmp_value;
	int		nb;

	values = NULL;
	values_end = NULL;
	ret = 1;
	nb = 0;
	(*i)++;
	while (ret)
	{
		tmp_value = handle_buf(buf, i);
		ft_lstaddend(&values_end, new_list_elt(tmp_value, sizeof(t_value)));
		if (!values)
			values = values_end;
		if (buf[*i] != ',')
			ret = 0;
		nb++;
	}
	go_to_next_char(buf, i, ']');
	(*i)++;
	return (values_list_to_array(values, nb));
}