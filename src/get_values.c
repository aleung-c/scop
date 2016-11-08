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
	t_token		*inline_token;
	int			inline_i;

	inline_i = 0;
	token = sc->obj_token_list;
	while (token)
	{
		if (token->col_number == 0)
		{
			if ((strcmp(token->value, "v") == 0))
				sc->nb_vertices += 1;
			if ((strcmp(token->value, "vt") == 0))
				sc->nb_texture_vertices += 1;
			if ((strcmp(token->value, "vn") == 0))
				sc->nb_normals_vertices += 1;
			if ((strcmp(token->value, "vp") == 0))
				sc->nb_parameter_space_vertices += 1;

			// face handling
			if (strcmp(token->value, "f"))
			{
				sc->nb_faces_3 += 1;
				inline_i = 0;
				inline_token = token->next;
				while (inline_token && inline_token->line_number == token->line_number)
				{
					inline_i++;
					inline_token = inline_token->next;
				}
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
	/*ft_putstr("total nb of line = ");
	ft_putnbr(line_number);
	ft_putchar('\n');*/

	ft_putstr("Nb of vertices = ");
	ft_putnbr(sc->nb_vertices);
	ft_putchar('\n');
	ft_putstr("Nb of tex vertices = ");
	ft_putnbr(sc->nb_texture_vertices);
	ft_putchar('\n');
	ft_putstr("Nb of normals vertices = ");
	ft_putnbr(sc->nb_normals_vertices);
	ft_putchar('\n');
	ft_putstr("Nb of parameter space vertices = ");
	ft_putnbr(sc->nb_parameter_space_vertices);
	ft_putchar('\n');
	ft_putstr("Nb of faces 3 = ");
	ft_putnbr(sc->nb_faces_3);
	ft_putchar('\n');
	ft_putstr("Nb of faces 4 = ");
	ft_putnbr(sc->nb_faces_4);
	ft_putchar('\n');
	ft_putstr("Nb of obj = ");
	ft_putnbr(sc->nb_obj);
	ft_putchar('\n');
	ft_putstr("Nb of groups = ");
	ft_putnbr(sc->nb_groups);
	ft_putchar('\n');
	ft_putstr("Nb of materials = ");
	ft_putnbr(sc->nb_materials);
	ft_putchar('\n');
	ft_putchar('\n');
}

/*
**	Put Values in variables for opengl processing.
*/
void get_values(t_scop *sc)
{
	t_token		*token;
	t_token		*inline_token;
	int			inline_i;

	token = sc->obj_token_list;
	while (token)
	{
		// --------------------------------------------	//
		// filling a vertex								//
		// --------------------------------------------	//
		if (strcmp(token->value, "v") == 0)
		{
			inline_token = token->next;
			inline_i = 0;
			while (inline_token->line_number == token->line_number)
			{
				sc->obj_vertices[sc->itmp] = strtof(&(*inline_token->value), &inline_token->value);
				inline_token = inline_token->next;
				sc->itmp++;
				inline_i++;
			}
			if (inline_i == 3)
			{
				// add the fourth 1.0;
				sc->obj_vertices[sc->itmp] = 1.0;
				sc->itmp++;
			}
		}
		// --------------------------------------------	//
		// filling a face								//
		// --------------------------------------------	//
		// TODO: take the x/x/x into account.
		if (strcmp(token->value, "f") == 0)
		{
			inline_i = 0;
			inline_token = token->next;
			// count nb of indices
			while (inline_token && inline_token->line_number == token->line_number)
			{
				inline_i++;
				inline_token = inline_token->next;
			}

			// Filling a face_3
			if (inline_i == 3)
			{
				inline_token = token->next;
				inline_i = 0;
				while (inline_token && inline_token->line_number == token->line_number)
				{
					// get the indice 1
					sc->face_3_indices[sc->indices_itmp] = strtol(inline_token->value, NULL, 0);
					sc->indices_itmp += 1;


					// one indice token => 3 float from the same vertex.
					sc->obj_faces_3[sc->faces_itmp] = sc->obj_vertices[(strtol(&(*(inline_token->value)), NULL, 10)) * 3];
					sc->faces_itmp += 1;
					sc->obj_faces_3[sc->faces_itmp] = sc->obj_vertices[((strtol(&(*(inline_token->value)), NULL, 10)) * 3) + 1];
					sc->faces_itmp += 1;
					sc->obj_faces_3[sc->faces_itmp] = sc->obj_vertices[((strtol(&(*(inline_token->value)), NULL, 10)) * 3) + 2];
					sc->faces_itmp += 1;

					// moving to next;
					inline_token = inline_token->next;
					inline_i++;
				}
			}
			
		}
		token = token->next;
	}
}
