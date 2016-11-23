/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opengl_set_matrices.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 17:52:34 by aleung-c          #+#    #+#             */
/*   Updated: 2016/11/23 17:52:35 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

void opengl_set_matrices(t_scop *sc)
{
	// setting uniform values for model
	GLint uniform_mat = glGetUniformLocation(sc->main_shader_programme, "identity_matrix");
	if (uniform_mat != -1)
	{
		glUniformMatrix4fv(uniform_mat, 1, GL_FALSE, &sc->matrix_identity[0][0]);
	}
	uniform_mat = glGetUniformLocation(sc->main_shader_programme, "model_recenter_translation_matrix");
	if (uniform_mat != -1)
	{
		set_translation_matrix(sc,
			-sc->bounding_box_center.x,
			-sc->bounding_box_center.y,
			-sc->bounding_box_center.z);
		glUniformMatrix4fv(uniform_mat, 1, GL_FALSE, &sc->matrix_translation[0][0]);
	}

	uniform_mat = glGetUniformLocation(sc->main_shader_programme, "model_translation_matrix");
	if (uniform_mat != -1)
	{
		set_translation_matrix(sc, 0.0, 0.0, -1.10);
		glUniformMatrix4fv(uniform_mat, 1, GL_FALSE, &sc->matrix_translation[0][0]);
	}
	uniform_mat = glGetUniformLocation(sc->main_shader_programme, "scaling_matrix");
	if (uniform_mat != -1)
	{
		set_scaling_matrix(sc, 0.2);
		glUniformMatrix4fv(uniform_mat, 1, GL_FALSE, &sc->matrix_scaling[0][0]);
	}
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
		set_z_rotation_matrix(sc, 0.0);
		glUniformMatrix4fv(uniform_mat, 1, GL_FALSE, &sc->matrix_z_rotation[0][0]);
	}
	
	// setting uniform values for view (camera pos)
	uniform_mat = glGetUniformLocation(sc->main_shader_programme, "view_translation_matrix");
	if (uniform_mat != -1)
	{
		set_translation_matrix(sc, -sc->camera_pos.x, -sc->camera_pos.y, -sc->camera_pos.z); // setting camera pos.
		glUniformMatrix4fv(uniform_mat, 1, GL_FALSE, &sc->matrix_translation[0][0]);
	}

	uniform_mat = glGetUniformLocation(sc->main_shader_programme, "view_orientation_matrix");
	if (uniform_mat != -1)
	{
		glUniformMatrix4fv(uniform_mat, 1, GL_FALSE, &sc->matrix_view_orientation[0][0]);
	}
	
	// setting uniform value for projection
	uniform_mat = glGetUniformLocation(sc->main_shader_programme, "perspective_projection_matrix");
	if (uniform_mat != -1)
	{
		glUniformMatrix4fv(uniform_mat, 1, GL_FALSE, &sc->matrix_perspective_projection[0][0]);
	}
}
