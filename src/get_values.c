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

void count_values(t_scop *sc)
{
	t_token		*token;
	int			inline_i;

	inline_i = 0;
	token = sc->obj_token_list;
	while (token)
	{
		if (token->col_number == 0)
		{
			if (!strcmp(token->value, "v"))
				sc->nb_vertices += 1;
			else if (!strcmp(token->value, "vt"))
				sc->nb_texture_vertices += 1;
			else if (!strcmp(token->value, "vn"))
				sc->nb_normals_vertices += 1;
			else if (!strcmp(token->value, "vp"))
				sc->nb_parameter_space_vertices += 1;
			// face handling
			else if (strcmp(token->value, "f") == 0)
			{
				//sc->nb_faces_3 += 1;
				inline_i = 0;
				sc->inline_token = token->next;
				while (sc->inline_token && sc->inline_token->line_number == token->line_number)
				{
					inline_i++;
					sc->inline_token = sc->inline_token->next;
				}
				//printf("\n");
				if (inline_i == 3)
					sc->nb_faces_3 += 1;
				else if (inline_i == 4)
					sc->nb_faces_4 += 1;
				else
					sc->nb_faces_more += 1;
			}
		}
		token = token->next;
	}

	ft_putstr(KGRN "Object file datas:" KRESET);
	ft_putchar('\n');

	printf("Nb of vertices = %lu\n", sc->nb_vertices);
	printf("Nb of tex vertices = %lu\n", sc->nb_texture_vertices);
	printf("Nb of normals vertices = %lu\n", sc->nb_texture_vertices);
	printf("Nb of normals vertices = %lu\n", sc->nb_normals_vertices);
	printf("Nb of parameter space vertices = %lu\n", sc->nb_parameter_space_vertices);
	printf("Nb of faces 3 = %lu\n", sc->nb_faces_3);
	printf("Nb of faces 4 = %lu\n", sc->nb_faces_4);
	printf("Nb of faces more = %lu\n", sc->nb_faces_more);
	printf("Nb of obj = %lu\n", sc->nb_obj);
	printf("Nb of groups = %lu\n", sc->nb_groups);
	printf("Nb of materials = %lu\n", sc->nb_materials);
	ft_putchar('\n');
}

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
		{
			fill_vertex(sc, token);
		}
		else if (!strcmp(token->value, "f"))
		{
			fill_face(sc, token);
		}
		else if (!strcmp(token->value, "vt"))
		{
			fill_tex_coord(sc, token);
		}
		else if (!strcmp(token->value, "vn"))
		{
			fill_normals(sc, token);
		}
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

void					set_bounding_box_limits(t_scop *sc)
{
	if (sc->inline_i == 0)
	{
		// x pos;
		if (sc->obj_vertices[sc->itmp] > sc->bounding_box_max.x)
			sc->bounding_box_max.x = sc->obj_vertices[sc->itmp];
		if (sc->obj_vertices[sc->itmp] < sc->bounding_box_min.x)
			sc->bounding_box_min.x = sc->obj_vertices[sc->itmp];
	}
	else if (sc->inline_i == 1)
	{
		// y pos;
		if (sc->obj_vertices[sc->itmp] > sc->bounding_box_max.y)
			sc->bounding_box_max.y = sc->obj_vertices[sc->itmp];
		if (sc->obj_vertices[sc->itmp] < sc->bounding_box_min.y)
			sc->bounding_box_min.y = sc->obj_vertices[sc->itmp];
	}
	else if (sc->inline_i == 2)
	{
		// z pos;
		if (sc->obj_vertices[sc->itmp] > sc->bounding_box_max.z)
			sc->bounding_box_max.z = sc->obj_vertices[sc->itmp];
		if (sc->obj_vertices[sc->itmp] < sc->bounding_box_min.z)
			sc->bounding_box_min.z = sc->obj_vertices[sc->itmp];
	}
}

void					set_bounding_box_center(t_scop *sc)
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
	// TODO: take the x/x/x into account.
	sc->inline_i = 0;
	sc->inline_token = token->next;
	// count nb of indices
	while (sc->inline_token && sc->inline_token->line_number == token->line_number)
	{
		//printf("%s ", sc->inline_token->value);
		sc->inline_i++;
		sc->inline_token = sc->inline_token->next;
	}
	//printf("\n");

	// Filling a face_3
	if (sc->inline_i == 3)
	{
		fill_face3(sc, token);
	}
	// Filling a face_4 - converting it into a triangle.
	if (sc->inline_i == 4)
	{
		fill_face4(sc, token);	
	}
}
