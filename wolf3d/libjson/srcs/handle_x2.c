/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_x2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 17:13:30 by dbousque          #+#    #+#             */
/*   Updated: 2018/04/28 17:19:32 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libjson.h"

char	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	init_key_values(t_list **key_values, char c_preceed[2])
{
	key_values[0] = NULL;
	key_values[1] = NULL;
	key_values[2] = NULL;
	key_values[3] = NULL;
	c_preceed[0] = '"';
	c_preceed[1] = '\\';
}

t_value	*handle_dict(char *buf, int *i)
{
	t_list	*kv[4];
	char	*tmp_k;
	t_value	*tmp_value;
	int		len;
	char	c_preceed[2];

	init_key_values(kv, c_preceed);
	while (1)
	{
		go_to_next_char(buf, i, '"');
		(*i)++;
		tmp_k = take_up_to_char(buf, i, c_preceed, &len);
		(*i)++;
		ft_lstaddend(&(kv[1]), new_list_elt(tmp_k, (len + 1) * sizeof(char)));
		kv[0] = kv[0] ? kv[0] : kv[1];
		buf[*i] != ':' ? no_colon() : (void)len;
		tmp_value = handle_buf(buf, i);
		ft_lstaddend(&(kv[3]), new_list_elt(tmp_value, sizeof(t_value)));
		kv[2] = kv[2] ? kv[2] : kv[3];
		if (buf[*i] != ',')
			break ;
	}
	go_to_next_char_not_in_string(buf, i, '}');
	(*i)++;
	return (keys_n_values_to_value(kv[0], kv[2]));
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
