/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/25 14:41:01 by aleung-c          #+#    #+#             */
/*   Updated: 2016/08/25 14:41:07 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H


# include "../libft/libft.h"
# include <unistd.h> //
# include <stdio.h> //
# include <stdlib.h>
# include "X.h"
//# include <X11/Xlib.h>
# include <mlx.h>

// Linking SDL2
//# include <SDL2/SDL.h>

// linking GLFW
# include "../glfw-3.2.1/include/GLFW/glfw3.h"

// Linking OpenGL
# if defined(__APPLE__)
# include <OpenGL/gl3.h>
# include <OpenGL/gl3ext.h>
// #  include <OpenGL/gl.h>
// # include <OpenGL/glext.h>
 # include <OpenGL/glu.h>
 # include <GLUT/glut.h>

# else
// #  include <GL/gl3.h>
// #  include <GL/gl.h>
 # include <GL/glu.h>
 # include <GL/glew.h>
# endif



typedef struct	s_scop
{
	GLFWwindow			*window;
	//SDL_Window			*window;
	//SDL_GLContext		*main_context;
	//SDL_Renderer		*renderer;

	int					escape_pressed;

}				t_scop;

/*
**	Function Prototypes.
*/




#endif