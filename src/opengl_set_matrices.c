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

void	opengl_set_matrices(t_scop *sc)
{
	modify_uniform_matrice(sc, &sc->matrix_identity[0][0],
			"identity_matrix");
	opengl_set_model_matrices(sc);
	opengl_set_view_matrices(sc);
	opengl_set_projection_matrices(sc);
}

void	opengl_set_model_matrices(t_scop *sc)
{
	set_translation_matrix(sc,
			-sc->bounding_box_center.x,
			-sc->bounding_box_center.y,
			-sc->bounding_box_center.z);
	modify_uniform_matrice(sc, &sc->matrix_translation[0][0],
		"model_recenter_translation_matrix");
	set_translation_matrix(sc, 0.0, 0.0, -1.10);
	modify_uniform_matrice(sc, &sc->matrix_translation[0][0],
		"model_translation_matrix");
	set_scaling_matrix(sc, sc->zoom_level);
	modify_uniform_matrice(sc, &sc->matrix_scaling[0][0],
		"scaling_matrix");
	set_x_rotation_matrix(sc, 0.0);
	modify_uniform_matrice(sc, &sc->matrix_x_rotation[0][0],
		"rotation_x_matrix");
	set_y_rotation_matrix(sc, 0.0);
	modify_uniform_matrice(sc, &sc->matrix_y_rotation[0][0],
		"rotation_y_matrix");
	set_z_rotation_matrix(sc, 0.0);
	modify_uniform_matrice(sc, &sc->matrix_z_rotation[0][0],
		"rotation_z_matrix");
}

void	opengl_set_view_matrices(t_scop *sc)
{
	set_translation_matrix(sc, -sc->camera_pos.x, -sc->camera_pos.y,
							-sc->camera_pos.z);
	modify_uniform_matrice(sc, &sc->matrix_translation[0][0],
		"view_translation_matrix");
	modify_uniform_matrice(sc, &sc->matrix_view_orientation[0][0],
		"view_orientation_matrix");
}

void	opengl_set_projection_matrices(t_scop *sc)
{
	modify_uniform_matrice(sc, &sc->matrix_perspective_projection[0][0],
		"perspective_projection_matrix");
}
