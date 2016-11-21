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
	// generating vbo buffers
	GLuint			vbo;
	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, (sc->nb_vertices * 4) * sizeof(float), sc->obj_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	// for the normals
	GLuint			nbo;
	glGenBuffers(1, &nbo);

	glBindBuffer(GL_ARRAY_BUFFER, nbo);
	glBufferData(GL_ARRAY_BUFFER, ((((sc->nb_faces_3 + (sc->nb_faces_4 * 2)) * 3) * 3) * 3) * sizeof(float), sc->faces_normals, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(1);
	
	// the color vbo.
	GLuint			cbo;
	glGenBuffers(1, &cbo);

	glBindBuffer(GL_ARRAY_BUFFER, cbo);
	glBufferData(GL_ARRAY_BUFFER, ((((sc->nb_faces_3 + (sc->nb_faces_4 * 2)) * 3) * 3) * 3) * sizeof(float), sc->vertex_color_values, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(2);


	// -------------------------------------------------------------------------- //
	//	EBO - Buffer object	of indices											  //
	// -------------------------------------------------------------------------- //
	// generating element array buff;
	GLuint ebo;
	glGenBuffers (1, &ebo);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (sc->nb_faces_3 * 3 + (sc->nb_faces_4 * 2) * 3) * sizeof(GL_UNSIGNED_INT), &sc->face_indices[0], GL_STATIC_DRAW);

}
