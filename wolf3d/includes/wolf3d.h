

#ifndef WOLF3D_H
# define WOLF3D_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <math.h>
# include <float.h>
# include "SOIL.h"

# include "mlx.h"
# include "libjson.h"

# define NB_THREADS 16
# define NB_KEY_PRESS 10

# define PIXEL_AT(window, x, y) (window).pixels[(x) + (y) * (window).width]
# define MAP_BLOCKS(w) ((t_block**)w->map.blocks_positions.elts)
# define BLOCK_AT(w, x, y) MAP_BLOCKS(w)[(x) + (y) * w->map.width]
# define SOIL_LOAD(p, w, h, c) SOIL_load_image(p, w, h, c, SOIL_LOAD_RGB)

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
# define RAD_TO_DEG(x) (x / 0.0174533)

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
	int			*img_pixels;
	int			*pixels;
	int			width;
	int			height;
	t_mouse		mouse;
	char		pressed_keys[NB_KEY_PRESS];
	char		antialiasing;
}				t_window;

typedef struct	s_list2
{
	void		*elts;
	int			size;
	int			len;
	size_t		elt_size;
}				t_list2;

typedef unsigned char uchar;

typedef struct	s_texture
{
	char		*name;
	uchar		*pixels;
	int			width;
	int			height;
	int			pixel_width;
	uchar		*to_free;
	char		soil_image;
}				t_texture;

typedef struct	s_block
{
	int			id;
	char		go_through;
	char		is_object;
	t_texture	*faces[4];
	t_texture	*obj_texture;
}				t_block;

typedef struct	s_map
{
	t_list2		textures;
	t_list2		blocks;
	t_list2		blocks_positions;
	t_texture	*floor;
	t_texture	*ceiling;
	int			width;
	int			height;
}				t_map;

typedef struct	s_player
{
	float		x;
	float		y;
	float		looking_dir;
}				t_player;

typedef struct	s_opts
{
	char		debug_mode;
	int			debug_block_size;
	char		big_mode;
	float		fov;
	float		hour_of_day;
}				t_opts;

typedef struct	s_wolf3d
{
	t_window	window;
	char		changed;
	t_timeval	last_frame;
	t_map		map;
	t_player	player;
	t_opts		opts;
}				t_wolf3d;

typedef struct	s_thread_data
{
	t_wolf3d	*wolf3d;
	int			from_x;
	int			until_x;
}				t_thread_data;

typedef struct	s_ray_result
{
	float		x;
	float		y;
	float		direction;
	int			block_x;
	int			block_y;
	t_block		*block;
	int			face;
	float		decal_in_face;
	float		distance;
}				t_ray_result;

typedef struct	s_config
{
	int			height;
	int			width;
	char		antialiasing;
}				t_config;

void			free_map(t_map *map);
int				exit_wolf3d(t_wolf3d *wolf3d);
void			set_color_at(t_wolf3d *wolf3d, int x, int y, int color);
void			safe_set_color_at(t_wolf3d *w, int x, int y, int color);
char			*copy_str(char *str);
void			normalize_decals(float *decal_x, float *decal_y);
char			equal_strings(char *str1, char *str2);
int				millis_since(struct timeval *start);
void			print_time_taken(struct timeval *start, char *before,
																char *after);
void			init_list(t_list2 *list, size_t elt_size);
void			*new_elt(t_list2 *lst);
void			remove_elt(t_list2 *lst, char *addr);
void			free_list(t_list2 *lst);
void			launch_thread(pthread_t *threads, t_thread_data *data, int i);
void			wait_for_threads_to_finish(pthread_t *threads);
char			endswith(char *str, char *end);
void			draw_line(t_wolf3d *w, int from[2], int to[2], int color);
void			safe_draw_line(t_wolf3d *w, int from[2], int to[2], int color);
void			draw_square(t_wolf3d *w, int from[2], int size, int color);
void			clear_screen(t_wolf3d *wolf3d);
void			draw_debug_grid(t_wolf3d *wolf3d);
void			draw_player_on_grid(t_wolf3d *wolf3d);
void			render_debug_ray(t_wolf3d *wolf3d, int pixel_x,
														t_ray_result *ray_res);
char			*read_tga(char *path, int *width, int *height,
															int *pixel_width);
int				expose_hook(void *param);
int				key_pressed_hook(int keycode, void *param);
int				key_released_hook(int keycode, void *param);
int				mouse_hook(int keycode, int x, int y, void *param);
int				mouse_move_hook(int x, int y, void *param);
void			apply_image_to_window(t_window *window);
char			init_window(t_window *window, int width, int height,
																char *title);
void			cpy_pixels_to_img(t_window *window);
char			interpret_map_file(t_wolf3d *wolf3d, t_value *map_json);
char			interpret_err(t_wolf3d *wolf3d, char *msg);
char			interpret_textures(t_wolf3d *wolf3d, t_value *textures);
char			interpret_blocks(t_wolf3d *wolf3d, t_value *blocks);
char			valid_block(t_value *block, char **error_msg);
void			send_ray_in_dir(t_wolf3d *wolf3d, float direction, int pixel_x,
																float from[2]);
t_texture		*find_texture(t_wolf3d *wolf3d, t_value *texture_name);
void			*compute_wolf3d_part(void *thread_data);

#endif