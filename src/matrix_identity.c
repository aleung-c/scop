/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_identity.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 18:36:57 by aleung-c          #+#    #+#             */
/*   Updated: 2016/11/08 18:37:00 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

void	init_identity_matrix(t_scop *sc)
{
	sc->matrix_identity[0][0] = 1.0;
	sc->matrix_identity[0][1] = 0.0;
	sc->matrix_identity[0][2] = 0.0;
	sc->matrix_identity[0][3] = 0.0;
	sc->matrix_identity[1][0] = 0.0;
	sc->matrix_identity[1][1] = 1.0;
	sc->matrix_identity[1][2] = 0.0;
	sc->matrix_identity[1][3] = 0.0;
	sc->matrix_identity[2][0] = 0.0;
	sc->matrix_identity[2][1] = 0.0;
	sc->matrix_identity[2][2] = 1.0;
	sc->matrix_identity[2][3] = 0.0;
	sc->matrix_identity[3][0] = 0.0;
	sc->matrix_identity[3][1] = 0.0;
	sc->matrix_identity[3][2] = 0.0;
	sc->matrix_identity[3][3] = 1.0;
}
