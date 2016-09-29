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

	glEnable(GL_PROGRAM_POINT_SIZE);
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
	//	Create points for objects												  //
	// -------------------------------------------------------------------------- //
	/*float points[] = {
		0.0f,  0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f
	};*/

		/*for (int i = 0; i < sc->nb_vertices; i++)
		{
			printf("val = %f \n", sc->obj_vertices[i]);
			//sleep(1);
		}*/


	// -------------------------------------------------------------------------- //
	//	VBO - Vertex buffer object												  //
	// -------------------------------------------------------------------------- //
	GLuint vbo = 0;
	glGenBuffers (1, &vbo);
	glBindBuffer (GL_ARRAY_BUFFER, vbo);
	glBufferData (GL_ARRAY_BUFFER, (sc->nb_vertices) * sizeof (float), sc->obj_vertices, GL_STATIC_DRAW);

	GLuint vbo2 = 0;
	glGenBuffers (1, &vbo2);
	glBindBuffer (GL_ARRAY_BUFFER, vbo2);
	glBufferData (GL_ARRAY_BUFFER, (sc->nb_faces * 3) * sizeof (float), sc->obj_faces, GL_STATIC_DRAW);

	// -------------------------------------------------------------------------- //
	//	VAO - Vertex Array object												  //
	// -------------------------------------------------------------------------- //
	GLuint vao = 0;

	glGenVertexArrays(1, &vao);

	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, NULL);

	GLuint vao2 = 0;

	glGenVertexArrays(1, &vao2);

	glBindVertexArray(vao2);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo2);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, NULL);



	// -------------------------------------------------------------------------- //
	//	Shaders																	  //
	// -------------------------------------------------------------------------- //
	// Position shader
	const char* vertex_shader =
		"#version 410\n"
		"in vec3 vp;"
		"void main () {"
		"  gl_Position = vec4 (vp, 100.0);"
		"  gl_PointSize = 1.0;"
		"}";

	// Color shaders
	const char* fragment_shader =
		"#version 410\n"
		"out vec4 frag_colour;"
		"void main () {"
		"  frag_colour = vec4 (1.0, 1.0, 1.0, 1.0);"
		"}";

	// Create shader programme
	GLuint vs = glCreateShader (GL_VERTEX_SHADER);
	glShaderSource (vs, 1, &vertex_shader, NULL);
	glCompileShader (vs);
	GLuint fs = glCreateShader (GL_FRAGMENT_SHADER);
	glShaderSource (fs, 1, &fragment_shader, NULL);
	glCompileShader (fs);

	GLuint shader_programme = glCreateProgram ();
	glAttachShader (shader_programme, fs);
	glAttachShader (shader_programme, vs);
	glLinkProgram (shader_programme);

	// check if shader is compiled and linked;
	GLint isLinked = 0;
	glGetProgramiv(shader_programme, GL_LINK_STATUS, &isLinked);
	if (isLinked == GL_FALSE)
	{
		printf("Error: Shader programme NOT linked\n");
	} else
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
	while (!glfwWindowShouldClose(sc->window))
	{

		// wipe the drawing surface clear
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram (shader_programme);
		glBindVertexArray (vao);

		// draw points 0-3 from the currently bound VAO with current in-use shader
		glDrawArrays (GL_POINTS, 0, sc->nb_vertices);

		glBindVertexArray(vao2);
		glDrawArrays (GL_TRIANGLES, 0, sc->nb_faces * 3);
		// update other events like input handling 
		glfwPollEvents ();
		// put the stuff we've been drawing onto the display
		glfwSwapBuffers (sc->window);
	}
}

int		main(int argc, char **argv)
{
	t_scop		sc;

	if (argc == 2)
	{
		if (get_obj(&sc, argv[1]) == 0)
		{
			scop(&sc);
		}
	}
	else
	{
		ft_putendl("Usage: ./scop [file.obj]");
	}
	return (0);
}