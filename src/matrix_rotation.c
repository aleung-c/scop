/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 15:20:50 by aleung-c          #+#    #+#             */
/*   Updated: 2016/11/09 15:20:52 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

void init_x_rotation_matrix(t_scop *sc)
{
	sc->matrix_x_rotation[0][0] = 1.0;
	sc->matrix_x_rotation[0][1] = 0.0;
	sc->matrix_x_rotation[0][2] = 0.0;
	sc->matrix_x_rotation[0][3] = 0.0;

	sc->matrix_x_rotation[1][0] = 0.0;
	sc->matrix_x_rotation[1][1] = cos(0.0);
	sc->matrix_x_rotation[1][2] = sin(0.0);
	sc->matrix_x_rotation[1][3] = 0.0;

	sc->matrix_x_rotation[2][0] = 0.0;
	sc->matrix_x_rotation[2][1] = -sin(0.0);
	sc->matrix_x_rotation[2][2] = cos(0.0);
	sc->matrix_x_rotation[2][3] = 0.0;

	sc->matrix_x_rotation[3][0] = 0.0;
	sc->matrix_x_rotation[3][1] = 0.0;
	sc->matrix_x_rotation[3][2] = 0.0;
	sc->matrix_x_rotation[3][3] = 1.0;
}

void set_x_rotation_matrix(t_scop *sc, float rot)
{
	sc->matrix_x_rotation[1][1] = cos(rot);
	sc->matrix_x_rotation[1][2] = sin(rot);
	sc->matrix_x_rotation[2][1] = -sin(rot);
	sc->matrix_x_rotation[2][2] = cos(rot);
}

void init_y_rotation_matrix(t_scop *sc)
{
	sc->matrix_y_rotation[0][0] = cos(0.0);
	sc->matrix_y_rotation[0][1] = 0.0;
	sc->matrix_y_rotation[0][2] = -sin(0.0);
	sc->matrix_y_rotation[0][3] = 0.0;

	sc->matrix_y_rotation[1][0] = 0.0;
	sc->matrix_y_rotation[1][1] = 1.0;
	sc->matrix_y_rotation[1][2] = 0.0;
	sc->matrix_y_rotation[1][3] = 0.0;

	sc->matrix_y_rotation[2][0] = sin(0.0);
	sc->matrix_y_rotation[2][1] = 0.0;
	sc->matrix_y_rotation[2][2] = cos(0.0);
	sc->matrix_y_rotation[2][3] = 0.0;

	sc->matrix_y_rotation[3][0] = 0.0;
	sc->matrix_y_rotation[3][1] = 0.0;
	sc->matrix_y_rotation[3][2] = 0.0;
	sc->matrix_y_rotation[3][3] = 1.0;
}

void set_y_rotation_matrix(t_scop *sc, float rot)
{
	sc->matrix_y_rotation[0][0] = cos(rot);
	sc->matrix_y_rotation[0][2] = -sin(rot);
	sc->matrix_y_rotation[2][0] = sin(rot);
	sc->matrix_y_rotation[2][2] = cos(rot);
}

void init_z_rotation_matrix(t_scop *sc)
{
	sc->matrix_z_rotation[0][0] = cos(0.0);
	sc->matrix_z_rotation[0][1] = sin(0.0);
	sc->matrix_z_rotation[0][2] = 0.0;
	sc->matrix_z_rotation[0][3] = 0.0;

	sc->matrix_z_rotation[1][0] = -sin(0.0);
	sc->matrix_z_rotation[1][1] = cos(0.0);
	sc->matrix_z_rotation[1][2] = 0.0;
	sc->matrix_z_rotation[1][3] = 0.0;

	sc->matrix_z_rotation[2][0] = 0.0;
	sc->matrix_z_rotation[2][1] = 0.0;
	sc->matrix_z_rotation[2][2] = 1.0;
	sc->matrix_z_rotation[2][3] = 0.0;

	sc->matrix_z_rotation[3][0] = 0.0;
	sc->matrix_z_rotation[3][1] = 0.0;
	sc->matrix_z_rotation[3][2] = 0.0;
	sc->matrix_z_rotation[3][3] = 1.0;
}

void set_z_rotation_matrix(t_scop *sc, float rot)
{
	sc->matrix_z_rotation[0][0] = cos(rot);
	sc->matrix_z_rotation[0][1] = sin(rot);
	sc->matrix_z_rotation[1][0] = -sin(rot);
	sc->matrix_z_rotation[1][1] = cos(rot);
}
