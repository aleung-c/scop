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

// -------------------------------------------------------------------------- //
//	Init opengl and glfw 													  //
//																			  //
// -------------------------------------------------------------------------- //
int		initGLFW(t_scop *sc)
{
	// start GL context and O/S window using the GLFW helper library
	if (!glfwInit ())
	{
		ft_putendl("ERROR: could not start GLFW3");
		return 1;
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
	// Create context
	glfwMakeContextCurrent (sc->window);
	return (0);
}

int initOpenGL(t_scop *sc)
{
	// get version info
	const GLubyte* renderer = glGetString (GL_RENDERER); // get renderer string
	const GLubyte* version = glGetString (GL_VERSION); // version as a string
	printf ("\nRenderer: %s\n", renderer);
	printf ("OpenGL version supported %s\n", version);

	//glEnable(GL_PROGRAM_POINT_SIZE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_BLEND);
	//glEnable(GL_CULL_FACE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glEnable(GL_LIGHTING);	// Active l'éclairage
 	//glEnable(GL_LIGHT0);	// Allume la lumière n°1

	#ifndef __APPLE__
	glewExperimental = GL_TRUE;
	glewInit();
	#endif
	return (0);
}

/*
**	Main scop fonction;
*/
void	scop(t_scop *sc)
{
	if (initGLFW(sc) == -1 || initOpenGL(sc) == -1)
	{
		ft_putendl("Initialisation Failed. Exiting ...");
		exit (-1);
	}
	
	opengl_set_buffers(sc); // opengl_set_buffers.c
	
	opengl_load_shaders(sc); // open_gl_load_shaders.c

	opengl_set_matrices(sc); // opengl_set_matrices.c

	opengl_load_textures(sc); // opengl_load_textures.c


	// -------------------------------------------------------------------------- //
	//	Error checking															  //
	// -------------------------------------------------------------------------- //
	// check if shader is compiled and linked;
	GLint isLinked = 0;
	glGetProgramiv(sc->main_shader_programme, GL_LINK_STATUS, &isLinked);
	if (isLinked == GL_FALSE)
	{
		printf("Error: Shader programme NOT linked\n");
	}
	else
	{
		printf("Shader programme linked\n");
	}

	// check for opengl errors.
	GLenum err = GL_NO_ERROR;
	while((err = glGetError()) != GL_NO_ERROR)
	{
		printf("OpenGL Error: %u\n", err);
	}

	event_init(sc);
	
	opengl_drawing(sc);
}

void		data_init(t_scop *sc)
{
	// obj value counters.
	sc->nb_vertices = 0;
	sc->nb_texture_vertices = 0;
	sc->nb_normals_vertices = 0;
	sc->nb_parameter_space_vertices = 0;
	sc->nb_faces_3 = 0;
	sc->nb_faces_4 = 0;
	sc->nb_faces_more = 0;
	sc->nb_obj = 0;
	sc->nb_groups = 0;
	sc->nb_materials = 0;

	// counters
	sc->itmp = 0;
	sc->faces_vertices_itmp = 0;
	sc->indices_itmp = 0;
	sc->normals_itmp = 0;
	sc->face_normals_itmp = 0;
	sc->faces_uv_itmp = 0;
	sc->vcolor_itmp = 0;
	sc->tpoints_i = 0;

	// matrices.
	init_translation_matrix(sc);
	init_scaling_matrix(sc);
	init_identity_matrix(sc);
	init_x_rotation_matrix(sc);
	init_y_rotation_matrix(sc);
	init_z_rotation_matrix(sc);

	// scene settings
	sc->zoom_level = 0.2;
	sc->camera_pos.x = 0.0;
	sc->camera_pos.y = 0.0;
	sc->camera_pos.z = 0.0;
	sc->camera_lookat.x = 0.0;
	sc->camera_lookat.y = 0.0;
	sc->camera_lookat.z = 1.0;
	init_view_orientation_matrix(sc);
	init_view_translation_matrix(sc);
	sc->camera_near = 0.1;
	sc->camera_far = 100.0;
	sc->camera_fov = 60.0;
	sc->camera_aspect = 1.33; // 4/3, 16/9, etc 1 = 4/4
	init_perspective_projection_matrix(sc);
	set_vec(&sc->bounding_box_center, 0.0, 0.0, 0.0);
	set_vec(&sc->bounding_box_max, 0.0, 0.0, 0.0);
	set_vec(&sc->bounding_box_min, 0.0, 0.0, 0.0);
	set_vec(&sc->light_pos, 2.0, 0.0, 0.0);
}

void	int_handler(int sig)
{
	deallocate_variables(g_global_sc);
}

int		main(int argc, char **argv)
{
	t_scop		sc;

	g_global_sc = &sc;
	if (argc == 2)
	{
		if (get_obj(&sc, argv[1]) == 0) // open file and fill chained list of tokens(lexer).
		{
			data_init(&sc); // set all values to zero;
			load_textures(&sc);
			init_dictionnaries(&sc); // init dictionnaries with authorised obj words.
			parse_obj(&sc); // parse the obj: are these lines corrects ?
			count_values(&sc); // has to count for mallocating.
			allocate_variables(&sc);
			signal(SIGINT, int_handler);
			get_values(&sc); // fill values in mallocated vars;
			set_model_colors(&sc); // set color for each v of each face.
			if (sc.nb_texture_vertices == 0)
			{
				generate_uvs(&sc);
			}
			generate_transition_points(&sc);
			scop(&sc);
		}
	}
	else
	{
		ft_putendl("Usage: ./scop [file.obj]");
	}
	return (0);
}
