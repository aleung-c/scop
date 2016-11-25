/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_scaling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 18:38:21 by aleung-c          #+#    #+#             */
/*   Updated: 2016/11/08 18:38:24 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

void	init_scaling_matrix(t_scop *sc)
{
	sc->matrix_scaling[0][0] = 1.0;
	sc->matrix_scaling[0][1] = 0.0;
	sc->matrix_scaling[0][2] = 0.0;
	sc->matrix_scaling[0][3] = 0.0;
	sc->matrix_scaling[1][0] = 0.0;
	sc->matrix_scaling[1][1] = 1.0;
	sc->matrix_scaling[1][2] = 0.0;
	sc->matrix_scaling[1][3] = 0.0;
	sc->matrix_scaling[2][0] = 0.0;
	sc->matrix_scaling[2][1] = 0.0;
	sc->matrix_scaling[2][2] = 1.0;
	sc->matrix_scaling[2][3] = 0.0;
	sc->matrix_scaling[3][0] = 0.0;
	sc->matrix_scaling[3][1] = 0.0;
	sc->matrix_scaling[3][2] = 0.0;
	sc->matrix_scaling[3][3] = 1.0;
}

void	set_scaling_matrix(t_scop *sc, float scale)
{
	sc->matrix_scaling[0][0] = scale;
	sc->matrix_scaling[1][1] = scale;
	sc->matrix_scaling[2][2] = scale;
}
