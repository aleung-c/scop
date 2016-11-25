/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opengl_load_shaders.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 14:54:06 by aleung-c          #+#    #+#             */
/*   Updated: 2016/11/21 14:54:09 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

void	opengl_load_shaders(t_scop *sc)
{
	GLuint	vs;
	GLuint	fs;

	sc->vertex_shader_1 = get_file_content("./shaders/vshader_1.vs");
	sc->fragment_shader_1 = get_file_content("./shaders/fshader_1.fs");
	vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, (const char *const *)&sc->vertex_shader_1, NULL);
	glCompileShader(vs);
	fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, (const char *const *)&sc->fragment_shader_1, NULL);
	glCompileShader(fs);
	opengl_create_shader_programme(sc, vs, fs);
}

void	opengl_create_shader_programme(t_scop *sc, GLuint vs, GLuint fs)
{
	GLuint	shader_programme;

	shader_programme = glCreateProgram();
	glAttachShader(shader_programme, fs);
	glAttachShader(shader_programme, vs);
	glLinkProgram(shader_programme);
	glUseProgram(shader_programme);
	sc->main_shader_programme = shader_programme;
}
