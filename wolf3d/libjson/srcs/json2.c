/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 17:13:43 by dbousque          #+#    #+#             */
/*   Updated: 2018/04/28 17:13:45 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libjson.h"

t_dict	*void_json_object(void)
{
	t_dict	*res;

	if (!(res = (t_dict*)malloc(sizeof(t_dict))))
		malloc_error();
	res->keys = NULL;
	res->values = NULL;
	return (res);
}

t_value	*void_value(void)
{
	t_value	*res;

	if (!(res = (t_value*)malloc(sizeof(t_value))))
		malloc_error();
	res->data = NULL;
	res->type = 0;
	return (res);
}

void	ft_putendl_n2(char *str, int n)
{
	char	ori_char;

	ori_char = str[n];
	str[n] = '\0';
	ft_putendl(str);
	str[n] = ori_char;
}

void	go_to_next_char(char *buf, int *i, char c)
{
	while (buf[*i] && buf[*i] != c)
		(*i)++;
	if (!buf[*i])
		wrong_format();
}

void	go_to_next_char_not_in_string(char *buf, int *i, char c)
{
	int		nb;

	nb = 0;
	while (buf[*i] && (buf[*i] != c || nb == 1))
	{
		if (buf[*i] == '"')
		{
			if (nb == 1 && *i > 0 && buf[*i - 1] != '\\')
				nb = 0;
			else
				nb = 1;
		}
		(*i)++;
	}
	if (!buf[*i])
		wrong_format();
}
