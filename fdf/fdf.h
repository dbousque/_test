/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <dbousque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/09 15:05:02 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/11 13:53:39 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"
# include <math.h>
# include <fcntl.h>
# include "get_next_line.h"


# define RAD 0.01745329252
# define WIDTH 1280
# define HEIGHT 860

typedef struct	s_point
{
	double		x;
	double		y;
	int			height;
}				t_point;

typedef struct	s_pov
{
	double		x;
	double		y;
	double		height;
	double		head_balance;
	double		zoom;
}				t_pov;

typedef struct	s_rect
{
	t_point		**points;
}				t_rect;

typedef struct	s_mlx
{
	void		*mlx;
	void		*win;
	int			*img;
	int			last_pixel;
	int			width;
	int			height;
	t_pov		*pov;
	int			**mesh;
	t_point		***points;
	double		unit;
	double		start_x;
	double		start_y;
	double		height_factor;
	double		angle;
	int			(*color_function) (t_point *p1, t_point *p2, double perc);
}				t_mlx;

typedef struct	s_vector
{
	double		x_step;
	double		y_step;
}				t_vector;

typedef struct	s_3d_vec
{
	double		ux;
	double		uy;
	double		uz;
}				t_3d_vec;

int				**ft_get_mesh(char *filename);
void			ft_draw_rect(t_mlx *mlx, t_rect *rect,
					int (*ft_clr) (t_point *p1, t_point *p2, double perc));
int				ft_render_mesh(void *mlx_param);
int				ft_unexpected_error(void);
t_point			*ft_new_point(double x, double y, int height);
t_rect			*ft_new_rect(t_point *one, t_point *two, t_point *three, t_point *four);
int				ft_get_color(t_point *p1, t_point *p2, double percentage);
int				ft_get_color2(t_point *p1, t_point *p2, double percentage);
int				ft_get_color3(t_point *p1, t_point *p2, double percentage);
void			ft_draw_line(t_mlx *mlx, t_point *p1, t_point *p2,
					int (*ft_clr) (t_point *p1, t_point *p2, double perc));
int				ft_get_mouse(int x, int y, t_mlx *param);
int				ft_render(void *mlx_param);
int				ft_nb_lines(int **mesh);
void			ft_put_image_to_window(void *mlx, void *win, void *img, int x, int y);
void			restore_window(t_mlx *mlx);
t_vector		*ft_new_vector(double x, double y);

#endif
