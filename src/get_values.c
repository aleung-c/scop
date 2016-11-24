/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_values.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 15:48:35 by aleung-c          #+#    #+#             */
/*   Updated: 2016/11/07 15:48:36 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

/*
**	Put Values in variables for opengl processing.
*/
void get_values(t_scop *sc)
{
	t_token		*token;

	token = sc->obj_token_list;
	while (token)
	{
		if (!strcmp(token->value, "v"))
			fill_vertex(sc, token);
		else if (!strcmp(token->value, "f"))
			fill_face(sc, token);
		else if (!strcmp(token->value, "vt"))
			fill_tex_coord(sc, token);
		else if (!strcmp(token->value, "vn"))
			fill_normals(sc, token);
		token = token->next;
	}
	set_bounding_box_center(sc);
}

void						fill_vertex(t_scop *sc, t_token *token)
{
	sc->inline_token = token->next;
	sc->inline_i = 0;
	while (sc->inline_token && sc->inline_token->line_number == token->line_number)
	{
		sc->obj_vertices[sc->itmp] = strtof(&(*sc->inline_token->value), &sc->inline_token->value);
		set_bounding_box_limits(sc);
		
		sc->itmp++;
		sc->inline_token = sc->inline_token->next;
		sc->inline_i++;
	}
	if (sc->inline_i == 3)
	{
		// add the fourth 1.0;
		sc->obj_vertices[sc->itmp] = 1.0;
		sc->itmp++;
	}
}

void						set_bounding_box_limits(t_scop *sc)
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

void						set_bounding_box_center(t_scop *sc)
{
	sc->bounding_box_center.x = (sc->bounding_box_min.x + sc->bounding_box_max.x) / 2;
	sc->bounding_box_center.y = (sc->bounding_box_min.y + sc->bounding_box_max.y) / 2;
	sc->bounding_box_center.z = (sc->bounding_box_min.z + sc->bounding_box_max.z) / 2;
}

void						fill_tex_coord(t_scop *sc, t_token *token)
{
	sc->inline_token = token->next;
	while (sc->inline_token && sc->inline_token->line_number == token->line_number)
	{
		sc->obj_tex_coords[sc->tex_coord_itmp] = strtof(&(*sc->inline_token->value), &sc->inline_token->value);
		sc->tex_coord_itmp++;
		sc->inline_token = sc->inline_token->next;
	}
}

void						fill_normals(t_scop *sc, t_token *token)
{
	sc->inline_token = token->next;
	while (sc->inline_token && sc->inline_token->line_number == token->line_number)
	{
		sc->obj_normals[sc->normals_itmp] = strtof(&(*sc->inline_token->value), &sc->inline_token->value);
		sc->normals_itmp++;
		sc->inline_token = sc->inline_token->next;
	}
}

void						fill_face(t_scop *sc, t_token *token)
{
	sc->inline_i = 0;
	sc->inline_token = token->next;
	while (sc->inline_token && sc->inline_token->line_number == token->line_number)
	{
		sc->inline_i++;
		sc->inline_token = sc->inline_token->next;
	}
	// Filling a face_3
	if (sc->inline_i == 3)
	{
		fill_face3(sc, token);
	}
	// Filling a face_4 - converting it into two triangles.
	else if (sc->inline_i == 4)
	{
		fill_face4(sc, token);
	}
	/*else if (sc->inline_i > 4)
	{
		fill_face_more(sc, token);
	}*/
}
