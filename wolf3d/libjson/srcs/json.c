

#include "libjson.h"

char	*take_up_to_char(char *buf, int *i, char c, char preceed, int *len)
{
	int		start;
	char	*res;

	start = *i;
	while (buf[*i] && (buf[*i] != c || (*i > 0 && buf[*i - 1] == preceed)))
		(*i)++;
	*len = *i - start;
	if (!(res = (char*)malloc(sizeof(char) * (*len + 1))))
		malloc_error();
	res[*len] = '\0';
	return (ft_strncpy(res, buf + start, *len));
}

t_list	*new_list_elt(void *content, int content_size)
{
	t_list	*res;

	if (!(res = (t_list*)malloc(sizeof(t_list))))
		malloc_error();
	res->content = content;
	res->content_size = content_size;
	res->next = NULL;
	return (res);
}

t_value	*string_value(char *buf, int *i)
{
	char	*str;
	int		len;
	t_value	*res;

	go_to_next_char(buf, i, '"');
	(*i)++;
	str = take_up_to_char(buf, i, '"', '\\', &len);
	(*i)++;
	if (!(res = (t_value*)malloc(sizeof(t_value))))
		malloc_error();
	res->data = (void*)str;
	res->type = STRING;
	return (res);
}

void	populate_dict(t_dict *dict, t_list *keys, t_list *values, int len)
{
	int		i;
	t_list	*tmp;

	dict->values[len] = NULL;
	dict->keys[len] = NULL;
	i = 0;
	while (keys)
	{
		dict->keys[i] = (char*)keys->content;
		dict->values[i] = (t_value*)values->content;
		tmp = keys;
		keys = keys->next;
		free(tmp);
		tmp = values;
		values = values->next;
		free(tmp);
		i++;
	}
}

t_value	*keys_n_values_to_value(t_list *keys, t_list *values)
{
	int		len;
	t_list	*tmp;
	t_dict	*dict;
	t_value	*ret_val;

	len = 0;
	tmp = keys;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	if (!(dict = (t_dict*)malloc(sizeof(t_dict))))
		malloc_error();
	if (!(dict->keys = (char**)malloc(sizeof(char*) * (len + 1))))
		malloc_error();
	if (!(dict->values = (t_value**)malloc(sizeof(t_value*) * (len + 1))))
		malloc_error();
	populate_dict(dict, keys, values, len);
	if (!(ret_val = (t_value*)malloc(sizeof(t_value))))
		malloc_error();
	ret_val->type = DICT;
	ret_val->data = (void*)dict;
	return (ret_val);
}