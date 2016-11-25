/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_rotation_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 16:11:10 by aleung-c          #+#    #+#             */
/*   Updated: 2016/11/25 16:11:12 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

void	init_z_rotation_matrix(t_scop *sc)
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

void	set_z_rotation_matrix(t_scop *sc, float rot)
{
	sc->matrix_z_rotation[0][0] = cos(rot);
	sc->matrix_z_rotation[0][1] = sin(rot);
	sc->matrix_z_rotation[1][0] = -sin(rot);
	sc->matrix_z_rotation[1][1] = cos(rot);
}
