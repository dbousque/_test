/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 18:35:27 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/08 20:18:50 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libdodo.h"

typedef struct		s_flag
{
	char			n;
	char			c;
	char			b;
}					t_flag;

typedef struct		s_salle
{
	char			*name;
	struct s_salle	**accessible_salles;
	t_list			*tmp_accessible_salles;
	t_list			*tmp_accessible_salles_end;
	int				x_coord;
	int				y_coord;
	int				id;
}					t_salle;

typedef struct		s_fourm
{
	t_salle			**salles;
	int				nb_fourmis;
	t_salle			*start;
	t_salle			*end;
	t_flag			*flags;
}					t_fourm;

typedef struct		s_fourmi
{
	int				*path;
	int				current_salle;
	int				id;
}					t_fourmi;

void				print_ft_ntoa_base(size_t n, char *base);
void				print_ft_ntoa_base_fd(size_t n, char *base, int fd);
void				print_number(size_t n);
char				is_tube_description(char *line);
char				is_comment(char *line);
char				only_numbers(char *str);
char				is_input_correct(char *line);
t_salle				**parse_salles(t_salle **start_salle, t_salle **end_salle,
											char **line, t_list **lines_end);
t_fourmi			*new_fourmi(int *path, int path_len);
t_salle				*new_salle(char *name, int x_coord, int y_coord);
t_salle				**list_to_salles(t_list *salles);
char				is_start_or_end_salle(char **line, t_salle **start_salle,
									t_salle **end_salle, t_list **lines_end);
int					strstrlen(char **strstr);
char				add_to_salles(t_list **salles_end, char **line,
									t_salle **str_end[2], t_list **lines_end);
void				put_salle(t_salle *salle);
void				put_salles(t_salle **salles);
int					get_tubes(t_salle **salles, char *line, t_list **lines_end);
t_fourm				*get_fourmiliere(t_salle **start_salle, t_salle **end_salle,
																t_list **lines);
int					listlen(t_list *list);
int					**find_suitable_paths(t_list *finished_paths, int nb_paths,
														t_fourm *fourmiliere);
void				put_path(t_list *path);
void				put_paths(t_list *paths);
char				lon(t_list **best_paths, int nb_best, int current_path_len,
																int nb_fourmis);
int					**path_to_int_paths(t_list **best_paths, int nb_paths);
char				no_shared_salle(t_list *tmp, t_list *visited_salles);
int					**find_best_paths(t_fourm *fourm, int nb_paths,
													t_list **finished_paths);
int					ft_error(void);
void				put_lines(t_list *lines);
int					make_fourmi_travel(int **best_paths, t_fourm *fourmiliere,
											int nb_paths, t_list *fourmis_end);
int					turns_required_for_n_fourmis(int path_len, int nb_fourmis);
char				lon(t_list **best_paths, int nb_best, int current_path_len,
																int nb_fourmis);
void				put_best_paths(int **best_paths, t_fourm *fourm);
int					intintlen(int **intint);
int					int_tab_len(int *tab);
int					*get_paths_len(int **best_paths, int nb_paths);
int					get_flags(int argc, char **argv, t_flag *flags);
t_flag				*void_flags(void);
void				print_fourmis(t_list *fourmis, t_fourm *fourmiliere);
void				print_fourmi_pos_color(int id, char *name);
void				print_address(void *ptr);

#endif
