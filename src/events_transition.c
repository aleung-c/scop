/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_transition.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 14:13:29 by aleung-c          #+#    #+#             */
/*   Updated: 2016/11/25 14:13:31 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

void	events_transition(t_scop *sc)
{
	if (sc->in_transition == 1)
	{
		transition_one_face(sc);
		if (sc->total_faces > 1000)
			transition_n_faces(sc, 3);
		if (sc->total_faces > 3000)
			transition_n_faces(sc, 6);
		if (sc->total_faces > 5000)
			transition_n_faces(sc, 6);
		if (sc->total_faces > 7000)
			transition_n_faces(sc, 6);
		glBindBuffer(GL_ARRAY_BUFFER, sc->tbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (sc->total_faces * 3),
					sc->transition_points, GL_STATIC_DRAW);
		sc->transition_counter++;
	}
	if (sc->buffer_i >= (sc->total_faces * 3))
	{
		sc->in_transition = 0;
		sc->on_standby = 1;
	}
}

void	transition_n_faces(t_scop *sc, int n)
{
	int i;

	i = 0;
	while (i != n)
	{
		transition_one_face(sc);
		i++;
	}
}

void	transition_one_face(t_scop *sc)
{
	if (sc->buffer_i < (sc->total_faces * 3))
	{
		sc->transition_points[sc->buffer_i] = sc->transition_value;
		sc->buffer_i++;
	}
}
