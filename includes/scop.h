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
//# include <unistd.h>
# include <stdio.h> //
# include <stdlib.h>
# include "X.h"
//# include <X11/Xlib.h>
# include <mlx.h>
# include <ctype.h>
# include <regex.h>

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
 #  include <GL/gl3.h>
 // #  include <GL/gl.h>
 # include <GL/glu.h>
 # include <GL/glew.h>
# endif

// color in text;
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
#define KRESET "\x1B[0m"

typedef enum	e_token_type
{
	word,
	numeric_value,
	indices,

	error
}				s_token_type;

// lexer parser
typedef struct						s_token
{
	int								line_number;
	int								col_number;
	s_token_type					token_type;
	char							*value;
	struct s_token					*next;
	
}									t_token;

typedef struct						s_scop
{
	GLFWwindow						*window;
	//SDL_Window					*window;
	//SDL_GLContext					*main_context;
	//SDL_Renderer					*renderer;

	// File Lexer / parser
	FILE							*fp;
	t_token							*obj_token_list;
	// file parsing datas
	unsigned long int				nb_vertices; 					// v
	unsigned long int				nb_texture_vertices;			// vt
	unsigned long int				nb_normals_vertices;			// vn
	unsigned long int				nb_parameter_space_vertices;	// vp
	unsigned long int				nb_faces;						// f
	unsigned long int				nb_obj;
	unsigned long int				nb_groups;
	unsigned long int				nb_materials;

	float							*obj_vertices;
	int								itmp;

	float							*obj_faces;
	int								faces_itmp;

	// events
	int								escape_pressed;
}									t_scop;



/*
**	Function Prototypes.
*/

/*
**	Get Object and parse it;
*/
int							get_obj(t_scop *sc, char *arg);

void						lex_obj(t_scop *sc);
void						lex_obj_line(t_scop *sc, char *line, int line_number);
void						set_token_type(t_token *cur_token, char *token_str);
void						add_token_to_list(t_scop *sc, t_token *obj_token_list, t_token *cur_token);

int							regex_match(char *string_to_search, char *regex_str);

void						parse_obj(t_scop *sc);
int							check_tokens(t_scop *sc);

void						data_init(t_scop *sc);

void						parse_pass1(t_scop *sc, FILE *fp);
void						parse_pass2(t_scop *sc, FILE *fp);

//void						parse_line_counting(t_scop *sc, char *line);
void						parse_line_filling(t_scop *sc, char *line);

void						allocate_variables(t_scop *sc);

void						put_vertex_in_var(t_scop *sc, char *line, int position);
void						put_faces_in_var(t_scop *sc, char *line, int position);


/*
**	Displaying the object -> glfw and open gl.
*/

int							initGLFW(t_scop *sc);
int							initOpenGL(t_scop *sc);

#endif