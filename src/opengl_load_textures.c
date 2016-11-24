/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opengl_load_textures.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 17:53:42 by aleung-c          #+#    #+#             */
/*   Updated: 2016/11/23 17:53:43 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

void opengl_load_textures(t_scop *sc)
{
	// -------------------------------------------------------------------------- //
	//	Default Texture loading in the engine.									  //
	// -------------------------------------------------------------------------- //
	// Create one OpenGL texture
	GLuint			textureID;
	GLuint			textureID2;
	GLuint			uniform_mat;

	glGenTextures(1, &textureID);
	glActiveTexture(GL_TEXTURE0);
	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, sc->default_texture.width, sc->default_texture.height, 0,
		GL_BGR, GL_UNSIGNED_BYTE, sc->default_texture.data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	// bind texture to fragment shader uniform sampler2D
	uniform_mat = glGetUniformLocation(sc->main_shader_programme, "texture_0");
	glUniform1i(uniform_mat, 0);

	
	//glBindTexture(GL_TEXTURE_2D, textureID);



	glGenTextures(1, &textureID2);
	glActiveTexture(GL_TEXTURE1);
	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID2);

	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, sc->second_texture.width, sc->second_texture.height, 0,
		GL_BGR, GL_UNSIGNED_BYTE, sc->second_texture.data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	// bind texture to fragment shader uniform sampler2D
	uniform_mat = glGetUniformLocation(sc->main_shader_programme, "texture_1");
	glUniform1i(uniform_mat, 1);
	//glBindTexture(GL_TEXTURE_2D, textureID2);
}
