/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_uv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 14:34:53 by aleung-c          #+#    #+#             */
/*   Updated: 2016/11/25 14:34:57 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

/*
**	Unused, uv are generated instead. but lets keep it, who knows.
*/

void		add_face_uv_from_indice(t_scop *sc, char *splitted_indice)
{
	int				indice_val;

	indice_val = (strtol(splitted_indice, NULL, 10) * 2) - 1;
	sc->faces_uv[sc->faces_uv_itmp] = sc->obj_tex_coords[indice_val];
	sc->faces_uv_itmp++;
	sc->faces_uv[sc->faces_uv_itmp] = sc->obj_tex_coords[indice_val + 1];
	sc->faces_uv_itmp++;
	sc->faces_uv[sc->faces_uv_itmp] = sc->obj_tex_coords[indice_val];
	sc->faces_uv_itmp++;
	sc->faces_uv[sc->faces_uv_itmp] = sc->obj_tex_coords[indice_val + 1];
	sc->faces_uv_itmp++;
	sc->faces_uv[sc->faces_uv_itmp] = sc->obj_tex_coords[indice_val];
	sc->faces_uv_itmp++;
	sc->faces_uv[sc->faces_uv_itmp] = sc->obj_tex_coords[indice_val + 1];
	sc->faces_uv_itmp++;
}
