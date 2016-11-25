/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bounding_box.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 14:46:06 by aleung-c          #+#    #+#             */
/*   Updated: 2016/11/25 14:46:08 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

/*
**	Needed to recenter the object. this creates its "central point"
*/

void				set_bounding_box_limits(t_scop *sc)
{
	if (sc->inline_i == 0)
	{
		if (sc->obj_vertices[sc->itmp] > sc->bounding_box_max.x)
			sc->bounding_box_max.x = sc->obj_vertices[sc->itmp];
		if (sc->obj_vertices[sc->itmp] < sc->bounding_box_min.x)
			sc->bounding_box_min.x = sc->obj_vertices[sc->itmp];
	}
	else if (sc->inline_i == 1)
	{
		if (sc->obj_vertices[sc->itmp] > sc->bounding_box_max.y)
			sc->bounding_box_max.y = sc->obj_vertices[sc->itmp];
		if (sc->obj_vertices[sc->itmp] < sc->bounding_box_min.y)
			sc->bounding_box_min.y = sc->obj_vertices[sc->itmp];
	}
	else if (sc->inline_i == 2)
	{
		if (sc->obj_vertices[sc->itmp] > sc->bounding_box_max.z)
			sc->bounding_box_max.z = sc->obj_vertices[sc->itmp];
		if (sc->obj_vertices[sc->itmp] < sc->bounding_box_min.z)
			sc->bounding_box_min.z = sc->obj_vertices[sc->itmp];
	}
}

void				set_bounding_box_center(t_scop *sc)
{
	sc->bounding_box_center.x = (sc->bounding_box_min.x +
									sc->bounding_box_max.x) / 2;
	sc->bounding_box_center.y = (sc->bounding_box_min.y +
									sc->bounding_box_max.y) / 2;
	sc->bounding_box_center.z = (sc->bounding_box_min.z +
									sc->bounding_box_max.z) / 2;
}
