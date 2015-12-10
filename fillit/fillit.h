/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 11:50:48 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/06 18:26:58 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include "./libft/libft.h"
# include <fcntl.h>

# define BUF_SIZE 64

typedef struct		s_tetrimino
{
	char			width;
	char			heigth;
	char			**content;
	char			letter;
}					t_tetrimino;

typedef struct		s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct		s_node2
{
	char			**board;
	int				heigth;
	int				width;
	int				priority;
	int				nb_pieces;
}					t_node2;

typedef struct		s_tree
{
	t_node2			**tree;
	int				max_size;
	int				nb_elts;
	int				last;
}					t_tree;

char				*ft_read_file(char *filename);
int					ft_valid_file(char *file_content);
char				**ft_allocate_strstr(int max_width, int max_height, char c);
void				ft_del_tetris(t_tetrimino **tetris);
t_tetrimino			**ft_get_tetriminos(char *file_content);
char				**ft_strstrdup(char **strstr);
void				ft_add_piece2(t_node2 *node, t_tetrimino *t, int x, int y);
t_node2				*ft_new2(char **board, int heig, int width, int nb_pieces);
t_tree				*ft_add_to_tree2(t_tree *tree, t_node2 *node);
t_node2				*ft_get_top(t_tree *tree);
t_tree				*ft_empty_tree(void);
void				ft_delstrstr(char **content);
t_tetrimino			*ft_new_tetrimino(char *content, int ind);
void				ft_delstrstr2(char **strstr);
void				ft_del_points(void *point, size_t size);
void				ft_free_node(t_node2 *node);
int					ft_has_four(t_tetrimino *piece);
int					ft_is_barre(t_tetrimino *p);
int					ft_is_carre(t_tetrimino *piece);
int					ft_is_fleche(t_tetrimino *p);
int					ft_is_semibarre(t_tetrimino *p);
int					ft_is_torti(t_tetrimino *p);
int					ft_valid_tetrimino(t_tetrimino *piece);
char				**ft_solve_tetris(t_tetrimino **tetris);
char				**ft_strrip(char *content, int x[], int y_min, int y_max);
int					ft_can_put(char **board, int x, int y, t_tetrimino *tetri);
int					ft_could_be_closer(t_node2 *n, t_node2 *b, int max);
int					ft_has_min_size(t_tetrimino **tetris, int max);
t_list				*ft_ok_pnts(t_node2 *n, t_tetrimino *t, int m, t_node2 *be);
t_node2				*ft_free_n_upd_max(t_node2 *best, t_node2 *high, int *max);
int					ft_bad_node(int max, t_node2 *hi, t_node2 *best, int cant);
char				**ft_rip_res(char **board, t_tetrimino **tetris);
int					ft_char_in_line(char *str);
t_node2				*ft_get_res_n_update(t_tree *tree);
int					ft_right_place(int *ind, t_tree *tree);
int					ft_first_higher(t_tree *tree, int ind1, int ind2);
t_node2				*ft_swap(t_tree *tree, int *ind, int ind2, t_node2 *tmp);
void				ft_void_int(int res[26]);

#endif
