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
	sc->total_faces = (sc->nb_faces_3 + (sc->nb_faces_4 * 2));
	if (!(sc->obj_vertices = (float *)malloc(sizeof(float) * sc->nb_vertices * 4))) // v
	{
		ft_putendl("vertices allocation failed.");
		exit (-1);
	}
	if (!(sc->face_indices = (unsigned int *)malloc(sc->total_faces * 3 * sizeof(GL_UNSIGNED_INT)))) // indices
	{
		ft_putendl("faces - indices allocation failed.");
		exit (-1);
	}
	if (!(sc->obj_normals = (float *)malloc(sizeof(float) * (sc->nb_normals_vertices) * 3))) // vn
	{
		ft_putendl("normal values allocation failed.");
		exit (-1);
	}
	if (!(sc->faces_normals = (float *)malloc(sizeof(float) * ((sc->total_faces * 3) * 3) * 3))) // for each face
	{
		ft_putendl("faces normals allocation failed.");
		exit (-1);
	}
	if (!(sc->faces_vertices = (float *)malloc(sizeof(float) * (sc->total_faces * 3) * 4))) // for each face
	{
		ft_putendl("faces vertices allocation failed.");
		exit (-1);
	}
	if (!(sc->obj_tex_coords = (float *)malloc(sizeof(float) * sc->nb_texture_vertices * 2))) // vt
	{
		ft_putendl("vt values allocation failed.");
		exit (-1);
	}
	if (!(sc->faces_uv = (float *)malloc(sizeof(float) * (sc->total_faces * 3) * 2))) // for each face
	{
		ft_putendl("faces uv allocation failed.");
		exit (-1);
	}
	if (!(sc->vertex_color_values = (float *)malloc(sizeof(float) * (sc->total_faces * 3) * 3))) // for each face
	{
		ft_putendl("color buffer allocation failed.");
		exit (-1);
	}
	if (!(sc->transition_points = (int *)malloc((sc->total_faces * 3) * sizeof(int)))) // for transition.
	{
		ft_putendl("transition_flags allocation failed.");
		exit (-1);
	}
	ft_putendl("- obj file variables allocated.");
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
	exit (0);
}
