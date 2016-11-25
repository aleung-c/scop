/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opengl_set_buffers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 14:51:30 by aleung-c          #+#    #+#             */
/*   Updated: 2016/11/21 14:51:32 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

void	opengl_set_buffers(t_scop *sc)
{
	GLuint vao;

	vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	opengl_set_gen_buffers(sc);
	opengl_set_vertice_buffers(sc);
	opengl_set_color_buffers(sc);
}

void	opengl_set_gen_buffers(t_scop *sc)
{
	sc->fvbo = 0;
	sc->cbo = 0;
	sc->nbo = 0;
	sc->vbo = 0;
	sc->ubo = 0;
	sc->tbo = 0;
	sc->ebo = 0;
	glGenBuffers(1, &(sc->fvbo));
	glGenBuffers(1, &(sc->nbo));
	glGenBuffers(1, &(sc->cbo));
	glGenBuffers(1, &(sc->vbo));
	glGenBuffers(1, &(sc->ubo));
	glGenBuffers(1, &(sc->tbo));
	glGenBuffers(1, &(sc->ebo));
}

void	opengl_set_vertice_buffers(t_scop *sc)
{
	glBindBuffer(GL_ARRAY_BUFFER, sc->fvbo);
	glBufferData(GL_ARRAY_BUFFER, ((sc->total_faces * 3) * 4) *
		sizeof(float), sc->faces_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, sc->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (sc->nb_vertices * 4),
		sc->obj_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sc->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (sc->total_faces * 3) * 3 *
		sizeof(GL_UNSIGNED_INT), &sc->face_indices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, sc->nbo);
	glBufferData(GL_ARRAY_BUFFER, (((sc->total_faces * 3) * 3) * 3) *
		sizeof(float), sc->faces_normals, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(1);
}

void	opengl_set_color_buffers(t_scop *sc)
{
	glBindBuffer(GL_ARRAY_BUFFER, sc->cbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * ((sc->total_faces * 3) * 3),
		sc->vertex_color_values, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, sc->ubo);
	glBufferData(GL_ARRAY_BUFFER, ((sc->total_faces * 3) * 2) * sizeof(float),
		sc->faces_uv, GL_STATIC_DRAW);
	glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(4);
	glBindBuffer(GL_ARRAY_BUFFER, sc->tbo);
	glBufferData(GL_ARRAY_BUFFER, (sc->total_faces * 3) * sizeof(GL_INT),
		sc->transition_points, GL_STATIC_DRAW);
	glVertexAttribPointer(5, 1, GL_INT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(5);
}
