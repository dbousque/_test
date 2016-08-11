/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_fourmis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 20:17:45 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/08 20:18:52 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_fourmi_pos_color(int id, char *name)
{
	char	*color;
	char	*str;

	if (id % 6 == 0)
		color = "{magenta}";
	else if (id % 6 == 1)
		color = "{red}";
	else if (id % 6 == 2)
		color = "{blue}";
	else if (id % 6 == 3)
		color = "{yellow}";
	else if (id % 6 == 4)
		color = "{cyan}";
	else if (id % 6 == 5)
		color = "{green}";
	else
		color = "{white}";
	str = ft_strjoin(color, "L%d-%s{eoc}");
	ft_printf(str, id, name);
	free(str);
}

void	print_fourmis(t_list *fourmis, t_fourm *fourmiliere)
{
	t_fourmi	*tmp_fourmi;

	while (fourmis)
	{
		tmp_fourmi = ((t_fourmi*)fourmis->content);
		if (fourmiliere->flags->c)
			print_fourmi_pos_color(tmp_fourmi->id,
		fourmiliere->salles[tmp_fourmi->path[tmp_fourmi->current_salle]]->name);
		else
			ft_printf("L%d-%s", tmp_fourmi->id,
		fourmiliere->salles[tmp_fourmi->path[tmp_fourmi->current_salle]]->name);
		if (fourmis->next)
			ft_putchar(' ');
		fourmis = fourmis->next;
	}
	ft_putchar('\n');
}
