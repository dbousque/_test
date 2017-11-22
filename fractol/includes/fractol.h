

#ifndef FRACTOL_H
# define FRACTOL_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

# include "mlx.h"

# define DEFAULT_WIDTH 1200
# define DEFAULT_HEIGHT 800
# define NB_THREADS 4
# define NB_FRACTALS 1
# define NB_PALETTES 6
# define PALETTE_LEN 50

# define PIXEL_AT(window, x, y) window.pixels[(x) + (y) * window.width]

# define IS_W(k) (k == 13 || k == 119)
# define IS_A(k) (k == 0 || k == 97)
# define IS_S(k) (k == 1 || k == 115)
# define IS_D(k) (k == 2 || k == 100)
# define IS_H(k) (k == 4 || k == 104)
# define IS_J(k) (k == 38 || k == 106)
# define IS_LEFT(k) (k == 123 || k == 65361)
# define IS_UP(k) (k == 126 || k == 65362)
# define IS_DOWN(k) (k == 125 || k == 65364)
# define IS_RIGHT(k) (k == 124 || k == 65363)
# define IS_Z(k) (k == 6 || k == 122)
# define IS_X(k) (k == 7 || k == 120)
# define IS_M(k) (k == 46 || k == 109)
# define IS_F(k) (k == 3 || k == 102)
# define IS_ESC(k) (k == 53 || k == 65307)
# define IS_P(k) (k == 112)
# define IS_B(k) (k == 98)

typedef struct	s_mouse
{
	int			x;
	int			y;
}				t_mouse;

typedef struct	s_window
{
	void		*mlx;
	void		*win;
	void		*img;
	int			*pixels;
	int			width;
	int			height;
	t_mouse		mouse;
}				t_window;

typedef struct	s_fractal
{
	float		params[1];
	int			max_iter;
	int			(*handle)(struct s_fractal *f, int x, int y, t_window *w);
}				t_fractal;

typedef struct	s_fractol
{
	t_window	window;
	t_fractal	fractals[1];
	int			current_fractal;
	int			palettes[NB_PALETTES][PALETTE_LEN];
	int			current_palette;
	char		big_mode;
	char		changed;
}				t_fractol;

typedef struct	s_thread_data
{
	t_fractol	*f;
	int			from_x;
	int			until_x;
	int			from_y;
	int			until_y;
}				t_thread_data;

void			ft_putstr(char *str);
int				exit_fractol(t_fractol *fractol);
void			parse_opts(int argc, char **argv, int *width, int *height);
void			maybe_update_current_fractal(t_fractol *fractol, int argc,
																char **argv);
void			ft_itoa(int n, char *res);
int				expose_hook(void *param);
int				key_hook(int keycode, void *param);
int				mouse_hook(int keycode, int x, int y, void *param);
void			apply_image_to_window(t_window *window);
char			init_window(t_window *window, int width, int height,
																char *title);
void			render_fractol(t_fractol *fractol);
void			init_palettes(int palettes[NB_PALETTES][PALETTE_LEN]);
int				mandelbrot(t_fractal *fractal, int x, int y, t_window *window);

#endif