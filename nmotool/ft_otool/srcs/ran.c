/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ran.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 18:40:59 by dbousque          #+#    #+#             */
/*   Updated: 2016/09/22 18:41:12 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

char	*ft_strjoin(char *str1, char *str2)
{
	char	*str_res;
	int		i;
	int		tmp;

	str_res = my_malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2) + 1));
	i = 0;
	while (str1[i])
	{
		str_res[i] = str1[i];
		i++;
	}
	tmp = i;
	i = 0;
	while (str2[i])
	{
		str_res[tmp + i] = str2[i];
		i++;
	}
	str_res[i] = '\0';
	return (str_res);
}

void	read_ranlib(void *ptr, struct ranlib *ran, size_t size)
{
	struct ar_hdr	*header;

	(void)size;
	header = ptr + ran->ran_off - 8;
	ft_putstr(get_current_ar_name(NULL));
	ft_putstr("(");
	ft_putstr(((char*)((void*)header + sizeof(struct ar_hdr))));
	ft_putstr("):\n");
	otool((void*)header + sizeof(struct ar_hdr) + end_of_name((void*)header
		+ sizeof(struct ar_hdr)), ft_atoi(header->ar_size),
		ft_strjoin(ft_strjoin(get_current_ar_name(NULL), ":"),
			(void*)header + sizeof(struct ar_hdr)), 0);
}

void	read_all_ranlibs(void *ptr, t_list *rans, size_t size)
{
	int		i;

	sort_list(rans, cmp_rans);
	i = 0;
	while (i < rans->len)
	{
		read_ranlib(ptr, rans->elts[i], size);
		i++;
	}
}

char	already_in_rans(t_list *rans, struct ranlib *ran)
{
	int		i;

	i = 0;
	while (i < rans->len)
	{
		if (cmp_rans(rans->elts[i], ran) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	read_ranlibs(void *ptr, struct ranlib *ran, int rans_len, size_t size)
{
	int		i;
	char	*stringtable;
	void	*end;
	t_list	*rans;

	rans = new_list();
	end = (void*)ran + rans_len;
	stringtable = ((char*)((void*)ran + rans_len - 8));
	i = 0;
	while (i < rans_len)
	{
		if ((void*)ran + sizeof(struct ranlib) > end)
			return (bad_executable());
		if (ran->ran_off && !already_in_rans(rans, ran))
			add_to_list(rans, ran);
		ran = (void*)ran + sizeof(struct ranlib);
		i += sizeof(struct ranlib);
	}
	read_all_ranlibs(ptr, rans, size);
}

void	handle_ranlib(void *ptr, size_t size, char *file_name)
{
	struct ar_hdr	*header;
	size_t			ar_size;
	void			*ran_start;
	int				rans_len;

	get_current_ar_name(file_name);
	(void)size;
	header = ptr;
	ar_size = ft_atoi(header->ar_size);
	if (ft_streq(((void*)header) + sizeof(struct ar_hdr), SYMDEF_SORTED))
		ran_start = ((void*)header) + sizeof(struct ar_hdr)
								+ ft_strlen(SYMDEF_SORTED) + sizeof(long);
	else if (ft_streq(((void*)header) + sizeof(struct ar_hdr), SYMDEF))
		ran_start = ((void*)header) + sizeof(struct ar_hdr)
									+ ft_strlen(SYMDEF) + sizeof(long);
	else
		return (bad_executable());
	rans_len = *((int*)(ran_start - sizeof(int)));
	read_ranlibs(ptr, ran_start, rans_len, size);
}
