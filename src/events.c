/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 15:20:50 by aleung-c          #+#    #+#             */
/*   Updated: 2016/11/21 15:20:53 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

void		event_init(t_scop *sc) // before the drawing loop.
{
	sc->i_axis = 0.0;
	sc->on_standby = 1;
	sc->is_rotating = 1;
	sc->is_rotating_x = 0;
	sc->is_rotating_y = 1;
	sc->is_rotating_z = 0;
}

void		event_process(t_scop *sc) // at each draw.
{
	GLint		uniform_mat; // matrice accessor.

	// change val to rotate model.
	sc->i_axis += 0.005;
	if (sc->is_rotating == 1)
	{
		if (sc->is_rotating_x == 1)
		{
			uniform_mat = glGetUniformLocation(sc->main_shader_programme, "rotation_x_matrix");
			if (uniform_mat != -1)
			{
				set_x_rotation_matrix(sc, sc->i_axis);
				glUniformMatrix4fv(uniform_mat, 1, GL_FALSE, &sc->matrix_x_rotation[0][0]);
			}
			uniform_mat = glGetUniformLocation(sc->main_shader_programme, "rotation_y_matrix");
			if (uniform_mat != -1)
			{
				set_y_rotation_matrix(sc, 0.0);
				glUniformMatrix4fv(uniform_mat, 1, GL_FALSE, &sc->matrix_y_rotation[0][0]);
			}
			uniform_mat = glGetUniformLocation(sc->main_shader_programme, "rotation_z_matrix");
			if (uniform_mat != -1)
			{
				set_z_rotation_matrix(sc, 0.0);
				glUniformMatrix4fv(uniform_mat, 1, GL_FALSE, &sc->matrix_z_rotation[0][0]);
			}
		}
		else if (sc->is_rotating_y == 1)
		{
			uniform_mat = glGetUniformLocation(sc->main_shader_programme, "rotation_x_matrix");
			if (uniform_mat != -1)
			{
				set_x_rotation_matrix(sc, 0.0);
				glUniformMatrix4fv(uniform_mat, 1, GL_FALSE, &sc->matrix_x_rotation[0][0]);
			}
			uniform_mat = glGetUniformLocation(sc->main_shader_programme, "rotation_y_matrix");
			if (uniform_mat != -1)
			{
				set_y_rotation_matrix(sc, sc->i_axis);
				glUniformMatrix4fv(uniform_mat, 1, GL_FALSE, &sc->matrix_y_rotation[0][0]);
			}
			uniform_mat = glGetUniformLocation(sc->main_shader_programme, "rotation_z_matrix");
			if (uniform_mat != -1)
			{
				set_z_rotation_matrix(sc, 0.0);
				glUniformMatrix4fv(uniform_mat, 1, GL_FALSE, &sc->matrix_z_rotation[0][0]);
			}
		}
		else if (sc->is_rotating_z == 1)
		{
			uniform_mat = glGetUniformLocation(sc->main_shader_programme, "rotation_x_matrix");
			if (uniform_mat != -1)
			{
				set_x_rotation_matrix(sc, 0.0);
				glUniformMatrix4fv(uniform_mat, 1, GL_FALSE, &sc->matrix_x_rotation[0][0]);
			}
			uniform_mat = glGetUniformLocation(sc->main_shader_programme, "rotation_y_matrix");
			if (uniform_mat != -1)
			{
				set_y_rotation_matrix(sc, 0.0);
				glUniformMatrix4fv(uniform_mat, 1, GL_FALSE, &sc->matrix_y_rotation[0][0]);
			}
			uniform_mat = glGetUniformLocation(sc->main_shader_programme, "rotation_z_matrix");
			if (uniform_mat != -1)
			{
				set_z_rotation_matrix(sc, sc->i_axis);
				glUniformMatrix4fv(uniform_mat, 1, GL_FALSE, &sc->matrix_z_rotation[0][0]);
			}
		}
	}
}
