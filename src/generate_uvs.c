/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_uvs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 18:08:55 by aleung-c          #+#    #+#             */
/*   Updated: 2016/11/21 18:08:59 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

void	generate_uvs(t_scop *sc)
{
	unsigned int		*tmp;
	unsigned int		total_indices;
	unsigned int		i;

	i = 0;
	tmp = sc->face_indices;
	total_indices = (sc->total_faces * 3);
	while (i != total_indices)
	{
		add_one_uv(sc, 1.0, 0.0);
		add_one_uv(sc, 0.0, 0.0);
		add_one_uv(sc, 0.0, 1.0);
		i += 3;
		tmp += 3;
	}
}

void	add_one_uv(t_scop *sc, float u, float v)
{
	sc->faces_uv[sc->faces_uv_itmp] = u;
	sc->faces_uv_itmp++;
	sc->faces_uv[sc->faces_uv_itmp] = v;
	sc->faces_uv_itmp++;
}
