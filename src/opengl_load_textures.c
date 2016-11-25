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

void	opengl_load_textures(t_scop *sc)
{
	opengl_load_default_tex(sc);
	opengl_load_second_tex(sc);
}

void	opengl_load_default_tex(t_scop *sc)
{
	GLuint			texture_id0;
	GLuint			uniform_mat;

	glGenTextures(1, &texture_id0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_id0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, sc->default_texture.width,
		sc->default_texture.height, 0, GL_BGR, GL_UNSIGNED_BYTE,
		sc->default_texture.data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	uniform_mat = glGetUniformLocation(sc->main_shader_programme,
										"texture_0");
	glUniform1i(uniform_mat, 0);
}

void	opengl_load_second_tex(t_scop *sc)
{
	GLuint			texture_id1;
	GLuint			uniform_mat;

	glGenTextures(1, &texture_id1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture_id1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, sc->second_texture.width,
		sc->second_texture.height, 0, GL_BGR, GL_UNSIGNED_BYTE,
		sc->second_texture.data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	uniform_mat = glGetUniformLocation(sc->main_shader_programme,
										"texture_1");
	glUniform1i(uniform_mat, 1);
}
