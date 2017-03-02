/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 18:11:45 by dbousque          #+#    #+#             */
/*   Updated: 2017/03/02 18:11:46 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myopengl.h"

GLfloat		g_quad_vertices[] = {
	-1.0f, 1.0f, 0.0f, 1.0f,
	-1.0f, -1.0f, 0.0f, 0.0f,
	1.0f, -1.0f, 1.0f, 0.0f,
	-1.0f, 1.0f, 0.0f, 1.0f,
	1.0f, -1.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 1.0f, 1.0f
};

t_globj		*make_screen_quad(void)
{
	t_globj	*quad;
	int		nb_vertices;
	int		attribs_struct[2];
	int		nb_attribs;

	nb_vertices = 6;
	attribs_struct[0] = 2;
	attribs_struct[1] = 2;
	nb_attribs = 2;
	if (!(quad = new_object(g_quad_vertices, nb_vertices,
											attribs_struct, nb_attribs)))
		return (NULL);
	return (quad);
}

void		setup_left_eye(void)
{
	GLenum	draw_buffers[1];

	glGenFramebuffers(1, &(g_conf.left_eye_framebuffer));
	glBindFramebuffer(GL_FRAMEBUFFER, g_conf.left_eye_framebuffer);
	glGenTextures(1, &(g_conf.left_eye_texture));
	glBindTexture(GL_TEXTURE_2D, g_conf.left_eye_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, g_conf.win_width, g_conf.win_height,
											0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glGenRenderbuffers(1, &(g_conf.left_eye_depthbuffer));
	glBindRenderbuffer(GL_RENDERBUFFER, g_conf.left_eye_depthbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT,
										g_conf.win_width, g_conf.win_height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
								GL_RENDERBUFFER, g_conf.left_eye_depthbuffer);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
												g_conf.left_eye_texture, 0);
	draw_buffers[0] = GL_COLOR_ATTACHMENT0;
	glDrawBuffers(1, draw_buffers);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		printf("Could not launch stereoscopic 3d.\n");
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void		setup_right_eye(void)
{
	GLenum	draw_buffers[1];

	glGenFramebuffers(1, &(g_conf.right_eye_framebuffer));
	glBindFramebuffer(GL_FRAMEBUFFER, g_conf.right_eye_framebuffer);
	glGenTextures(1, &(g_conf.right_eye_texture));
	glBindTexture(GL_TEXTURE_2D, g_conf.right_eye_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, g_conf.win_width, g_conf.win_height,
											0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glGenRenderbuffers(1, &(g_conf.right_eye_depthbuffer));
	glBindRenderbuffer(GL_RENDERBUFFER, g_conf.right_eye_depthbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT,
										g_conf.win_width, g_conf.win_height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
								GL_RENDERBUFFER, g_conf.right_eye_depthbuffer);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
												g_conf.right_eye_texture, 0);
	draw_buffers[0] = GL_COLOR_ATTACHMENT0;
	glDrawBuffers(1, draw_buffers);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		printf("Could not launch stereoscopic 3d.\n");
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void		setup_eyes(void)
{
	g_conf.left_eye_framebuffer = 0;
	setup_left_eye();
	g_conf.right_eye_framebuffer = 0;
	setup_right_eye();
}

void		set_left_eye(void)
{
	float	tmp_x;
	float	tmp_y;
	float	tmp_z;
	float	norm;

	if (g_conf.stereoscopic)
	{
		front_up_cross(&tmp_x, &tmp_y, &tmp_z);
		norm = get_norm(tmp_x, tmp_y, tmp_z);
		g_cam.x -= tmp_x / norm * g_cam.stereo_decal * 0.5;
		g_cam.y -= tmp_y / norm * g_cam.stereo_decal * 0.5;
		g_cam.z -= tmp_z / norm * g_cam.stereo_decal * 0.5;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, g_conf.left_eye_framebuffer);
	glBindTexture(GL_TEXTURE_2D, g_conf.left_eye_texture);
	glBindRenderbuffer(GL_RENDERBUFFER, g_conf.left_eye_depthbuffer);
	glViewport(0, 0, g_conf.win_width, g_conf.win_height);
}

void		set_right_eye(void)
{
	float	tmp_x;
	float	tmp_y;
	float	tmp_z;
	float	norm;

	if (g_conf.stereoscopic)
	{
		front_up_cross(&tmp_x, &tmp_y, &tmp_z);
		norm = get_norm(tmp_x, tmp_y, tmp_z);
		g_cam.x += tmp_x / norm * g_cam.stereo_decal * 0.5;
		g_cam.y += tmp_y / norm * g_cam.stereo_decal * 0.5;
		g_cam.z += tmp_z / norm * g_cam.stereo_decal * 0.5;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, g_conf.right_eye_framebuffer);
	glBindTexture(GL_TEXTURE_2D, g_conf.right_eye_texture);
	glBindRenderbuffer(GL_RENDERBUFFER, g_conf.right_eye_depthbuffer);
	glViewport(0, 0, g_conf.win_width, g_conf.win_height);
}

void		set_std_buffer(void)
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, g_conf.win_width, g_conf.win_height);
}

void		merge_two_eyes(void)
{
	GLint	loc;

	glUseProgram(g_conf.quad->shader->program);
	loc = glGetUniformLocation(g_conf.quad->shader->program, "twoText");
	glUniform1i(loc, g_conf.stereoscopic);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, g_conf.left_eye_texture);
	loc = glGetUniformLocation(g_conf.quad->shader->program, "text1");
	glUniform1i(loc, 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, g_conf.right_eye_texture);
	loc = glGetUniformLocation(g_conf.quad->shader->program, "text2");
	glUniform1i(loc, 1);
	draw_object(g_conf.quad->shader, g_conf.quad);
}

void		make_right_eye_view(t_list *objs, t_list *lights, t_mat *projection)
{
	t_mat		*view2;

	g_cam.yaw -= g_cam.stereo_decal_front * 30.0;
	update_camera();
	set_right_eye();
	update_camera();
	view2 = build_view();
	glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	set_lights(objs, lights, g_conf.texture_strength, g_conf.colors_strength);
	draw_objects(objs, view2, projection);
	draw_lights(lights, view2, projection);
}

void		main_loop2(t_list *objs, t_list *lights)
{
	t_mat		*view1;
	t_mat		*projection;

	projection = perspective(deg_to_rad(g_cam.fov),
				((float)g_conf.win_height) / g_conf.win_width, 0.1, 100.0);
	set_left_eye();
	if (g_conf.stereoscopic)
		g_cam.yaw += g_cam.stereo_decal_front * 30.0;
	update_camera();
	view1 = build_view();
	glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	set_lights(objs, lights, g_conf.texture_strength, g_conf.colors_strength);
	draw_objects(objs, view1, projection);
	draw_lights(lights, view1, projection);
	if (g_conf.stereoscopic)
		make_right_eye_view(objs, lights, projection);
}

void		main_loop(t_window *window, t_list *objs, t_list *lights)
{
	GLfloat		current_frame;
	GLfloat		last_frame;
	GLfloat		delta_time;

	while (!glfwWindowShouldClose(window->win))
	{
		glfwPollEvents();
		last_frame = current_frame;
		current_frame = glfwGetTime();
		delta_time = current_frame - last_frame;
		do_movement(delta_time, objs, lights);
		update_camera();
		main_loop2(objs, lights);
		set_std_buffer();
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		merge_two_eyes();
		g_conf.time_spent += glfwGetTime() - current_frame;
		update_stats();
		glfwSwapBuffers(window->win);
	}
}

void		add_environment3(void)
{
	g_conf.generic_textures[3] = new_obj_from_path(
								"environment/plate/plate.obj", 0);
	if (!g_conf.generic_textures[3])
		return ;
	load_texture_to_obj(g_conf.generic_textures[3],
											"environment/plate/diff.jpg");
	load_specular_map_to_obj(g_conf.generic_textures[3],
											"environment/plate/spec.jpg");
	load_normal_map_to_obj(g_conf.generic_textures[3],
											"environment/plate/normal.jpg");
	attach_shader_program_to_obj(g_conf.generic_textures[3], g_obj_program);
	g_conf.generic_textures[3]->specular_strength = 10.5;
	g_conf.generic_textures[3]->y = -2.0;
	g_conf.generic_textures[3]->scale = 7.0;
}

void		add_environment2(void)
{
	g_conf.generic_textures[2] = new_obj_from_path(
								"environment/parquet2/parquet2.obj", 0);
	if (!g_conf.generic_textures[2])
		return ;
	load_texture_to_obj(g_conf.generic_textures[2],
											"environment/parquet2/diff.jpg");
	load_specular_map_to_obj(g_conf.generic_textures[2],
											"environment/parquet2/spec.jpg");
	load_normal_map_to_obj(g_conf.generic_textures[2],
											"environment/parquet2/normal.jpg");
	attach_shader_program_to_obj(g_conf.generic_textures[2], g_obj_program);
	g_conf.generic_textures[2]->specular_strength = 5.5;
	g_conf.generic_textures[2]->y = -2.0;
	g_conf.generic_textures[2]->scale = 7.0;
	add_environment3();
}

void		add_environment1(void)
{
	g_conf.generic_textures[1] = new_obj_from_path(
								"environment/wall2/wall2.obj", 0);
	if (!g_conf.generic_textures[1])
		return ;
	load_texture_to_obj(g_conf.generic_textures[1],
											"environment/wall2/diff.png");
	load_specular_map_to_obj(g_conf.generic_textures[1],
											"environment/wall2/spec.png");
	load_normal_map_to_obj(g_conf.generic_textures[1],
											"environment/wall2/normal.png");
	attach_shader_program_to_obj(g_conf.generic_textures[1], g_obj_program);
	g_conf.generic_textures[1]->specular_strength = 1.5;
	g_conf.generic_textures[1]->y = -2.0;
	g_conf.generic_textures[1]->scale = 7.0;
	add_environment2();
}

void		add_environment(t_list *objs)
{
	g_conf.generic_textures[0] = new_obj_from_path(
								"environment/parquet/parquet.obj", 0);
	if (!g_conf.generic_textures[0])
		return ;
	load_texture_to_obj(g_conf.generic_textures[0],
											"environment/parquet/diff.png");
	load_specular_map_to_obj(g_conf.generic_textures[0],
											"environment/parquet/spec.png");
	load_normal_map_to_obj(g_conf.generic_textures[0],
											"environment/parquet/normal.png");
	attach_shader_program_to_obj(g_conf.generic_textures[0], g_obj_program);
	g_conf.generic_textures[0]->specular_strength = 3.5;
	g_conf.generic_textures[0]->y = -2.0;
	g_conf.generic_textures[0]->scale = 7.0;
	add_to_list(objs, &(g_conf.generic_textures[0]));
	add_environment1();
}

char		init_shaders(void)
{
	g_obj_program = new_shader_program("shaders/test1.vs", "shaders/test1.fs");
	if (!g_obj_program)
		return (0);
	g_light_program = new_shader_program("shaders/light.vs", "shaders/light.fs");
	if (!g_light_program)
		return (0);
	g_merge_program = new_shader_program("shaders/merge_stereo.vs", "shaders/merge_stereo.fs");
	if (!g_merge_program)
		return (0);
	return (1);
}

int			main(int argc, char **argv)
{
	t_window			*window;
	t_light				*light;
	t_list				*objs;
	t_list				*lights;

	if (argc != 2)
	{
		ft_putstr("format : ./scop <object_file>\n");
		return (-1);
	}
	setup_keys();
	setup_conf();
	init_camera();
	window = setup_window(g_conf.win_width, g_conf.win_height, "scop - dbousque");
	if (!window)
		return (-1);
	glEnable(GL_DEPTH_TEST);
	if (!init_shaders())
		return (-1);
	objs = new_list(sizeof(t_globj*));
	lights = new_list(sizeof(t_light*));
	if (!load_object_file(argv[1], objs))
	{
		printf("could not load .object file %s\n", argv[1]);
		return (-1);
	}
	add_environment(objs);
	light = new_std_light(1.0, 1.0, 1.0, 0.2);
	if (!light)
		return (-1);
	attach_shader_program_to_obj(light->obj, g_light_program);
	add_to_list(lights, &light);
	g_conf.quad = make_screen_quad();
	if (!g_conf.quad)
		return (-1);
	attach_shader_program_to_obj(g_conf.quad, g_merge_program);
	g_conf.info_updated_at = glfwGetTime();
	g_conf.frames_seen = 0;
	g_conf.time_spent = 0.0;
	setup_eyes();
	main_loop(window, objs, lights);
	return (0);
}
