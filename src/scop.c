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
	
	// TODO : add a color vbo.

	// for the normals
	GLuint			nbo;
	glGenBuffers(1, &nbo);

	glBindBuffer(GL_ARRAY_BUFFER, nbo);
	glBufferData(GL_ARRAY_BUFFER, ((((sc->nb_faces_3 + (sc->nb_faces_4 * 2)) * 3) * 3) * 3) * sizeof(float), sc->faces_normals, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(1);
	

	// -------------------------------------------------------------------------- //
	//	EBO - Buffer object	of indices											  //
	// -------------------------------------------------------------------------- //
	// generating element array buff;
	GLuint ebo;
	glGenBuffers (1, &ebo);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (sc->nb_faces_3 * 3 + (sc->nb_faces_4 * 2) * 3) * sizeof(GL_UNSIGNED_INT), &sc->face_indices[0], GL_STATIC_DRAW);


	/*GLuint vao2 = 0;

	glGenVertexArrays(1, &vao2);

	glBindVertexArray(vao2);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo2);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);*/
	/*int i;
	for (i = 0; i < ((((sc->nb_faces_3 + (sc->nb_faces_4 * 2)) * 3) * 3) * 3); i += 3)
	{
		printf("normal : %fx %fy %fz \n", sc->faces_normals[i], sc->faces_normals[i + 1], sc->faces_normals[i + 2]);
	}
	printf("i = %d\n", i);*/
	

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
	uniform_mat = glGetUniformLocation(shader_programme, "model_recenter_translation_matrix");
	if (uniform_mat != -1)
	{
		set_translation_matrix(sc,
			-sc->bounding_box_center.x,
			-sc->bounding_box_center.y,
			-sc->bounding_box_center.z);
		glUniformMatrix4fv(uniform_mat, 1, GL_FALSE, &sc->matrix_translation[0][0]);
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
	uniform_mat = glGetUniformLocation(shader_programme, "tex");
	glUniform1i(uniform_mat, 0);

	//set bool for textures
	glUniform1i(glGetUniformLocation(shader_programme, "has_texture"), GL_FALSE);

	/*glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);*/



	// -------------------------------------------------------------------------- //
	//	Error checking															  //
	// -------------------------------------------------------------------------- //
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
	float i_axis = 0.0;
	while (!glfwWindowShouldClose(sc->window))
	{
		// wipe the drawing surface clear
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shader_programme);

		// change val to rotate model.
		i_axis += 0.005;
		uniform_mat = glGetUniformLocation(shader_programme, "rotation_y_matrix");
		if (uniform_mat != -1)
		{
			set_y_rotation_matrix(sc, i_axis);
			glUniformMatrix4fv(uniform_mat, 1, GL_FALSE, &sc->matrix_y_rotation[0][0]);
		}
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		//glBindVertexArray (vao);

		// draw points 0-3 from the currently bound VAO with current in-use shader
		//glDrawArrays (GL_POINTS, 0, sc->nb_vertices * 4);
		
		//glDrawArrays (GL_TRIANGLES, 0, ((sc->nb_faces_3 * 3) * 3));
		glDrawElements(GL_TRIANGLES, (sc->nb_faces_3 * 3 + (sc->nb_faces_4 * 2) * 3), GL_UNSIGNED_INT, (void *)0);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		// update other events like input handling 
		glfwPollEvents();
		// put the stuff we've been drawing onto the display
		glfwSwapBuffers(sc->window);
	}

// ggaubin's code.	
/*
	static void		fifty_fifty(t_object *o, t_mat4 p, t_mat4 view)
{
	update_mat(&o->model, o->translation, o->rotation, o->scale);
	glUseProgram(o->program);
	glUniformMatrix4fv(o->view_matrix_id, 1, GL_FALSE, (void *)&view);
	glUniformMatrix4fv(o->projection_matrix_id, 1, GL_FALSE,\
						(void *)&p);
	glUniformMatrix4fv(o->model_matrix_id, 1, GL_FALSE, (void *)&(o->model));
	glUniform1f(o->texture_mix_id, o->texture_mix_coeff);
	set_ambiant_color(o);
	glBindTexture(GL_TEXTURE_2D, o->texture);
	glBindBuffer(GL_ARRAY_BUFFER, o->vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, o->cvbo);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}

void			draw(t_object *o, GLenum mode, t_mat4 projection, t_mat4 view)
{
	fifty_fifty(o, projection, view);
	glBindBuffer(GL_ARRAY_BUFFER, o->nbo);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, o->ubo);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glDrawArrays(mode, 0, o->size_mesh / 3);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
}
*/
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
	sc->indices_itmp = 0;
	sc->normals_itmp = 0;
	sc->face_normals_itmp = 0;
	sc->faces_uv_itmp = 0;
	
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
	if (!(sc->obj_vertices = (float *)malloc(sizeof(float) * sc->nb_vertices * 4))) // v
	{
		ft_putendl("vertices allocation failed.");
		exit (-1);
	}
	if (!(sc->face_indices = (unsigned int *)malloc((sc->nb_faces_3 * 3 + (sc->nb_faces_4 * 2) * 3) * sizeof(GL_UNSIGNED_INT)))) // indices
	{
		ft_putendl("faces - indices allocation failed.");
		exit (-1);
	}
	if (!(sc->obj_normals = (float *)malloc(sizeof(float) * (sc->nb_normals_vertices) * 3))) // vn
	{
		ft_putendl("normal values allocation failed.");
		exit (-1);
	}
	if (!(sc->faces_normals = (float *)malloc(sizeof(float) * ((((sc->nb_faces_3 + (sc->nb_faces_4 * 2)) * 3) * 3) * 3)))) // for each face
	{
		ft_putendl("faces normals allocation failed.");
		exit (-1);
	}
	if (!(sc->obj_tex_coords = (float *)malloc(sizeof(float) * sc->nb_texture_vertices * 2))) // vt
	{
		ft_putendl("vt values allocation failed.");
		exit (-1);
	}
	if (!(sc->faces_uv = (float *)malloc(sizeof(float) * (sc->nb_faces_3 * 3 + (sc->nb_faces_4 * 2) * 3) * 2))) // for each face
	{
		ft_putendl("faces uv allocation failed.");
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
			load_textures(&sc);
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
