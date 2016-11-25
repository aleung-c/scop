/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_variables.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 14:12:12 by aleung-c          #+#    #+#             */
/*   Updated: 2016/11/23 14:12:14 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

void		allocate_variables(t_scop *sc)
{
	sc->total_faces = (sc->nb_faces_3 + (sc->nb_faces_4 * 2)
		+ (sc->nb_indices_more));
	if (!(sc->obj_vertices = (float *)malloc(sizeof(float) * sc->nb_vertices
		* 4)))
		error_allocation("vertices allocation failed.");
	if (!(sc->face_indices = (unsigned int *)malloc(sizeof(GL_UNSIGNED_INT)
		* sc->total_faces * 3)))
		error_allocation("faces - indices allocation failed.");
	if (!(sc->obj_normals = (float *)malloc(sizeof(float)
		* (sc->nb_normals_vertices) * 3)))
		error_allocation("normal values allocation failed.");
	if (!(sc->faces_normals = (float *)malloc(sizeof(float)
		* ((sc->total_faces * 3) * 3) * 3)))
		error_allocation("faces normals allocation failed.");
	allocate_variables_2(sc);
}

void		allocate_variables_2(t_scop *sc)
{
	if (!(sc->faces_vertices = (float *)malloc(sizeof(float)
		* (sc->total_faces * 3) * 4)))
		error_allocation("faces vertices allocation failed.");
	if (!(sc->obj_tex_coords = (float *)malloc(sizeof(float)
		* sc->nb_texture_vertices * 2)))
		error_allocation("vt values allocation failed.");
	if (!(sc->faces_uv = (float *)malloc(sizeof(float)
		* (sc->total_faces * 3) * 2)))
		error_allocation("faces uv allocation failed.");
	if (!(sc->vertex_color_values = (float *)malloc(sizeof(float)
		* (sc->total_faces * 3) * 3)))
		error_allocation("color buffer allocation failed.");
	if (!(sc->transition_points = (int *)malloc(sizeof(int)
		* (sc->total_faces * 3))))
		error_allocation("transition_flags allocation failed.");
	ft_putendl("- obj file variables allocated.");
}

void		error_allocation(char *msg_string)
{
	ft_putendl(msg_string);
	exit(-1);
}

void		deallocate_variables(t_scop *sc)
{
	t_token		*tmp;

	free(sc->obj_vertices);
	free(sc->face_indices);
	free(sc->obj_normals);
	free(sc->faces_normals);
	free(sc->faces_vertices);
	free(sc->obj_tex_coords);
	free(sc->faces_uv);
	free(sc->vertex_color_values);
	free(sc->transition_points);
	free(sc->default_texture.data);
	free(sc->second_texture.data);
	while (sc->obj_token_list)
	{
		free(sc->obj_token_list->value_pointer);
		tmp = sc->obj_token_list;
		free(tmp);
		sc->obj_token_list = sc->obj_token_list->next;
	}
	exit(0);
}
