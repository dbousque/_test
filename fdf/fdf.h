/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <dbousque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/09 15:05:02 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/17 17:50:21 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "./libmlx/mlx.h"
# include "./libft/libft.h"
# include <math.h>
# include <fcntl.h>
# include "get_next_line.h"

# define RAD 0.01745329252
# define WIDTH 1280
# define HEIGHT 760
# define W 13
# define A 0
# define S 1
# define D 2
# define H 4
# define J 38
# define LEFT 123
# define UP 126
# define DOWN 125
# define RIGHT 124
# define Z 6
# define X 7
# define M 46
# define F 3
# define ESC 53

typedef struct	s_point
{
	double		x;
	double		y;
	double		height;
}				t_point;

typedef struct	s_rect
{
	t_point		**points;
}				t_rect;

typedef struct	s_mlx
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*pixels;
	int			bpp;
	int			s_line;
	int			ed;
	int			last_pixel;
	int			width;
	int			height;
	int			**mesh;
	t_point		***points;
	double		unit;
	double		start_x;
	double		start_y;
	int			view_mode;
	double		height_factor;
	double		angle;
	double		elevation;
	double		lower_point;
	double		higher_point;
	t_point		*center;
	int			(*clr_fct) (struct s_mlx *m, t_point *p, t_point *d, double pe);
	int			clr_function_num;
}				t_mlx;

typedef struct	s_vector
{
	double		x_step;
	double		y_step;
}				t_vector;

int				**ft_get_mesh(char *filename);
void			ft_draw_rect(t_mlx *mlx, int y, int x);
int				ft_render_mesh(void *mlx_param);
int				ft_unexpected_error(void);
t_point			*ft_new_point(double x, double y, int height);
t_rect			*ft_new_rect(t_point *o, t_point *tw, t_point *th, t_point *fo);
int				ft_get_color(t_mlx *mlx, t_point *p1, t_point *p2, double perc);
int				ft_get_color2(t_mlx *mlx, t_point *p1, t_point *p2, double per);
int				ft_get_color3(t_mlx *mlx, t_point *p1, t_point *p2, double per);
int				ft_get_color4(t_mlx *mlx, t_point *p1, t_point *p2, double per);
void			ft_draw_line(t_mlx *mlx, t_point *p1, t_point *p2);
int				ft_get_mouse(int x, int y, void *param);
int				ft_render(void *mlx_param);
int				ft_nb_lines(int **mesh);
void			ft_put_image_to_window(void *mlx, void *win, void *img);
void			restore_window(t_mlx *mlx);
t_vector		*ft_new_vector(double x, double y);
double			ft_real_value(double inp);
double			ft_perc(t_point *p1, t_point *p2, double x, double y);
int				ft_map_error(void);
int				ft_connection_failed(void);
int				ft_unexpected_error(void);
t_mlx			*ft_new_mlx(int width, int height, char *title);
t_point			***empty_points(t_mlx *mlx);
void			draw_full_rect(t_mlx *mlx, t_rect *rect);
int				key_hook(int keycode, void *mlx_param);
void			ft_draw_line2(t_mlx *mlx, t_point *p1, t_point *p2);
int				ft_exit(t_mlx *mlx);
int				expose_hook(void *mlx_param);
int				mouse_hook(int keycode, int x, int y, t_mlx *mlx);
double			ft_perc(t_point *p1, t_point *p2, double x, double y);
void			ft_draw_void_rect(t_mlx *mlx, int y, int x);
int				ft_lstlen(t_list *lines);
int				ft_strstrlen(char **strstr);
void			ft_delstr(void *content, size_t size);
void			get_coords_at_xy(t_mlx *mlx, int y, int x, t_vector *dev);
double			get_extreme_y(t_mlx *mlx, int nb_lines);
double			get_extreme_x(t_mlx *mlx, int nb_lines);
void			set_start_point(t_mlx *mlx, t_vector *dev, int nb_lines);

#endif
