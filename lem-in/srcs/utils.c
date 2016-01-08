/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 16:55:02 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/08 18:02:19 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	put_salle(t_salle *salle)
{
	int		i;

	ft_printf("SALLE N %d :\n  - NAME : %s\n  - X : %d\n  - Y : %d\n",
			salle->id, salle->name, salle->x_coord, salle->y_coord);
	i = 0;
	while (salle->accessible_salles && salle->accessible_salles[i])
	{
		ft_printf("     access : %d\n", salle->accessible_salles[i]->id);
		i++;
	}
}

void	put_salles(t_salle **salles)
{
	int		i;

	i = 0;
	while (salles[i])
	{
		put_salle(salles[i]);
		i++;
	}
}

void	put_path(t_list *path)
{
	while (path)
	{
		ft_putnbr(*(int*)path->content);
		ft_putstr(", ");
		path = path->next;
	}
	ft_putchar('\n');
}

void	put_paths(t_list *paths)
{
	while (paths)
	{
		put_path((t_list*)paths->content);
		paths = paths->next;
	}
}
