/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 15:20:50 by aleung-c          #+#    #+#             */
/*   Updated: 2016/11/21 15:20:53 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

void		event_init(t_scop *sc)
{
	sc->i_axis = 0.0;
	sc->on_standby = 1;
	sc->is_rotating = 1;
	sc->is_rotating_x = 0;
	sc->is_rotating_y = 1;
	sc->is_rotating_z = 0;
	sc->using_array = 1;
	sc->transition_counter = 0;
	sc->transition_value = 0;
	sc->has_stepped_back = 0;
	sc->buffer_i = 0;
	sc->cur_texture_id = 0;
}

void		event_process(t_scop *sc)
{
	events_rotations(sc);
	events_transition(sc);
}
