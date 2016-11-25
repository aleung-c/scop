/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 16:16:37 by aleung-c          #+#    #+#             */
/*   Updated: 2016/11/25 16:16:39 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

void	toggle_rotation(t_scop *sc, int key, int action)
{
	if (key == GLFW_KEY_F && action == GLFW_PRESS)
	{
		if (sc->is_rotating == 1)
			sc->is_rotating = 0;
		else
			sc->is_rotating = 1;
	}
}

void	toggle_rotation_change_1(t_scop *sc, int key, int action)
{
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		sc->is_rotating_x = -1;
		sc->is_rotating_y = 0;
		sc->is_rotating_z = 0;
	}
	else if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
		sc->is_rotating_x = 1;
		sc->is_rotating_y = 0;
		sc->is_rotating_z = 0;
	}
}

void	toggle_rotation_change_2(t_scop *sc, int key, int action)
{
	if (key == GLFW_KEY_A && action == GLFW_PRESS)
	{
		sc->is_rotating_x = 0;
		sc->is_rotating_y = -1;
		sc->is_rotating_z = 0;
	}
	else if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		sc->is_rotating_x = 0;
		sc->is_rotating_y = 1;
		sc->is_rotating_z = 0;
	}
	else if (key == GLFW_KEY_Q && action == GLFW_PRESS)
	{
		sc->is_rotating_x = 0;
		sc->is_rotating_y = 0;
		sc->is_rotating_z = 1;
	}
	else if (key == GLFW_KEY_E && action == GLFW_PRESS)
	{
		sc->is_rotating_x = 0;
		sc->is_rotating_y = 0;
		sc->is_rotating_z = -1;
	}
}

void	toggle_transition_and_tswitch(t_scop *sc, int key, int action)
{
	if (key == GLFW_KEY_R && action == GLFW_PRESS && sc->on_standby == 1)
	{
		sc->on_standby = 0;
		sc->in_transition = 1;
		sc->buffer_i = 0;
		if (sc->transition_value == 0)
			sc->transition_value = 1;
		else
			sc->transition_value = 0;
	}
	else if (key == GLFW_KEY_G && action == GLFW_PRESS)
	{
		if (sc->cur_texture_id == 0)
			sc->cur_texture_id = 1;
		else
			sc->cur_texture_id = 0;
		glUniform1i(glGetUniformLocation(sc->main_shader_programme,
			"texture_id"), sc->cur_texture_id);
	}
}

void	set_zoom_level(t_scop *sc, int key, int action)
{
	if (key == GLFW_KEY_C && action == GLFW_PRESS)
	{
		if (sc->zoom_level > 0.01f)
			sc->zoom_level -= 0.01f;
		if (fabsf(sc->zoom_level - (float)0.0) < (float)0.0000001)
			sc->zoom_level = 0.05f;
		set_scaling_matrix(sc, sc->zoom_level);
		modify_uniform_matrice(sc, &sc->matrix_scaling[0][0],
			"scaling_matrix");
	}
	else if (key == GLFW_KEY_V && action == GLFW_PRESS)
	{
		if (sc->zoom_level < 2.0)
			sc->zoom_level += 0.05;
		set_scaling_matrix(sc, sc->zoom_level);
		modify_uniform_matrice(sc, &sc->matrix_scaling[0][0],
			"scaling_matrix");
	}
}
