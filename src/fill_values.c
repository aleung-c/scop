/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_values.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 17:25:29 by aleung-c          #+#    #+#             */
/*   Updated: 2016/11/16 17:25:31 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

/*
**	Split indice of format x/x/x or x//x or x. Works with faces_3 and faces_4.
*/

void		fill_face_split_indice(t_scop *sc, t_token *inline_token)
{
	char			*splitted_indice;
	char			*t_val_cpy;
	char			*t_val_cpy_free;
	int				pos_in_indice;

	pos_in_indice = 0;
	t_val_cpy = strdup(inline_token->value);
	t_val_cpy_free = t_val_cpy;
	splitted_indice = strtok(t_val_cpy, "/");
	while (splitted_indice != NULL)
	{
		if (pos_in_indice == 0)
			fill_face_indice_vertex(sc, splitted_indice);
		else if (pos_in_indice == 1 && regex_match(inline_token->value,
			"^[-]?[0-9]+\\/\\/[-]?[0-9]*$"))
			add_face_normal_from_indice(sc, splitted_indice);
		else if (pos_in_indice == 2)
			add_face_normal_from_indice(sc, splitted_indice);
		splitted_indice = strtok(NULL, "/");
		pos_in_indice++;
	}
	free(t_val_cpy_free);
}

void		fill_face_indice_vertex(t_scop *sc, char *splitted_indice)
{
	sc->face_indices[sc->indices_itmp] = strtol(splitted_indice,
				NULL, 10) - 1;
	fill_face_vertices(sc, (sc->face_indices[sc->indices_itmp])
		* 4);
	sc->indices_itmp++;
}

void		add_face_normal_from_indice(t_scop *sc,
										char *splitted_indice)
{
	int				indice_val;

	indice_val = (strtol(splitted_indice, NULL, 10) * 3) - 1;
	add_one_face_normal_from_indice(sc, indice_val);
	add_one_face_normal_from_indice(sc, indice_val);
	add_one_face_normal_from_indice(sc, indice_val);
}

void		add_one_face_normal_from_indice(t_scop *sc, int indice_val)
{
	sc->faces_normals[sc->face_normals_itmp] =
		sc->obj_normals[indice_val];
	sc->face_normals_itmp++;
	sc->faces_normals[sc->face_normals_itmp] =
		sc->obj_normals[indice_val + 1];
	sc->face_normals_itmp++;
	sc->faces_normals[sc->face_normals_itmp] =
		sc->obj_normals[indice_val + 2];
	sc->face_normals_itmp++;
}
