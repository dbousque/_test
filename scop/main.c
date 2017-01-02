

#include "myopengl.h"

void	main_loop(t_window *window, t_list *objs, t_list *lights)
{
	GLfloat		current_frame;
	GLfloat		last_frame;
	GLfloat		delta_time;
	t_mat		*view;
	t_mat		*projection;
	char		i;

	i = 0;
	while (!glfwWindowShouldClose(window->win))
	{
		if (i == 0)
		{
			g_conf.blue_strength = 0.0;
			g_conf.red_strength = 1.0;
			g_conf.green_strength = 0.0;
			g_cam.x -= 0.1;
			//g_cam.front_x += 50.0;
			i = 1;
		}
		else
		{
			g_conf.blue_strength = 1.0;
			g_conf.red_strength = 0.0;
			g_conf.green_strength = 1.0;
			g_cam.x += 0.1;
			//g_cam.front_x -= 50.0;
			i = 0;
		}
		glfwPollEvents();
		if (i == 0)
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}
		else
			glClearDepth(1);
		last_frame = current_frame;
		current_frame = glfwGetTime();
		delta_time = current_frame - last_frame;
		do_movement(delta_time, objs, lights);
		update_camera();
		view = build_view();
		projection = perspective(deg_to_rad(g_cam.fov),
					((float)g_conf.win_height) / g_conf.win_width, 0.1, 100.0);
		set_lights(objs, lights, g_conf.texture_strength, g_conf.colors_strength);
		draw_objects(objs, view, projection);
		draw_lights(lights, view, projection);
		g_conf.time_spent += glfwGetTime() - current_frame;
		update_stats();
		if (i == 1)
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
	float	planeCoefficients[] = {1.0, 0.0, 0.0, 0.0};
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGenfv(GL_S, GL_OBJECT_PLANE, planeCoefficients);
	glEnable(GL_TEXTURE_GEN_S);
	g_obj_program = new_shader_program("shaders/test1.vs", "shaders/test1.fs");
	if (!g_obj_program)
		return (-1);
	g_light_program = new_shader_program("shaders/light.vs", "shaders/light.fs");
	if (!g_light_program)
		return (-1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
	main_loop(window, objs, lights);
	return (0);
}
