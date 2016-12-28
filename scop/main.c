

#include "myopengl.h"

void	main_loop(t_window *window, t_list *objs, t_list *lights)
{
	GLfloat		current_frame;
	GLfloat		last_frame;
	GLfloat		delta_time;
	t_mat		*view;
	t_mat		*projection;

	while (!glfwWindowShouldClose(window->win))
	{
		glfwPollEvents();
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		last_frame = current_frame;
		current_frame = glfwGetTime();
		delta_time = current_frame - last_frame;
		do_movement(delta_time, objs, lights);
		update_camera();
		view = build_view();
		projection = perspective(deg_to_rad(g_cam.fov),
					((float)g_conf.win_height) / g_conf.win_width, 0.1, 100.0);
		set_lights(objs, lights, g_conf.texture_strength);
		draw_objects(objs, view, projection);
		draw_lights(lights, view, projection);
		g_conf.time_spent += glfwGetTime() - current_frame;
		update_stats();
		glfwSwapBuffers(window->win);
	}
}

int		main(void)
{
	t_window			*window;
	t_shader_program	*program;
	t_shader_program	*light_program;
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
	program = new_shader_program("shaders/test1.vs", "shaders/test1.fs");
	if (!program)
		return (-1);
	light_program = new_shader_program("shaders/light.vs", "shaders/light.fs");
	if (!light_program)
		return (-1);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	objs = new_list(sizeof(t_globj*));
	lights = new_list(sizeof(t_light*));
	//obj = new_obj_from_path("ressources/plane/Su-27_Flanker.obj");
	obj = new_obj_from_path("ressources/42.obj");
	if (!obj)
		return (-1);
	attach_shader_program_to_obj(obj, program);
	add_to_list(objs, &obj);
	light = new_std_light(1.0, 1.0, 1.0, 0.2);
	if (!light)
		return (-1);
	attach_shader_program_to_obj(light->obj, light_program);
	add_to_list(lights, &light);
	//attach_indices_to_obj(obj, indices, nb_indices);
	//load_texture_to_obj(obj, "ressources/plane/Su-27_Flanker_P01.png");
	load_texture_to_obj(obj, "wall.png");
	g_conf.info_updated_at = glfwGetTime();
	g_conf.frames_seen = 0;
	g_conf.time_spent = 0.0;
	main_loop(window, objs, lights);
	glfwTerminate();
	return (0);
}
