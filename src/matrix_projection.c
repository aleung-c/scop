/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_projection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 15:28:14 by aleung-c          #+#    #+#             */
/*   Updated: 2016/11/10 15:28:16 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

void	init_perspective_projection_matrix(t_scop *sc)
{
	sc->camera_top = sc->camera_near * tan(M_PI / 180.0 * sc->camera_fov / 2);
	sc->camera_bottom = -sc->camera_top;
	sc->camera_right = sc->camera_top * sc->camera_aspect;
	sc->camera_left = -sc->camera_right;

	// ! column 1
	sc->matrix_perspective_projection[0][0] = (2 * sc->camera_near) / (sc->camera_right - sc->camera_left);
	sc->matrix_perspective_projection[0][1] = 0.0;
	sc->matrix_perspective_projection[0][2] = 0.0;
	sc->matrix_perspective_projection[0][3] = 0.0;

	// ! column 2
	sc->matrix_perspective_projection[1][0] = 0.0;
	sc->matrix_perspective_projection[1][1] = (2 * sc->camera_near) / (sc->camera_top - sc->camera_bottom);
	sc->matrix_perspective_projection[1][2] = 0.0;
	sc->matrix_perspective_projection[1][3] = 0.0;

	// ! column 3
	sc->matrix_perspective_projection[2][0] = (sc->camera_right + sc->camera_left) / (sc->camera_right - sc->camera_left);
	sc->matrix_perspective_projection[2][1] = (sc->camera_top + sc->camera_bottom) / (sc->camera_top - sc->camera_bottom);
	sc->matrix_perspective_projection[2][2] = -((sc->camera_far + sc->camera_near) / (sc->camera_far - sc->camera_near));
	sc->matrix_perspective_projection[2][3] = -1.0;

	// ! column 4
	sc->matrix_perspective_projection[3][0] = 0.0;
	sc->matrix_perspective_projection[3][1] = 0.0;
	sc->matrix_perspective_projection[3][2] = -((2 * sc->camera_far * sc->camera_near) / (sc->camera_far - sc->camera_near));
	sc->matrix_perspective_projection[3][3] = 0.0;
}