/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <dbousque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/09 15:05:02 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/10 12:29:39 by dbousque         ###   ########.fr       */
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
# define WIDTH 1680
# define HEIGHT 1280

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
}				t_pov;

typedef struct	s_rect
{
	t_point		**points;
}				t_rect;

typedef struct	s_mlx
{
	void		*mlx;
	void		*win;
	void		*img;
	int			width;
	int			height;
	t_pov		*pov;
	int			**mesh;
}				t_mlx;

int				**ft_get_mesh(char *filename);
void			ft_draw_rect(t_mlx *mlx, t_rect *rect,
					int (*ft_clr) (t_point *p1, t_point *p2, double perc));
int				ft_render_mesh(void *mlx_param);
int				ft_unexpected_error(void);
t_point			*ft_new_point(double x, double y, int height);
t_rect			*ft_new_rect(t_point *one, t_point *two, t_point *three, t_point *four);
int				ft_get_color(t_point *p1, t_point *p2, double percentage);

#endif
