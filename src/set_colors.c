/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 13:26:34 by aleung-c          #+#    #+#             */
/*   Updated: 2016/11/21 13:26:36 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

void		set_model_colors(t_scop *sc)
{
	unsigned int		total_indices;
	int 				i;
	float				cur_color;

	i = 0;
	total_indices = (sc->total_faces * 3);
	cur_color = 0.3;
	while (i < total_indices)
	{
		//printf("current indice = %d\n", *tmp);
		cur_color = set_gray_level(cur_color + 0.3);
		sc->vertex_color_values[sc->vcolor_itmp] = cur_color;
		sc->vcolor_itmp++;
		sc->vertex_color_values[sc->vcolor_itmp] = cur_color;
		sc->vcolor_itmp++;
		sc->vertex_color_values[sc->vcolor_itmp] = cur_color;
		sc->vcolor_itmp++;

		sc->vertex_color_values[sc->vcolor_itmp] = cur_color;
		sc->vcolor_itmp++;
		sc->vertex_color_values[sc->vcolor_itmp] = cur_color;
		sc->vcolor_itmp++;
		sc->vertex_color_values[sc->vcolor_itmp] = cur_color;
		sc->vcolor_itmp++;

		sc->vertex_color_values[sc->vcolor_itmp] = cur_color;
		sc->vcolor_itmp++;
		sc->vertex_color_values[sc->vcolor_itmp] = cur_color;
		sc->vcolor_itmp++;
		sc->vertex_color_values[sc->vcolor_itmp] = cur_color;
		sc->vcolor_itmp++;
		//printf("added color %f\n", cur_color);
		
		i += 3;
	}
}

float		set_gray_level(float color)
{
	float		ret;

	if (color > 1.0)
		ret = 0.3;
	else
		ret = color;
	return (ret);
}