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
