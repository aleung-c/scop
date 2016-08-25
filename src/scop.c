/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/25 14:40:50 by aleung-c          #+#    #+#             */
/*   Updated: 2016/08/25 14:40:53 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

int InitSDL(t_scop *sc)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		return (-1);
	}

	// Create an application window with the following settings:
	sc->window = SDL_CreateWindow(
		"An SDL2 window",					// window title
		SDL_WINDOWPOS_UNDEFINED,			// initial x position
		SDL_WINDOWPOS_UNDEFINED,			// initial y position
		640,								// width, in pixels
		480,								// height, in pixels
		SDL_WINDOW_OPENGL					// flags - see below
	);

	// Check that the window was successfully created
	if (sc->window == NULL)
	{
		// In the case that the window could not be made...
		printf("Could not create window: %s\n", SDL_GetError()); //
		return (-1);
	}
	SDL_GL_CreateContext(sc->window);
	// set Context variables for SDL and OpenGL;
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	// major.minor version setting ==> version 4.1 of OpenGL
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    // set the double buffering;
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    glDisable(GL_CULL_FACE);

	// Create renderer contexts.
	
	
	#ifndef __APPLE__
	glewExperimental = GL_TRUE;
	glewInit();
	#endif

	return (0);
	//sc->renderer = SDL_CreateRenderer(sc->window, -1, SDL_RENDERER_ACCELERATED);
}


/*
**	Main scop fonction;
*/
void scop(t_scop *sc)
{
	if (InitSDL(sc) == -1)
	{
		SDL_Quit();
		return;
	}

	// ----------------------- Enter objects in GPU;
	GLfloat points[] = {
	   0.0f,  0.5f,  0.0f,
	   0.5f, -0.5f,  0.0f,
	  -0.5f, -0.5f,  0.0f
	};

	// Vertex Buffer Object (VBO)
	// generating the Vertex Buffer Object (VBO) and binding its datas.
	//const uint32_t countVBOs = 1;
	GLuint vbo = 0; // where the ids will be added. must be of size of the nb of buffer we want;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof (GLfloat), points, GL_STATIC_DRAW);

	// Vertex Attribute Object (VBO)
	// creating Vertex Attribute Object (VAO). allows to give meaning to the datas we send in the buffer
	GLuint vao = 0;
	glGenVertexArraysAPPLE (1, &vao);
	glBindVertexArrayAPPLE (vao);
	glEnableVertexAttribArray (0);
	glBindBuffer (GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL); // 3 means every 3 floats, we have a vertex;

	// SHADERS
	// defining a shader and a shader fragment, the first one to position, the second to colour;
	const char *vertex_shader =
			"#version 410\n"
			"in vec3 vp;"
			"void main () {"
			"  gl_Position = vec4 (vp, 0.5);"
			"}";
	const char *fragment_shader =
			"#version 410\n"
			"out vec4 frag_colour;"
			"void main () {"
			"  frag_colour = vec4 (0.5, 0.0, 0.5, 1.0);"
			"}";
	// now to put theses shader in actual glshaders;
	GLuint vs = glCreateShader (GL_VERTEX_SHADER);
	glShaderSource (vs, 1, &vertex_shader, NULL);
	glCompileShader (vs);
	GLuint fs = glCreateShader (GL_FRAGMENT_SHADER);
	glShaderSource (fs, 1, &fragment_shader, NULL);
	glCompileShader (fs);
	// these shaders must then be compiled in a single "program";
	GLuint shader_programme = glCreateProgram ();
	glAttachShader (shader_programme, fs);
	glAttachShader (shader_programme, vs);
	glLinkProgram (shader_programme);

	// ------------------------------- DRAWING
	SDL_Event event;
	sc->escape_pressed = 0;

	while (sc->escape_pressed == 0)
	{
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear (GL_COLOR_BUFFER_BIT);
		glUseProgram (shader_programme);
		glBindVertexArrayAPPLE (vao);
		// draw points 0-3 from the currently bound VAO with current in-use shader
		glDrawArrays (GL_TRIANGLES, 0, 3);

		// Swap our buffers to make our changes visible
		

		while( SDL_PollEvent( &event ) )
		{
			if (event.type == SDL_KEYDOWN)
    		{
    			if (event.key.keysym.sym == SDLK_r)
				{
					glClearColor(1.0, 0.0, 0.0, 1.0);
					glClear(GL_COLOR_BUFFER_BIT);
					SDL_GL_SwapWindow(sc->window);
					break;
				}
    			sc->escape_pressed = 1;
    			break ;
    		}
    	}
    	SDL_GL_SwapWindow(sc->window);
	}
	
	//SDL_Delay(3000);	// Pause execution for 3000 milliseconds, for example

	// Close and destroy the window
	SDL_DestroyWindow(sc->window);
	// Clean up
	SDL_Quit();
}

int main(int argc, char **argv)
{
	t_scop		sc;

	if (argc != 0 && argv)
	{
		scop(&sc);
	}

	return (0);
}
