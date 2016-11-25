/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_faces.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 14:31:00 by aleung-c          #+#    #+#             */
/*   Updated: 2016/11/25 14:31:01 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

void		fill_face3(t_scop *sc, t_token *token)
{
	sc->inline_token = token->next;
	while (sc->inline_token && sc->inline_token->line_number
		== token->line_number)
	{
		fill_face_split_indice(sc, sc->inline_token);
		sc->inline_token = sc->inline_token->next;
	}
}

/*
**	Odd bug with pointer copy forces this syntax.
*/

void		fill_face4(t_scop *sc, t_token *token)
{
	sc->inline_token = token->next;
	fill_face_split_indice(sc, sc->inline_token);
	sc->inline_token = token->next->next;
	fill_face_split_indice(sc, sc->inline_token);
	sc->inline_token = token->next->next->next;
	fill_face_split_indice(sc, sc->inline_token);
	sc->inline_token = token->next->next->next->next;
	fill_face_split_indice(sc, sc->inline_token);
	sc->inline_token = token->next->next->next;
	fill_face_split_indice(sc, sc->inline_token);
	sc->inline_token = token->next;
	fill_face_split_indice(sc, sc->inline_token);
}

void		fill_face_more(t_scop *sc, t_token *token)
{
	t_token		*tmp;
	t_token		*tmp2;
	t_token		*tmp3;

	tmp = token->next;
	while (tmp && tmp->line_number == token->line_number)
	{
		tmp2 = tmp->next;
		tmp3 = tmp2->next;
		if (tmp2 && tmp3 && tmp2->line_number == token->line_number
			&& tmp3->line_number == token->line_number)
		{
			fill_face_split_indice(sc, tmp);
			fill_face_split_indice(sc, tmp2);
			fill_face_split_indice(sc, tmp3);
		}
		tmp = tmp->next;
	}
}

void		fill_face_vertices(t_scop *sc, unsigned int indice)
{
	if (indice < (sc->nb_vertices * 4))
	{
		sc->faces_vertices[sc->faces_vertices_itmp] =
			sc->obj_vertices[indice];
		sc->faces_vertices_itmp++;
		sc->faces_vertices[sc->faces_vertices_itmp] =
			sc->obj_vertices[indice + 1];
		sc->faces_vertices_itmp++;
		sc->faces_vertices[sc->faces_vertices_itmp] =
			sc->obj_vertices[indice + 2];
		sc->faces_vertices_itmp++;
		sc->faces_vertices[sc->faces_vertices_itmp] = 1.0;
		sc->faces_vertices_itmp++;
	}
}
