/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myopengl.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 17:06:46 by dbousque          #+#    #+#             */
/*   Updated: 2017/03/02 17:06:48 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MYOPENGL_H
# define MYOPENGL_H

# define GLEW_STATIC
# include <GL/glew.h>
# include <GLFW/glfw3.h>
# ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <GLUT/glut.h>
#  include <OpenGL/glu.h>
# endif
# include "SOIL.h"
# include <stdio.h>
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "matrices.h"

# define MAX_SHADER_SIZE 	32768
# define READ_BUFFER_LEN 	4096

typedef struct			s_shader_program
{
	GLuint				vertex_shader;
	GLuint				fragment_shader;
	GLuint				program;
}						t_shader_program;

typedef struct			s_globj
{
	GLuint				vao1;
	GLuint				vbo1;
	GLuint				ebo1;
	GLuint				vao2;
	GLuint				vbo2;
	GLuint				ebo2;
	char				normal_mode;
	int					nb_vertices;
	int					nb_indices;
	char				has_indices;
	char				has_textures;
	GLuint				*textures;
	int					nb_textures;
	t_shader_program	*shader;
	float				x;
	float				y;
	float				z;
	GLuint				specular_map;
	GLuint				normal_map;
	char				has_specular_map;
	char				has_normal_map;
	float				specular_strength;
	float				scale;
}						t_globj;

typedef struct			s_window
{
	GLFWwindow			*win;
}						t_window;

typedef struct			s_camera
{
	float				x;
	float				y;
	float				z;
	float				front_x;
	float				front_y;
	float				front_z;
	float				up_x;
	float				up_y;
	float				up_z;
	float				speed;
	float				fov;
	float				pitch;
	float				yaw;
	float				roll;
	float				stereo_decal_front;
	float				stereo_decal;
}						t_camera;

typedef struct			s_list
{
	void				*elts;
	size_t				size;
	size_t				len;
	size_t				elt_size;
}						t_list;

typedef struct			s_objfile
{
	char				*objname;
	t_list				*vertices;
	t_list				*texture;
	t_list				*normals;
	t_list				*faces;
	t_list				*calc_normals;
}						t_objfile;

typedef struct			s_config
{
	char				lines;
	int					win_width;
	int					win_height;
	int					obj_ind;
	float				info_updated_at;
	float				time_spent;
	int					frames_seen;
	char				normal_mode;
	float				texture_strength;
	float				colors_strength;
	char				texture_plus;
	char				colors_plus;
	float				red_strength;
	float				green_strength;
	float				blue_strength;
	GLuint				left_eye_framebuffer;
	GLuint				right_eye_framebuffer;
	GLuint				left_eye_texture;
	GLuint				right_eye_texture;
	GLuint				left_eye_depthbuffer;
	GLuint				right_eye_depthbuffer;
	t_globj				*quad;
	char				stereoscopic;
	t_globj				*generic_textures[4];
	int					generic_textures_ind;
}						t_config;

typedef struct			s_light
{
	t_globj				*obj;
	float				r;
	float				g;
	float				b;
	float				ambient_strength;
}						t_light;

t_camera				g_cam;
char					g_keys[1024];
t_config				g_conf;
t_shader_program		*g_obj_program;
t_shader_program		*g_light_program;
t_shader_program		*g_merge_program;

t_list					*new_list(size_t elt_size);
void					add_to_list(t_list *lst, void *elt);
size_t					ft_strlen(char *str);
char					startswith(char *str, char *begin);
void					ft_putstr(char *str);
char					*ft_itoa(int n);
char					*ft_strconcat(char *st1, char *st2);
char					*read_file(char *filename, size_t max_size);
void					key_callback(GLFWwindow *window, int key, int scancode,
														int action, int mode);

void					calculate_raw_normals(GLfloat *v, int nb_vertices);
t_shader_program		*new_shader_program(char *vertex_shader_path,
												char *fragment_shader_path);
t_window				*setup_window(int width, int height, char *title_name);
void					draw_object(t_shader_program *shader_program,
																t_globj *obj);
t_globj					*new_object(GLfloat *vertices, int nb_vertices,
										int attribs_struct[], int nb_attribs);
void					load_texture_to_obj(t_globj *obj, char *img_path);
void					attach_indices_to_obj(t_globj *obj, GLuint indices[],
															int nb_indices);
void					attach_shader_program_to_obj(t_globj *obj,
													t_shader_program *shader);
t_objfile				*parse_objfile(char *path);
char					add_vertex(t_objfile *objfile, char *line,
															size_t line_nb);
char					add_face(t_objfile *objfile, char *line,
															size_t line_nb);
void					update_camera(void);
void					init_camera(void);
void					do_movement(GLfloat delta_time, t_list *objs,
															t_list *lights);
void					key_callback(GLFWwindow *window, int key, int scancode,
														int action, int mode);
void					setup_keys(void);
char					objfile_to_vertices(t_objfile *objfile,
										GLfloat **vertices, int *nb_vertices);
char					valid_int(char *line, char **end);
char					add_normal(t_objfile *objfile, char *line,
															size_t line_nb);
char					add_texture(t_objfile *objfile, char *line,
															size_t line_nb);
void					set_lights(t_list *objs, t_list *lights,
								float texture_strength, float colors_strength);
t_light					*new_std_light(float r, float g, float b,
													float ambient_strength);
float					adjust_obj(GLfloat *vertices, int nb_vertices);
t_mat					*build_view(void);
void					setup_conf(void);
void					draw_lights(t_list *lights, t_mat *view,
															t_mat *projection);
void					draw_objects(t_list *objs, t_mat *view,
															t_mat *projection);
t_globj					*new_obj_from_path(char *path, char main_obj);
void					update_stats(void);
void					load_specular_map_to_obj(t_globj *obj, char *img_path);
void					load_normal_map_to_obj(t_globj *obj, char *img_path);
void					front_up_cross(float *x, float *y, float *z);
char					load_object_file(char *filename, t_list *objs);

#endif
