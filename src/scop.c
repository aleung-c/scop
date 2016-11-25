/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 14:31:06 by aleung-c          #+#    #+#             */
/*   Updated: 2016/09/26 14:31:10 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

/*
**	Main scop fonction;
*/

void	scop(t_scop *sc)
{
	if (init_glfw(sc) == -1 || init_opengl(sc) == -1)
	{
		ft_putendl("Initialisation Failed. Exiting ...");
		exit(-1);
	}
	opengl_set_buffers(sc);
	opengl_load_shaders(sc);
	opengl_set_matrices(sc);
	opengl_load_textures(sc);
	check_opengl_errors(sc);
	event_init(sc);
	opengl_drawing(sc);
}

void	check_opengl_errors(t_scop *sc)
{
	GLint		is_linked;
	GLenum		err;

	glGetProgramiv(sc->main_shader_programme, GL_LINK_STATUS, &is_linked);
	if (is_linked == GL_FALSE)
		printf("Error: Shader programme NOT linked\n");
	else
		printf("Shader programme linked\n");
	is_linked = 0;
	err = GL_NO_ERROR;
	while ((err = glGetError()) != GL_NO_ERROR)
		printf("OpenGL Error: %u\n", err);
}

void	int_handler(int sig)
{
	if (sig)
	{
	}
	deallocate_variables(g_global_sc);
}

int		main(int argc, char **argv)
{
	t_scop		sc;

	g_global_sc = &sc;
	if (argc == 2)
	{
		if (get_obj(&sc, argv[1]) == 0)
		{
			data_init(&sc);
			load_textures(&sc);
			init_dictionnaries(&sc);
			parse_obj(&sc);
			count_values(&sc);
			allocate_variables(&sc);
			signal(SIGINT, int_handler);
			get_values(&sc);
			set_model_colors(&sc);
			generate_uvs(&sc);
			generate_transition_points(&sc);
			scop(&sc);
		}
	}
	else
		ft_putendl("Usage: ./scop [file.obj]");
	return (0);
}
