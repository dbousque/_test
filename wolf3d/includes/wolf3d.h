

#ifndef WOLF3D_H
# define WOLF3D_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <math.h>

# include "mlx.h"
# include "libjson.h"

# define DEFAULT_WIDTH 1200
# define DEFAULT_HEIGHT 800
# define NB_THREADS 32
# define NB_KEY_PRESS 0

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
# define IS_P(k) (k == 35 || k == 112)
# define IS_B(k) (k == 11 || k == 98)
# define IS_PLUS(k) (k == 24 || k == 61)
# define IS_MINUS(k) (k == 27 || k == 45)
# define IS_PLUS_BIS(k) (k == 44 || k == 47)
# define IS_MINUS_BIS(k) (k == 47 || k == 46)
# define IS_MOUSE_FORWARD(k) (k == 4)
# define IS_MOUSE_BACKWARDS(k) (k == 5)

# define DEG_TO_RAD(x) (x * 0.0174533)

typedef struct timeval	t_timeval;

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
	char		pressed_keys[NB_KEY_PRESS];
}				t_window;

typedef struct	s_list2
{
	void		*elts;
	int			size;
	int			len;
	size_t		elt_size;
}				t_list2;

typedef struct	s_texture
{
	char		*name;
	int			*pixels;
	int			width;
	int			height;
}				t_texture;

typedef enum
{
	STD_BLOCK,
	OBJECT_BLOCK
}	t_block_typ;

typedef enum
{
	POSITION_TOP,
	POSITION_BOTTOM
}	t_obj_pos;

typedef struct	s_block
{
	t_block_typ	type;
	int			id;
	char		go_through;
	char		is_object;
	t_texture	faces[4];
	t_texture	*obj_texture;
	double		scale;
	t_obj_pos	position;
}				t_block;

typedef struct	s_map
{
	t_list2		textures;
	t_list2		blocks;
	t_list2		blocks_positions;
}				t_map;

typedef struct	s_player
{
	float		x;
	float		y;
	float		looking_dir;
}				t_player;

typedef struct	s_wolf3d
{
	t_window	window;
	char		changed;
	char		big_mode;
	t_timeval	last_frame;
	t_map		map;
	t_player	player;
}				t_wolf3d;

int				exit_wolf3d(t_wolf3d *wolf3d);
void			set_color_at(t_wolf3d *wolf3d, int x, int y, int color);
int				millis_since(struct timeval *start);
void			print_time_taken(struct timeval *start, char *before,
																char *after);
char			init_list(t_list2 *list, size_t elt_size);
void			*new_elt(t_list2 *lst);
void			remove_elt(t_list2 *lst, char *addr);
void			wait_for_threads_to_finish(pthread_t *threads);
int				expose_hook(void *param);
int				key_pressed_hook(int keycode, void *param);
int				key_released_hook(int keycode, void *param);
int				mouse_hook(int keycode, int x, int y, void *param);
int				mouse_move_hook(int x, int y, void *param);
void			apply_image_to_window(t_window *window);
char			init_window(t_window *window, int width, int height,
																char *title);

#endif