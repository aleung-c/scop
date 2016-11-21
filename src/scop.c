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
	sc->window = glfwCreateWindow(640, 480, "Hello Triangle", NULL, NULL);
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

	// setting uniform values for model
	GLint uniform_mat = glGetUniformLocation(sc->main_shader_programme, "identity_matrix");
	if (uniform_mat != -1)
	{
		glUniformMatrix4fv(uniform_mat, 1, GL_FALSE, &sc->matrix_identity[0][0]);
	}
	uniform_mat = glGetUniformLocation(sc->main_shader_programme, "model_recenter_translation_matrix");
	if (uniform_mat != -1)
	{
		set_translation_matrix(sc,
			-sc->bounding_box_center.x,
			-sc->bounding_box_center.y,
			-sc->bounding_box_center.z);
		glUniformMatrix4fv(uniform_mat, 1, GL_FALSE, &sc->matrix_translation[0][0]);
	}

	uniform_mat = glGetUniformLocation(sc->main_shader_programme, "model_translation_matrix");
	if (uniform_mat != -1)
	{
		set_translation_matrix(sc, 0.0, 0.0, -1.10);
		glUniformMatrix4fv(uniform_mat, 1, GL_FALSE, &sc->matrix_translation[0][0]);
	}
	uniform_mat = glGetUniformLocation(sc->main_shader_programme, "scaling_matrix");
	if (uniform_mat != -1)
	{
		set_scaling_matrix(sc, 0.2);
		glUniformMatrix4fv(uniform_mat, 1, GL_FALSE, &sc->matrix_scaling[0][0]);
	}
	uniform_mat = glGetUniformLocation(sc->main_shader_programme, "rotation_x_matrix");
	if (uniform_mat != -1)
	{
		set_x_rotation_matrix(sc, 0.0);
		glUniformMatrix4fv(uniform_mat, 1, GL_FALSE, &sc->matrix_x_rotation[0][0]);
	}
	uniform_mat = glGetUniformLocation(sc->main_shader_programme, "rotation_y_matrix");
	if (uniform_mat != -1)
	{
		set_y_rotation_matrix(sc, 0.0);
		glUniformMatrix4fv(uniform_mat, 1, GL_FALSE, &sc->matrix_y_rotation[0][0]);
	}
	uniform_mat = glGetUniformLocation(sc->main_shader_programme, "rotation_z_matrix");
	if (uniform_mat != -1)
	{
		set_z_rotation_matrix(sc, 0.0);
		glUniformMatrix4fv(uniform_mat, 1, GL_FALSE, &sc->matrix_z_rotation[0][0]);
	}
	
	// setting uniform values for view (camera pos)
	uniform_mat = glGetUniformLocation(sc->main_shader_programme, "view_translation_matrix");
	if (uniform_mat != -1)
	{
		set_translation_matrix(sc, -sc->camera_pos.x, -sc->camera_pos.y, -sc->camera_pos.z); // setting camera pos.
		glUniformMatrix4fv(uniform_mat, 1, GL_FALSE, &sc->matrix_translation[0][0]);
	}

	uniform_mat = glGetUniformLocation(sc->main_shader_programme, "view_orientation_matrix");
	if (uniform_mat != -1)
	{
		glUniformMatrix4fv(uniform_mat, 1, GL_FALSE, &sc->matrix_view_orientation[0][0]);
	}
	
	// setting uniform value for projection
	uniform_mat = glGetUniformLocation(sc->main_shader_programme, "perspective_projection_matrix");
	if (uniform_mat != -1)
	{
		glUniformMatrix4fv(uniform_mat, 1, GL_FALSE, &sc->matrix_perspective_projection[0][0]);
	}

	// -------------------------------------------------------------------------- //
	//	Texture loading in the engine.											  //
	// -------------------------------------------------------------------------- //
	// Create one OpenGL texture
	GLuint textureID;
	glGenTextures(1, &textureID);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, sc->default_texture.width, sc->default_texture.height, 0,
		GL_BGR, GL_UNSIGNED_BYTE, sc->default_texture.data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	// bind texture to fragment shader uniform sampler2D
	uniform_mat = glGetUniformLocation(sc->main_shader_programme, "tex");
	glUniform1i(uniform_mat, 0);

	/*glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);*/



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
	
	// matrices.
	init_translation_matrix(sc);
	init_scaling_matrix(sc);
	init_identity_matrix(sc);
	init_x_rotation_matrix(sc);
	init_y_rotation_matrix(sc);
	init_z_rotation_matrix(sc);

	// scene settings
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
	if (!(sc->faces_uv = (float *)malloc(sizeof(float) * sc->total_faces * 3 * 2))) // for each face
	{
		ft_putendl("faces uv allocation failed.");
		exit (-1);
	}
	if (!(sc->vertex_color_values = (float *)malloc(sizeof(float) * (sc->total_faces * 3) * 3))) // for each face
	{
		ft_putendl("color buffer allocation failed.");
		exit (-1);
	}
	if (!(sc->vertex_color_values_copy = (float *)malloc(sizeof(float) * (sc->total_faces * 3) * 3))) // for each face
	{
		ft_putendl("color buffer copy allocation failed.");
		exit (-1);
	}
	ft_putendl("- obj file variables allocated.");
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
			get_values(&sc); // fill values in mallocated vars;
			set_model_colors(&sc); // set color for each v of each face.
			if (sc.nb_texture_vertices == 0)
			{
				generate_uvs(&sc);
			}
			scop(&sc);
		}
	}
	else
	{
		ft_putendl("Usage: ./scop [file.obj]");
	}
	return (0);
}
