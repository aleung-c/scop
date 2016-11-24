/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_transition_points.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 14:09:59 by aleung-c          #+#    #+#             */
/*   Updated: 2016/11/23 14:10:01 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

void generate_transition_points(t_scop *sc)
{
	unsigned int		*tmp;
	unsigned int		total_indices;
	unsigned int 		i;

	i = 0;
	tmp = sc->face_indices;
	total_indices = (sc->total_faces * 3);
	while (i != total_indices)
	{
		sc->transition_points[sc->tpoints_i] = 0;
		sc->tpoints_i++;
		i++;
	}
}