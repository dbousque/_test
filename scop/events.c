

#include "myopengl.h"

void	setup_keys(void)
{
	int		i;

	i = 0;
	while (i < 1024)
	{
		g_keys[i] = 0;
		i++;
	}
}


void    key_callback(GLFWwindow *window, int key, int scancode, int action,
																	int mode)
{
	(void)scancode;
	(void)mode;
	if (action == GLFW_PRESS)
		g_keys[key] = 1;
	if (action == GLFW_RELEASE)
		g_keys[key] = 0;
	if (key == GLFW_KEY_L && action == GLFW_PRESS)
	{
		if (g_conf.lines)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			g_conf.lines = 0;
		}
		else
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			g_conf.lines = 1;
		}

	}
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void	front_up_cross(float *x, float *y, float *z)
{
	*x = (g_cam.front_y * g_cam.up_z) - (g_cam.front_z * g_cam.up_y);
	*y = (g_cam.front_z * g_cam.up_x) - (g_cam.front_x * g_cam.up_z);
	*z = (g_cam.front_x * g_cam.up_y) - (g_cam.front_y * g_cam.up_x);
}

void	do_movement3(GLfloat delta_time, t_list *objs, t_list *lights)
{
	if (g_keys[GLFW_KEY_KP_ADD])
		g_conf.obj_scale += delta_time * (g_conf.obj_scale * 0.5);
	if (g_keys[GLFW_KEY_KP_SUBTRACT])
		g_conf.obj_scale -= delta_time * (g_conf.obj_scale * 0.5);
	if (g_keys[GLFW_KEY_N])
	{
		if (g_conf.obj_ind >= (int)(objs->len + lights->len))
			g_conf.obj_ind = 0;
		else
			g_conf.obj_ind++;
	}
}

void	obj_movement(GLfloat delta_time, t_list *objs, t_list *lights)
{
	float		norm;
	float		tmp_x;
	float		tmp_y;
	float		tmp_z;
	t_globj		*obj;

	if (g_conf.obj_ind > 0)
	{
		if (g_conf.obj_ind <= (int)objs->len)
			obj = ((t_globj**)objs->elts)[g_conf.obj_ind - 1];
		else
			obj = ((t_light**)lights->elts)[g_conf.obj_ind - 1 - objs->len]->obj;
	}
	if (g_keys[GLFW_KEY_A])
	{
		if (g_conf.obj_ind == 0)
		{
			front_up_cross(&tmp_x, &tmp_y, &tmp_z);
			norm = get_norm(tmp_x, tmp_y, tmp_z);
			g_cam.x -= tmp_x / norm * g_cam.speed * delta_time;
			g_cam.y -= tmp_y / norm * g_cam.speed * delta_time;
			g_cam.z -= tmp_z / norm * g_cam.speed * delta_time;
		}
		else
			obj->x -= 2.0 * g_cam.speed * delta_time;
	}
	if (g_keys[GLFW_KEY_D])
	{
		if (g_conf.obj_ind == 0)
		{
			front_up_cross(&tmp_x, &tmp_y, &tmp_z);
			norm = get_norm(tmp_x, tmp_y, tmp_z);
			g_cam.x += tmp_x / norm * g_cam.speed * delta_time;
			g_cam.y += tmp_y / norm * g_cam.speed * delta_time;
			g_cam.z += tmp_z / norm * g_cam.speed * delta_time;
		}
		else
			obj->x += 2.0 * g_cam.speed * delta_time;
	}
	if (g_keys[GLFW_KEY_W])
	{
		if (g_conf.obj_ind == 0)
		{
			g_cam.x += g_cam.speed * g_cam.front_x * delta_time;
			g_cam.y += g_cam.speed * g_cam.front_y * delta_time;
			g_cam.z += g_cam.speed * g_cam.front_z * delta_time;
		}
		else
			obj->z -= 2.0 * g_cam.speed * delta_time;
	}
	if (g_keys[GLFW_KEY_S])
	{
		if (g_conf.obj_ind == 0)
		{
			g_cam.x -= g_cam.speed * g_cam.front_x * delta_time;
			g_cam.y -= g_cam.speed * g_cam.front_y * delta_time;
			g_cam.z -= g_cam.speed * g_cam.front_z * delta_time;
		}
		else
			obj->z += 2.0 * g_cam.speed * delta_time;
	}
	if (g_keys[GLFW_KEY_E])
	{
		if (g_conf.obj_ind == 0)
			g_cam.y += 2.0 * g_cam.speed * delta_time;
		else
			obj->y += 2.0 * g_cam.speed * delta_time;
	}
	if (g_keys[GLFW_KEY_Q])
	{
		if (g_conf.obj_ind == 0)
			g_cam.y -= 2.0 * g_cam.speed * delta_time;
		else
			obj->y -= 2.0 * g_cam.speed * delta_time;
	}
}

void	do_movement2(GLfloat delta_time, t_list *objs, t_list *lights)
{
	if (g_keys[GLFW_KEY_C])
		g_cam.roll -= 20 * g_cam.speed * delta_time;
	if (g_keys[GLFW_KEY_V])
		g_cam.roll += 20 * g_cam.speed * delta_time;
	if (g_keys[GLFW_KEY_UP])
		g_cam.pitch += 20 * g_cam.speed * delta_time;
	if (g_keys[GLFW_KEY_DOWN])
		g_cam.pitch -= 20 * g_cam.speed * delta_time;
	if (g_keys[GLFW_KEY_RIGHT])
		g_cam.yaw += 20 * g_cam.speed * delta_time;
	if (g_keys[GLFW_KEY_LEFT])
		g_cam.yaw -= 20 * g_cam.speed * delta_time;
	do_movement3(delta_time, objs, lights);
}

void	do_movement(GLfloat delta_time, t_list *objs, t_list *lights)
{
	obj_movement(delta_time, objs, lights);
	if (g_keys[GLFW_KEY_Z])
		g_cam.fov += 80.0 * g_cam.speed * delta_time;
	if (g_keys[GLFW_KEY_X])
		g_cam.fov -= 80.0 * g_cam.speed * delta_time;
	do_movement2(delta_time, objs, lights);
}