/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 18:37:40 by dbousque          #+#    #+#             */
/*   Updated: 2016/09/22 18:37:42 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

void	print_n_char(char c, int n)
{
	int		i;

	i = 0;
	while (i < n)
	{
		write(1, &c, 1);
		i++;
	}
}

void	ft_putstrn(char *str, int n)
{
	write(1, str, n);
}

char	ft_streq(char *str1, char *str2)
{
	int		i;

	i = 0;
	while (str1[i] && str1[i] == str2[i])
		i++;
	if (!str1[i] && !str2[i])
		return (1);
	return (0);
}

void	print_n_bytes(unsigned char *start, size_t i, int nb_bytes,
																	size_t end)
{
	size_t	x;

	(void)end;
	x = i;
	while (x < i + nb_bytes && x < end)
	{
		print_hexa_n(start[x], 2);
		ft_putstr(" ");
		x++;
	}
}

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
