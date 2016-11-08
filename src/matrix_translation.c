/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_translation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 17:47:16 by aleung-c          #+#    #+#             */
/*   Updated: 2016/11/08 17:47:19 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

void init_translation_matrix(t_scop *sc)
{
	// ! column 1
	sc->matrix_translation[0][0] = 1.0;
	sc->matrix_translation[0][1] = 0.0;
	sc->matrix_translation[0][2] = 0.0;
	sc->matrix_translation[0][3] = 0.0;

	// ! column 2
	sc->matrix_translation[1][0] = 0.0;
	sc->matrix_translation[1][1] = 1.0;
	sc->matrix_translation[1][2] = 0.0;
	sc->matrix_translation[1][3] = 0.0;

	// ! column 3
	sc->matrix_translation[2][0] = 0.0;
	sc->matrix_translation[2][1] = 0.0;
	sc->matrix_translation[2][2] = 1.0;
	sc->matrix_translation[2][3] = 0.0;

	// ! column 4
	sc->matrix_translation[3][0] = 0.0; // will be x
	sc->matrix_translation[3][1] = 0.0; // will be y
	sc->matrix_translation[3][2] = 0.0; // will be z
	sc->matrix_translation[3][3] = 1.0;
}

void set_translation_matrix(t_scop *sc, float x, float y, float z)
{
	// ! column 4
	sc->matrix_translation[3][0] = x;
	sc->matrix_translation[3][1] = y;
	sc->matrix_translation[3][2] = z;
}