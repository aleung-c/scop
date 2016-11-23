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
	sc->using_array = 1;
	sc->transition_counter = 0;
	sc->transition_value = 0;
	sc->buffer_i = 0;
	glUniform1i(glGetUniformLocation(sc->main_shader_programme, "has_texture"), GL_FALSE);
}

void		event_process(t_scop *sc) // at each draw loop.
{
	GLint		uniform_mat; // matrice accessor.
	float		transition_color;

	// change val to rotate model.
	sc->i_axis += 0.005;
	// rotation process;
	if (sc->is_rotating == 1)
	{
		if (sc->is_rotating_x == 1 || sc->is_rotating_x == -1)
		{
			uniform_mat = glGetUniformLocation(sc->main_shader_programme, "rotation_x_matrix");
			if (uniform_mat != -1)
			{
				set_x_rotation_matrix(sc, sc->i_axis * sc->is_rotating_x);
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
		else if (sc->is_rotating_y == 1 || sc->is_rotating_y == -1)
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
				set_y_rotation_matrix(sc, sc->i_axis * sc->is_rotating_y);
				glUniformMatrix4fv(uniform_mat, 1, GL_FALSE, &sc->matrix_y_rotation[0][0]);
			}
			uniform_mat = glGetUniformLocation(sc->main_shader_programme, "rotation_z_matrix");
			if (uniform_mat != -1)
			{
				set_z_rotation_matrix(sc, 0.0);
				glUniformMatrix4fv(uniform_mat, 1, GL_FALSE, &sc->matrix_z_rotation[0][0]);
			}
		}
		else if (sc->is_rotating_z == 1 || sc->is_rotating_z == -1)
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
				set_z_rotation_matrix(sc, sc->i_axis * sc->is_rotating_z);
				glUniformMatrix4fv(uniform_mat, 1, GL_FALSE, &sc->matrix_z_rotation[0][0]);
			}
		}
	}

	transition_color = 0.0;
	if (sc->in_transition == 1)
	{
		transition_one_face(sc);
		if (sc->nb_vertices > 1000)
		{
			transition_one_face(sc);
			transition_one_face(sc);
			transition_one_face(sc);
		}
		if (sc->nb_vertices > 3000)
		{
			transition_one_face(sc);
			transition_one_face(sc);
			transition_one_face(sc);

			transition_one_face(sc);
			transition_one_face(sc);
			transition_one_face(sc);
		}


		glBindBuffer(GL_ARRAY_BUFFER, sc->tbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (sc->total_faces * 3), sc->transition_points, GL_STATIC_DRAW);

		sc->transition_counter++;
		
	}
	if (sc->buffer_i >= (sc->total_faces * 3))
	{
		sc->in_transition = 0;
		sc->on_standby = 1;
		//set bool for textures
		glUniform1i(glGetUniformLocation(sc->main_shader_programme, "has_texture"), GL_TRUE);
	}

}

void	transition_one_face(t_scop *sc)
{
	if (sc->buffer_i < (sc->total_faces * 3))
	{
		sc->transition_points[sc->buffer_i] = sc->transition_value;
		sc->buffer_i++;
	}
}
