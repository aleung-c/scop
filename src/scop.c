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
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	

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

	// -------------------------------------------------------------------------- //
	//	VAO - Vertex Array object												  //
	// -------------------------------------------------------------------------- //
	GLuint vao = 0;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// -------------------------------------------------------------------------- //
	//	VBO - Vertex buffer object												  //
	// -------------------------------------------------------------------------- //
	// generating vbo buffers
	GLuint			vbo;
	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, (sc->nb_vertices * 4) * sizeof(float), sc->obj_vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);

	// -------------------------------------------------------------------------- //
	//	EBO - Buffer object	of indices											  //
	// -------------------------------------------------------------------------- //
	// generating element array buff;
	GLuint ebo;
	glGenBuffers (1, &ebo);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (sc->nb_faces_3 * 3) * sizeof(GL_UNSIGNED_INT), sc->face_3_indices, GL_STATIC_DRAW);


	/*GLuint vao2 = 0;

	glGenVertexArrays(1, &vao2);

	glBindVertexArray(vao2);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo2);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);*/

	// -------------------------------------------------------------------------- //
	//	Shaders																	  //
	// -------------------------------------------------------------------------- //
	// Go get Position shader
	sc->vertex_shader_1 = get_file_content("./shaders/vshader_1.vs");
	sc->fragment_shader_1 = get_file_content("./shaders/fshader_1.fs");

	// Create shader programme
	GLuint vs = glCreateShader (GL_VERTEX_SHADER);
	glShaderSource (vs, 1, (const char * const *)&sc->vertex_shader_1, NULL);
	glCompileShader (vs);
	GLuint fs = glCreateShader (GL_FRAGMENT_SHADER);
	glShaderSource (fs, 1, (const char * const *)&sc->fragment_shader_1, NULL);
	glCompileShader (fs);

	GLuint shader_programme = glCreateProgram ();
	glAttachShader (shader_programme, fs);
	glAttachShader (shader_programme, vs);
	glLinkProgram (shader_programme);
	glUseProgram(shader_programme);

	// setting uniform values for model
	GLint uniform_mat = glGetUniformLocation(shader_programme, "identity_matrix");
	if (uniform_mat != -1)
	{
		glUniformMatrix4fv(uniform_mat, 1, GL_FALSE, &sc->matrix_identity[0][0]);
	}
	uniform_mat = glGetUniformLocation(shader_programme, "model_translation_matrix");
	if (uniform_mat != -1)
	{
		set_translation_matrix(sc, 0.0, 0.0, -1.10);
		glUniformMatrix4fv(uniform_mat, 1, GL_FALSE, &sc->matrix_translation[0][0]);
	}
	uniform_mat = glGetUniformLocation(shader_programme, "scaling_matrix");
	if (uniform_mat != -1)
	{
		set_scaling_matrix(sc, 0.2);
		glUniformMatrix4fv(uniform_mat, 1, GL_FALSE, &sc->matrix_scaling[0][0]);
	}
	uniform_mat = glGetUniformLocation(shader_programme, "rotation_x_matrix");
	if (uniform_mat != -1)
	{
		set_x_rotation_matrix(sc, 0.0);
		glUniformMatrix4fv(uniform_mat, 1, GL_FALSE, &sc->matrix_x_rotation[0][0]);
	}
	uniform_mat = glGetUniformLocation(shader_programme, "rotation_y_matrix");
	if (uniform_mat != -1)
	{
		set_y_rotation_matrix(sc, 0.0);
		glUniformMatrix4fv(uniform_mat, 1, GL_FALSE, &sc->matrix_y_rotation[0][0]);
	}
	uniform_mat = glGetUniformLocation(shader_programme, "rotation_z_matrix");
	if (uniform_mat != -1)
	{
		set_z_rotation_matrix(sc, 0.0);
		glUniformMatrix4fv(uniform_mat, 1, GL_FALSE, &sc->matrix_z_rotation[0][0]);
	}
	
	// setting uniform values for view (camera pos)
	uniform_mat = glGetUniformLocation(shader_programme, "view_translation_matrix");
	if (uniform_mat != -1)
	{
		set_translation_matrix(sc, -sc->camera_pos.x, -sc->camera_pos.y, -sc->camera_pos.z); // setting camera pos.
		glUniformMatrix4fv(uniform_mat, 1, GL_FALSE, &sc->matrix_translation[0][0]);
	}

	uniform_mat = glGetUniformLocation(shader_programme, "view_orientation_matrix");
	if (uniform_mat != -1)
	{
		glUniformMatrix4fv(uniform_mat, 1, GL_FALSE, &sc->matrix_view_orientation[0][0]);
	}
	
	// setting uniform value for projection
	uniform_mat = glGetUniformLocation(shader_programme, "perspective_projection_matrix");
	if (uniform_mat != -1)
	{
		glUniformMatrix4fv(uniform_mat, 1, GL_FALSE, &sc->matrix_perspective_projection[0][0]);
	}


	// check if shader is compiled and linked;
	GLint isLinked = 0;
	glGetProgramiv(shader_programme, GL_LINK_STATUS, &isLinked);
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

	// -------------------------------------------------------------------------- //
	//	DRAWING																	  //
	// -------------------------------------------------------------------------- //
	float i = 0.0;
	while (!glfwWindowShouldClose(sc->window))
	{
		// wipe the drawing surface clear
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shader_programme);
		i += 0.005;
		uniform_mat = glGetUniformLocation(shader_programme, "rotation_y_matrix");
		if (uniform_mat != -1)
		{
			set_y_rotation_matrix(sc, i);
			glUniformMatrix4fv(uniform_mat, 1, GL_FALSE, &sc->matrix_y_rotation[0][0]);
		}
		//glBindVertexArray (vao);

		// draw points 0-3 from the currently bound VAO with current in-use shader
		//glDrawArrays (GL_POINTS, 0, sc->nb_vertices * 4);
		
		//glDrawArrays (GL_TRIANGLES, 0, ((sc->nb_faces_3 * 3) * 3));
		glDrawElements(GL_TRIANGLES, sc->nb_faces_3 * 3, GL_UNSIGNED_INT, NULL);
		
		// update other events like input handling 
		glfwPollEvents();
		// put the stuff we've been drawing onto the display
		glfwSwapBuffers(sc->window);
	}
}

void		data_init(t_scop *sc)
{
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
	sc->itmp = 0;
	sc->faces_itmp = 0;
	sc->indices_itmp = 0;
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

}

void		allocate_variables(t_scop *sc)
{
	if (!(sc->obj_vertices = (float *)malloc(sizeof(float) * sc->nb_vertices * 4)))
	{
		ft_putendl("vertices allocation failed.");
		exit (-1);
	}
	if (!(sc->obj_faces_3 = (float *)malloc(sizeof(float) * (sc->nb_faces_3 * 3) * 3)))
	{
		ft_putendl("faces_3 - 3 vertices allocation failed.");
		exit (-1);
	}
	if (!(sc->face_3_indices = (unsigned int *)malloc(sizeof(GL_UNSIGNED_INT) * (sc->nb_faces_3 * 3))))
	{
		ft_putendl("faces_3 - indices allocation failed.");
		exit (-1);
	}
	ft_putendl("- obj file variables allocated.");
}

int		main(int argc, char **argv)
{
	t_scop		sc;

	if (argc == 2)
	{
		if (get_obj(&sc, argv[1]) == 0) // open file and fill chained list of tokens(lexer).
		{
			data_init(&sc); // set all values to zero;
			init_dictionnaries(&sc); // init dictionnaries with authorised obj words.
			parse_obj(&sc); // parse the obj: are these lines corrects ?
			count_values(&sc); // has to count for mallocating.
			allocate_variables(&sc);
			get_values(&sc); // fill values in mallocated vars;
			
			scop(&sc);
		}
	}
	else
	{
		ft_putendl("Usage: ./scop [file.obj]");
	}
	return (0);
}
