/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_fourmi_travel.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 18:20:48 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/08 20:19:00 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	make_turn(t_list *fourmis, t_fourm *fourmiliere, int end)
{
	t_fourmi	*tmp_fourmi;
	static int	nb = 0;

	if (fourmis)
		nb++;
	if (end)
	{
		if (fourmiliere->flags->n)
			ft_printf("--> {cyan}NB TURNS{eoc} : {red}%d{eoc}\n", nb);
	}
	else
	{
		while (fourmis)
		{
			tmp_fourmi = ((t_fourmi*)fourmis->content);
			tmp_fourmi->current_salle--;
			fourmis = fourmis->next;
		}
	}
}

void	remove_fourmis_at_end(t_list **fourmis, t_list **fourmis_end,
																t_list *parent)
{
	t_list	*tmp;
	t_list	*next;

	tmp = *fourmis;
	while (tmp)
	{
		ft_putstr("current_salle : ");
		print_number(((t_fourmi*)tmp->content)->current_salle);
		ft_putstr("\n");
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
			ft_putstr("else\n");
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
	ft_putstr("start make fourmi\n");
	if (!(paths_len = get_paths_len(best_paths, nb_paths)))
		return (ft_error());
	ft_putstr("after get paths\n");
	fourmis = NULL;
	while (fourmiliere->nb_fourmis > 0 || fourmis)
	{
		ft_putstr("TOUR DE FOURMI, nb de fourmis : ");
		print_number(fourmiliere->nb_fourmis);
		ft_putstr("\n");
		ft_putstr("fourmis : ");
		print_address(fourmis);
		ft_putstr("\n");
		make_turn(fourmis, fourmiliere, 0);
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
	make_turn(NULL, fourmiliere, 1);
	return (0);
}
