/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_view.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 14:28:11 by aleung-c          #+#    #+#             */
/*   Updated: 2016/11/10 14:28:14 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

void	init_view_orientation_matrix(t_scop *sc)
{
	t_vec3		up_vec;
	t_vec3		xaxis;
	t_vec3		yaxis;
	t_vec3		zaxis;

	set_vec(&up_vec, 0.0, 1.0, 0.0);
	zaxis = normalize(vec_sub(sc->camera_lookat, sc->camera_pos));
	xaxis = normalize(vec_cross(up_vec, zaxis));
	yaxis = vec_cross(zaxis, xaxis);
	init_view_orientation_matrix_part2(sc, xaxis, yaxis, zaxis);
}

void	init_view_orientation_matrix_part2(t_scop *sc, t_vec3 xaxis,
										t_vec3 yaxis, t_vec3 zaxis)
{
	sc->matrix_view_orientation[0][0] = xaxis.x;
	sc->matrix_view_orientation[0][1] = xaxis.y;
	sc->matrix_view_orientation[0][2] = xaxis.z;
	sc->matrix_view_orientation[0][3] = 0.0;
	sc->matrix_view_orientation[1][0] = yaxis.x;
	sc->matrix_view_orientation[1][1] = yaxis.y;
	sc->matrix_view_orientation[1][2] = yaxis.z;
	sc->matrix_view_orientation[1][3] = 0.0;
	sc->matrix_view_orientation[2][0] = zaxis.x;
	sc->matrix_view_orientation[2][1] = zaxis.y;
	sc->matrix_view_orientation[2][2] = zaxis.z;
	sc->matrix_view_orientation[2][3] = 0.0;
	sc->matrix_view_orientation[3][0] = 0.0;
	sc->matrix_view_orientation[3][1] = 0.0;
	sc->matrix_view_orientation[3][2] = 0.0;
	sc->matrix_view_orientation[3][3] = 1.0;
}

/*
**	May not be totally accurate.
*/

void	init_view_translation_matrix(t_scop *sc)
{
	sc->matrix_view_translation[0][0] = 1.0;
	sc->matrix_view_translation[0][1] = 0.0;
	sc->matrix_view_translation[0][2] = 0.0;
	sc->matrix_view_translation[0][3] = -sc->camera_pos.x;
	sc->matrix_view_translation[1][0] = 0.0;
	sc->matrix_view_translation[1][1] = 1.0;
	sc->matrix_view_translation[1][2] = 0.0;
	sc->matrix_view_translation[1][3] = -sc->camera_pos.y;
	sc->matrix_view_translation[2][0] = 0.0;
	sc->matrix_view_translation[2][1] = 0.0;
	sc->matrix_view_translation[2][2] = 1.0;
	sc->matrix_view_translation[2][3] = -sc->camera_pos.z;
	sc->matrix_view_translation[3][0] = 0.0;
	sc->matrix_view_translation[3][1] = 0.0;
	sc->matrix_view_translation[3][2] = 0.0;
	sc->matrix_view_translation[3][3] = 1.0;
}
