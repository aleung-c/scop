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

void opengl_set_buffers(t_scop *sc)
{
	// -------------------------------------------------------------------------- //
	//	VAO - Vertex Array object												  //
	// -------------------------------------------------------------------------- //
	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// -------------------------------------------------------------------------- //
	//	VBOs - Vertex buffer object												  //
	// -------------------------------------------------------------------------- //
	
	//generating vbo buffers
	sc->vbo = 0;
	glGenBuffers(1, &(sc->vbo));

	glBindBuffer(GL_ARRAY_BUFFER, sc->vbo);
	glBufferData(GL_ARRAY_BUFFER, (sc->nb_vertices * 4) * sizeof(float), sc->obj_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(3);

	// generating buffer of face vertices.
	sc->fvbo = 0;
	glGenBuffers(1, &(sc->fvbo));

	glBindBuffer(GL_ARRAY_BUFFER, sc->fvbo);
	glBufferData(GL_ARRAY_BUFFER, ((sc->total_faces * 3) * 4) * sizeof(float), sc->faces_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	// for the normals
	sc->nbo = 0;
	glGenBuffers(1, &(sc->nbo));

	glBindBuffer(GL_ARRAY_BUFFER, sc->nbo);
	glBufferData(GL_ARRAY_BUFFER, (((sc->total_faces * 3) * 3) * 3) * sizeof(float), sc->faces_normals, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(1);
	
	// the color bo.
	sc->cbo = 0;
	glGenBuffers(1, &(sc->cbo));

	glBindBuffer(GL_ARRAY_BUFFER, sc->cbo);
	glBufferData(GL_ARRAY_BUFFER, (((sc->total_faces * 3) * 3) * 3) * sizeof(float), sc->faces_uv, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(2);

	// the uv buffer.
	sc->ubo = 0;
	glGenBuffers(1, &(sc->ubo));

	glBindBuffer(GL_ARRAY_BUFFER, sc->ubo);
	glBufferData(GL_ARRAY_BUFFER, (sc->total_faces * 3) * 2 * sizeof(float), sc->vertex_color_values, GL_STATIC_DRAW);
	glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(4);



	// -------------------------------------------------------------------------- //
	//	EBO - Buffer object	of indices											  //
	// -------------------------------------------------------------------------- //
	// generating element array buff;
	sc->ebo = 0;
	glGenBuffers (1, &(sc->ebo));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sc->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (sc->nb_faces_3 * 3 + (sc->nb_faces_4 * 2) * 3) * sizeof(GL_UNSIGNED_INT), &sc->face_indices[0], GL_STATIC_DRAW);

}
