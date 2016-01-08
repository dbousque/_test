/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_fourmi_travel.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 18:20:48 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/08 18:24:06 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	make_turn(t_list *fourmis)
{
	t_fourmi	*tmp_fourmi;

	while (fourmis)
	{
		tmp_fourmi = ((t_fourmi*)fourmis->content);
		tmp_fourmi->current_salle--;
		fourmis = fourmis->next;
	}
}

void	print_fourmis(t_list *fourmis, t_fourm *fourmiliere)
{
	t_fourmi	*tmp_fourmi;

	while (fourmis)
	{
		tmp_fourmi = ((t_fourmi*)fourmis->content);
		ft_printf("L%d-%s", tmp_fourmi->id,
		fourmiliere->salles[tmp_fourmi->path[tmp_fourmi->current_salle]]->name);
		if (fourmis->next)
			ft_putchar(' ');
		fourmis = fourmis->next;
	}
	ft_putchar('\n');
}

void	remove_fourmis_at_end(t_list **fourmis, t_list **fourmis_end,
																t_list *parent)
{
	t_list	*tmp;
	t_list	*next;

	tmp = *fourmis;
	while (tmp)
	{
		if (((t_fourmi*)tmp->content)->current_salle <= -1)
		{
			next = tmp->next;
			free(tmp);
			if (!parent)
				*fourmis = next;
			else
				parent->next = next;
			if (!next)
				*fourmis_end = parent;
			tmp = next;
		}
		else
		{
			parent = tmp;
			tmp = tmp->next;
		}
	}
}

void	fourm_on_ot_paths(int **best_paths, int *paths_len,
								t_fourm *fourmiliere, t_list **fourmis_end)
{
	char	go_on;
	int		i;

	i = 1;
	go_on = 1;
	while (go_on && best_paths[i] && fourmiliere->nb_fourmis > 0)
	{
		if (turns_required_for_n_fourmis(paths_len[i], 1) <=
	turns_required_for_n_fourmis(paths_len[i - 1], fourmiliere->nb_fourmis / i))
		{
			ft_lstaddend(fourmis_end,
				ft_lstnew(
					new_fourmi(best_paths[i], paths_len[i]), sizeof(t_fourmi)));
			fourmiliere->nb_fourmis--;
		}
		else
			go_on = 0;
		i++;
	}
}

int		make_fourmi_travel(int **best_paths, t_fourm *fourmiliere, int nb_paths,
															t_list *fourmis_end)
{
	int		*paths_len;
	t_list	*fourmis;

	ft_putchar('\n');
	if (!(paths_len = get_paths_len(best_paths, nb_paths)))
		return (ft_error());
	fourmis = NULL;
	while (fourmiliere->nb_fourmis > 0 || fourmis)
	{
		make_turn(fourmis);
		if (fourmiliere->nb_fourmis > 0)
		{
			ft_lstaddend(&fourmis_end, ft_lstnew(
					new_fourmi(best_paths[0], paths_len[0]), sizeof(t_fourmi)));
			fourmiliere->nb_fourmis--;
			if (!fourmis)
				fourmis = fourmis_end;
			fourm_on_ot_paths(best_paths, paths_len, fourmiliere, &fourmis_end);
		}
		remove_fourmis_at_end(&fourmis, &fourmis_end, NULL);
		if (fourmis)
			print_fourmis(fourmis, fourmiliere);
	}
	return (0);
}
