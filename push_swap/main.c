/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/30 19:55:41 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/30 19:55:43 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

typedef struct	s_pile
{
	int			*elts;
	int			top;
	int			length;
}				t_pile;

void	put_pile(t_pile *pile)
{
	int		i;

	i = pile->top;
	while (i < pile->length)
	{
		if (i != pile->top)
			ft_putstr(", ");
		ft_putnbr(pile->elts[i]);
		i++;
	}
	ft_putchar('\n');
}

t_pile	*empty_pile(void)
{
	t_pile	*res;

	if (!(res = (t_pile*)malloc(sizeof(t_pile))))
		return (NULL);
	res->length = 1;
	res->top = 1;
	if (!(res->elts = (int*)malloc(sizeof(int))))
		return (NULL);
	return (res);
}

void	double_pile_length(t_pile *pile)
{
	int		*ori;
	int		i;
	int		half;

	half = pile->length;
	pile->length *= 2;
	ori = pile->elts;
	if ((pile->elts = (int*)malloc(sizeof(int) * pile->length)))
	{
		i = 0;
		while (i < half)
		{
			pile->elts[i + half] = ori[i];
			i++;
		}
		pile->top += half;
	}
	free(ori);
	ori = NULL;
}

char	put_on_pile(t_pile *pile, int nb)
{
	if (pile->top <= 0)
		double_pile_length(pile);
	if (!pile || !pile->elts)
		return (-1);
	pile->top--;
	pile->elts[pile->top] = nb;
	return (0);
}

t_pile	*pile_from_array(int *nbs, int length)
{
	t_pile	*res;
	int		i;

	i = length - 1;
	res = empty_pile();
	while (i >= 0)
	{
		if (put_on_pile(res, nbs[i]) == -1)
			return (NULL);
		i--;
	}
	return (res);
}

char	twice_same(int argc, int *nbs)
{
	int		i;
	int		x;

	i = 0;
	while (i < argc)
	{
		x = 0;
		while (x < argc)
		{
			if (i != x && nbs[i] == nbs[x])
				return (1);
			x++;
		}
		i++;
	}
	return (0);
}

char	invalid_char_in(char *str)
{
	int		i;

	i = 0;
	if (str[0] == '-')
		str++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9' || (str[0] == '0'))
			return (1);
		i++;
	}
	return (0);
}

char	too_big_len_ten(char *str, char signe, int len)
{
	int		i;
	char	*int_max;

	int_max = "2147483647";
	i = 0;
	while (i < len)
	{
		if (i == 9)
		{
			if (str[i] > '8' || (signe == 0 && str[i] > '7'))
				return (1);
		}
		else if (str[i] > int_max[i])
			return (1);
		i++;
	}
	return (0);
}

char	too_big_for_int(char *str)
{
	int		len;
	char	signe;

	signe = 0;
	if (str[0] == '-')
	{
		signe = 1;
		str++;
	}
	len = ft_strlen(str);
	if (len > 10)
		return (1);
	else if (len == 10)
		return (too_big_len_ten(str, signe, len));
	return (0);
}

int		*get_nbs(int argc, char **argv)
{
	int		*nbs;
	int		i;

	if (!(nbs = (int*)malloc(sizeof(int) * (argc - 1))))
		return (NULL);
	i = 1;
	while (i < argc)
	{
		if (invalid_char_in(argv[i]) || too_big_for_int(argv[i]))
		{
			free(nbs);
			return (NULL);
		}
		nbs[i - 1] = ft_atoi(argv[i]);
		i++;
	}
	return (nbs);
}

int		error(int *nbs)
{
	if (nbs)
		free(nbs);
	nbs = NULL;
	ft_putendl_fd("Error", 2);
	return (0);
}

int		main(int argc, char **argv)
{
	int		*nbs;
	t_pile	*pile_a;

	nbs = get_nbs(argc, argv);
	if (!nbs || twice_same(argc - 1, nbs))
		return (error(nbs));
	if (!(pile_a = pile_from_array(nbs, argc - 1)))
		return (error(nbs));
	free(nbs);
	nbs = NULL;
	put_pile(pile_a);
	return (0);
}
