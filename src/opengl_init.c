/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opengl_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 18:23:44 by aleung-c          #+#    #+#             */
/*   Updated: 2016/11/25 18:23:45 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

int		init_glfw(t_scop *sc)
{
	if (!glfwInit())
	{
		ft_putendl("ERROR: could not start GLFW3");
		return (1);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	sc->window = glfwCreateWindow(640, 480, "aleung-c's scop", NULL, NULL);
	if (!sc->window)
	{
		ft_putendl("ERROR: could not open window with GLFW3");
		glfwTerminate();
		return (-1);
	}
	glfwMakeContextCurrent(sc->window);
	return (0);
}

int		init_opengl(t_scop *sc)
{
	const GLubyte	*renderer;
	const GLubyte	*version;

	if (sc)
	{
		renderer = glGetString(GL_RENDERER);
		version = glGetString(GL_VERSION);
		printf("\nRenderer: %s\n", renderer);
		printf("OpenGL version supported %s\n", version);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glEnable(GL_BLEND);
	}
	return (0);
}
