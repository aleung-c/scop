/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_rotations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 13:52:48 by aleung-c          #+#    #+#             */
/*   Updated: 2016/11/25 13:52:50 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

void	events_rotations(t_scop *sc)
{
	if (sc->is_rotating == 1)
	{
		sc->i_axis += 0.005;
		set_x_rotation_matrix(sc, sc->i_axis * sc->is_rotating_x);
		modify_uniform_matrice(sc, &sc->matrix_x_rotation[0][0],
			"rotation_x_matrix");
		set_y_rotation_matrix(sc, sc->i_axis * sc->is_rotating_y);
		modify_uniform_matrice(sc, &sc->matrix_y_rotation[0][0],
			"rotation_y_matrix");
		set_z_rotation_matrix(sc, sc->i_axis * sc->is_rotating_z);
		modify_uniform_matrice(sc, &sc->matrix_z_rotation[0][0],
			"rotation_z_matrix");
	}
}

void	modify_uniform_matrice(t_scop *sc, float *matrice, char *uniform_string)
{
	GLint		uniform_mat;

	uniform_mat = glGetUniformLocation(sc->main_shader_programme,
										uniform_string);
	if (uniform_mat != -1)
	{
		glUniformMatrix4fv(uniform_mat, 1, GL_FALSE, matrice);
	}
}
