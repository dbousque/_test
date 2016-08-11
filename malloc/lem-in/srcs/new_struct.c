/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 16:21:49 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/08 16:22:07 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_fourmi	*new_fourmi(int *path, int path_len)
{
	static int	id = 1;
	t_fourmi	*res;

	if (!(res = (t_fourmi*)malloc(sizeof(t_fourmi))))
		return (NULL);
	res->path = path;
	res->id = id;
	res->current_salle = path_len - 1;
	id++;
	return (res);
}

t_salle		*new_salle(char *name, int x_coord, int y_coord)
{
	static int	id = 0;
	t_salle		*res;

	if (!(res = (t_salle*)malloc(sizeof(t_salle))))
		return (NULL);
	res->x_coord = x_coord;
	res->y_coord = y_coord;
	res->accessible_salles = NULL;
	res->tmp_accessible_salles = NULL;
	res->tmp_accessible_salles_end = NULL;
	res->name = ft_strdup(name);
	res->id = id;
	id++;
	return (res);
}
