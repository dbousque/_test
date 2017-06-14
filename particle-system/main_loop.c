/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 13:57:41 by dbousque          #+#    #+#             */
/*   Updated: 2017/03/03 13:57:43 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myopengl.h"

void		set_std_buffer(void)
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, g_conf.win_width, g_conf.win_height);
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

void		main_loop(t_window *window, t_list *objs)
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
