/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 18:11:26 by dbousque          #+#    #+#             */
/*   Updated: 2017/03/02 18:11:28 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (key == GLFW_KEY_N && action == GLFW_PRESS)
		g_conf.obj_ind++;
	if (key == GLFW_KEY_M && action == GLFW_PRESS)
		g_conf.normal_mode = g_conf.normal_mode == 0 ? 1 : 0;
	if (key == GLFW_KEY_T && action == GLFW_PRESS)
	{
		if (!g_conf.texture_plus && !g_conf.colors_plus)
			g_conf.colors_plus = 1;
		else if (g_conf.colors_plus)
		{
			g_conf.colors_plus = 0;
			g_conf.texture_plus = 1;
		}
		else if (g_conf.texture_plus)
			g_conf.texture_plus = 0;
	}
	if (key == GLFW_KEY_G && action == GLFW_PRESS)
		g_conf.generic_textures_ind++;
	if (key == GLFW_KEY_J && action == GLFW_PRESS)
		g_conf.stereoscopic = g_conf.stereoscopic ? 0 : 1;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void	do_movement3(GLfloat delta_time, t_list *objs, t_list *lights)
{
	(void)objs;
	(void)lights;
	if (g_keys[GLFW_KEY_KP_ADD])
	{
		((t_globj**)objs->elts)[0]->scale += delta_time
								* ((t_globj**)objs->elts)[0]->scale * 0.5;
	}
	if (g_keys[GLFW_KEY_KP_SUBTRACT])
	{
		((t_globj**)objs->elts)[0]->scale -= delta_time
								* ((t_globj**)objs->elts)[0]->scale * 0.5;
	}
	if (g_keys[GLFW_KEY_MINUS])
		g_cam.stereo_decal -= delta_time * 1.0;
	if (g_keys[GLFW_KEY_EQUAL])
		g_cam.stereo_decal += delta_time * 1.0;
	if (g_keys[GLFW_KEY_LEFT_BRACKET])
		g_cam.stereo_decal_front -= delta_time * 0.1;
	if (g_keys[GLFW_KEY_RIGHT_BRACKET])
		g_cam.stereo_decal_front += delta_time * 0.1;
	if (g_cam.stereo_decal_front < 0.0)
		g_cam.stereo_decal_front = 0.0;
	if (g_cam.stereo_decal < 0.0)
		g_cam.stereo_decal = 0.0;
	if (g_conf.texture_plus)
	{
		g_conf.texture_strength += 1.0 * delta_time;
		if (g_conf.texture_strength > 1.0)
			g_conf.texture_strength = 1.0;
	}
	else
	{
		g_conf.texture_strength -= 1.0 * delta_time;
		if (g_conf.texture_strength < 0.0)
			g_conf.texture_strength = 0.0;
	}
	if (g_conf.colors_plus)
	{
		g_conf.colors_strength += 1.0 * delta_time;
		if (g_conf.colors_strength > 1.0)
			g_conf.colors_strength = 1.0;
	}
	else
	{
		g_conf.colors_strength -= 1.0 * delta_time;
		if (g_conf.colors_strength < 0.0)
			g_conf.colors_strength = 0.0;
	}
}

void	front_up_cross(float *x, float *y, float *z)
{
	*x = (g_cam.front_y * g_cam.up_z) - (g_cam.front_z * g_cam.up_y);
	*y = (g_cam.front_z * g_cam.up_x) - (g_cam.front_x * g_cam.up_z);
	*z = (g_cam.front_x * g_cam.up_y) - (g_cam.front_y * g_cam.up_x);
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
	t_light		*sel_light;

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
	if (g_keys[GLFW_KEY_1] && g_conf.obj_ind > (int)objs->len)
	{
		sel_light = ((t_light**)lights->elts)[g_conf.obj_ind - (int)objs->len - 1];
		sel_light->r -= 1.0 * delta_time;
		if (sel_light->r < 0.0)
			sel_light->r = 0.0;
	}
	if (g_keys[GLFW_KEY_2] && g_conf.obj_ind > (int)objs->len)
	{
		sel_light = ((t_light**)lights->elts)[g_conf.obj_ind - (int)objs->len - 1];
		sel_light->g -= 1.0 * delta_time;
		if (sel_light->g < 0.0)
			sel_light->g = 0.0;
	}
	if (g_keys[GLFW_KEY_3] && g_conf.obj_ind > (int)objs->len)
	{
		sel_light = ((t_light**)lights->elts)[g_conf.obj_ind - (int)objs->len - 1];
		sel_light->b -= 1.0 * delta_time;
		if (sel_light->b < 0.0)
			sel_light->b = 0.0;
	}
	if (g_keys[GLFW_KEY_4] && g_conf.obj_ind > (int)objs->len)
	{
		sel_light = ((t_light**)lights->elts)[g_conf.obj_ind - (int)objs->len - 1];
		sel_light->r += 1.0 * delta_time;
		if (sel_light->r > 1.0)
			sel_light->r = 1.0;
	}
	if (g_keys[GLFW_KEY_5] && g_conf.obj_ind > (int)objs->len)
	{
		sel_light = ((t_light**)lights->elts)[g_conf.obj_ind - (int)objs->len - 1];
		sel_light->g += 1.0 * delta_time;
		if (sel_light->g > 1.0)
			sel_light->g = 1.0;
	}
	if (g_keys[GLFW_KEY_6] && g_conf.obj_ind > (int)objs->len)
	{
		sel_light = ((t_light**)lights->elts)[g_conf.obj_ind - (int)objs->len - 1];
		sel_light->b += 1.0 * delta_time;
		if (sel_light->b > 1.0)
			sel_light->b = 1.0;
	}
	do_movement3(delta_time, objs, lights);
}

void	do_movement(GLfloat delta_time, t_list *objs, t_list *lights)
{
	t_globj				*sel_obj;
	t_light				*light;

	if (g_conf.obj_ind > (int)(objs->len + lights->len))
		g_conf.obj_ind = 0;
	obj_movement(delta_time, objs, lights);
	if (g_keys[GLFW_KEY_M])
	{
		if (g_conf.obj_ind > 0 && (size_t)g_conf.obj_ind <= objs->len)
		{
			sel_obj = ((t_globj**)objs->elts)[g_conf.obj_ind - 1];
			sel_obj->normal_mode = sel_obj->normal_mode == 0 ? 1 : 0;
		}
		g_keys[GLFW_KEY_M] = 0;
	}
	if (g_keys[GLFW_KEY_P] && lights->len < 10)
	{
		light = new_std_light(1.0, 1.0, 1.0, 0.2);
		if (light)
		{
			attach_shader_program_to_obj(light->obj, g_light_program);
			add_to_list(lights, &light);
		}
		g_keys[GLFW_KEY_P] = 0;
	}
	if (g_conf.generic_textures_ind >= 4)
		g_conf.generic_textures_ind = 0;
	((t_globj**)objs->elts)[objs->len - 1] =
						g_conf.generic_textures[g_conf.generic_textures_ind];
	if (g_keys[GLFW_KEY_Z])
		g_cam.fov += 80.0 * g_cam.speed * delta_time;
	if (g_keys[GLFW_KEY_X])
		g_cam.fov -= 80.0 * g_cam.speed * delta_time;
	do_movement2(delta_time, objs, lights);
}
