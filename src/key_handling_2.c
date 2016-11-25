/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handling_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 17:26:20 by aleung-c          #+#    #+#             */
/*   Updated: 2016/11/25 17:26:22 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

void	apply_step_back(t_scop *sc, int key, int action)
{
	if (key == GLFW_KEY_B && action == GLFW_PRESS)
	{
		if (sc->has_stepped_back == 0)
		{
			sc->has_stepped_back = 1;
			set_translation_matrix(sc, -sc->camera_pos.x, -sc->camera_pos.y,
			-sc->camera_pos.z - 20.0);
		}
		else
		{
			sc->has_stepped_back = 0;
			set_translation_matrix(sc, -sc->camera_pos.x, -sc->camera_pos.y,
			-sc->camera_pos.z);
		}
		modify_uniform_matrice(sc, &sc->matrix_translation[0][0],
			"view_translation_matrix");
	}
}
