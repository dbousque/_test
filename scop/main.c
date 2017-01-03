

#include "myopengl.h"

t_globj	*make_screen_quad(void)
{
	GLfloat vertices[] = {
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };
	t_globj	*quad;
	int		nb_vertices = 6;
	int		attribs_struct[] = {2, 2};
	int		nb_attribs = 2;

	if (!(quad = new_object(vertices, nb_vertices, attribs_struct, nb_attribs)))
		return (NULL);
	return (quad);
}

void	setup_left_eye(void)
{
	GLenum	draw_buffers[1];

	g_conf.left_eye_framebuffer = 0;
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
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		printf("Could not launch stereoscopic 3d.\n");
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void	setup_right_eye(void)
{
	GLenum	draw_buffers[1];

	g_conf.right_eye_framebuffer = 0;
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
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		printf("Could not launch stereoscopic 3d.\n");
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void	setup_eyes(void)
{
	setup_left_eye();
	setup_right_eye();
}

void	set_left_eye(void)
{
	if (g_conf.stereoscopic)
		g_cam.x -= 0.1;
	glBindFramebuffer(GL_FRAMEBUFFER, g_conf.left_eye_framebuffer);
	glBindTexture(GL_TEXTURE_2D, g_conf.left_eye_texture);
	glBindRenderbuffer(GL_RENDERBUFFER, g_conf.left_eye_depthbuffer);
	glViewport(0, 0, g_conf.win_width, g_conf.win_height);
}

void	set_right_eye(void)
{
	g_cam.x += 0.1;
	glBindFramebuffer(GL_FRAMEBUFFER, g_conf.right_eye_framebuffer);
	glBindTexture(GL_TEXTURE_2D, g_conf.right_eye_texture);
	glBindRenderbuffer(GL_RENDERBUFFER, g_conf.right_eye_depthbuffer);
	glViewport(0, 0, g_conf.win_width, g_conf.win_height);
}

void	set_std_buffer(void)
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, g_conf.win_width, g_conf.win_height);
}

void	merge_two_eyes(void)
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
	glUniform1i(loc, 0);

	glBindTexture(GL_TEXTURE_2D, 0);

	draw_object(g_conf.quad->shader, g_conf.quad);
}

void	main_loop(t_window *window, t_list *objs, t_list *lights)
{
	GLfloat		current_frame;
	GLfloat		last_frame;
	GLfloat		delta_time;
	t_mat		*view1;
	t_mat		*view2;
	t_mat		*projection;

	while (!glfwWindowShouldClose(window->win))
	{
		glfwPollEvents();
		last_frame = current_frame;
		current_frame = glfwGetTime();
		delta_time = current_frame - last_frame;
		do_movement(delta_time, objs, lights);
		update_camera();
		if (g_conf.stereoscopic)
			g_cam.front_x += 0.3;
		printf("%f\n", g_cam.front_x);
		view1 = build_view();
		if (g_conf.stereoscopic)
		{
			g_cam.front_x -= 0.3;
			printf("%f\n", g_cam.front_x);
			view2 = build_view();
		}
		projection = perspective(deg_to_rad(g_cam.fov),
					((float)g_conf.win_height) / g_conf.win_width, 0.1, 100.0);

		set_left_eye();
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		set_lights(objs, lights, g_conf.texture_strength, g_conf.colors_strength);
		draw_objects(objs, view1, projection);
		draw_lights(lights, view1, projection);

		if (g_conf.stereoscopic)
		{
			set_right_eye();
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			set_lights(objs, lights, g_conf.texture_strength, g_conf.colors_strength);
			draw_objects(objs, view2, projection);
			draw_lights(lights, view2, projection);
		}

		set_std_buffer();
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		merge_two_eyes();

		g_conf.time_spent += glfwGetTime() - current_frame;
		update_stats();
		glfwSwapBuffers(window->win);
	}
}

int		main(void)
{
	t_window			*window;
	t_globj				*obj;
	t_light				*light;
	t_list				*objs;
	t_list				*lights;

	setup_keys();
	setup_conf();
	init_camera();
	window = setup_window(g_conf.win_width, g_conf.win_height, "scop - dbousque");
	if (!window)
		return (-1);
	glEnable(GL_DEPTH_TEST);
	g_obj_program = new_shader_program("shaders/test1.vs", "shaders/test1.fs");
	if (!g_obj_program)
		return (-1);
	g_light_program = new_shader_program("shaders/light.vs", "shaders/light.fs");
	if (!g_light_program)
		return (-1);
	g_merge_program = new_shader_program("shaders/merge_stereo.vs", "shaders/merge_stereo.fs");
	if (!g_merge_program)
		return (-1);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	objs = new_list(sizeof(t_globj*));
	lights = new_list(sizeof(t_light*));
	//obj = new_obj_from_path("ressources/plane/Su-27_Flanker.obj");
	obj = new_obj_from_path("ressources/42.obj");
	if (!obj)
		return (-1);
	attach_shader_program_to_obj(obj, g_obj_program);
	add_to_list(objs, &obj);
	light = new_std_light(1.0, 1.0, 1.0, 0.2);
	if (!light)
		return (-1);
	attach_shader_program_to_obj(light->obj, g_light_program);
	add_to_list(lights, &light);
	g_conf.quad = make_screen_quad();
	if (!g_conf.quad)
		return (-1);
	attach_shader_program_to_obj(g_conf.quad, g_merge_program);
	//attach_indices_to_obj(obj, indices, nb_indices);
	//load_texture_to_obj(obj, "ressources/plane/Su-27_Flanker_P01.png");
	obj->specular_strength = 10.5;
	//load_texture_to_obj(obj, "ressources/teeth/teeth_diff.png");
	//load_specular_map_to_obj(obj, "ressources/teeth/teeth_spec.png");
	//load_normal_map_to_obj(obj, "ressources/teeth/teeth_normal.png");
	load_texture_to_obj(obj, "wall2.jpg");
	load_specular_map_to_obj(obj, "wall2_specular.jpg");
	load_normal_map_to_obj(obj, "wall2_normal.jpg");
	//load_texture_to_obj(obj, "ressources/plane/Su-27_Flanker_P01.png");
	//load_specular_map_to_obj(obj, "ressources/plane/Su-27_Flanker_S2.png");
	//load_normal_map_to_obj(obj, "ressources/plane/Su-27_Flanker_N.png");
	//load_texture_to_obj(obj, "ressources/pouf/diff.jpg");
	//load_specular_map_to_obj(obj, "ressources/pouf/spec.jpg");
	//load_normal_map_to_obj(obj, "ressources/pouf/normal.png");
	g_conf.info_updated_at = glfwGetTime();
	g_conf.frames_seen = 0;
	g_conf.time_spent = 0.0;
	setup_eyes();
	main_loop(window, objs, lights);
	return (0);
}
