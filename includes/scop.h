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
# include <math.h>

// Linking SDL2
//# include <SDL2/SDL.h>

// linking GLFW
# include "../glfw-3.2.1/include/GLFW/glfw3.h"

// Linking OpenGL
# if defined(__APPLE__)
#  define __gl_h_
#  define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
#  include <OpenGL/gl3.h>
#  include <OpenGL/gl3ext.h>
// #  include <OpenGL/gl.h>
// # include <OpenGL/glext.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>

# else
#  include <GL/gl3.h>
 // #  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/glew.h>
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



typedef enum						e_token_type
{
	word,
	numeric_value,
	indices,
	file_name,

	error
}									s_token_type;

// lexer parser
typedef struct						s_token
{
	int								line_number;
	int								col_number;
	s_token_type					token_type;
	char							*value;
	char							*value_pointer; // maintaining ptr to be freed;
	struct s_token					*next;
	
}									t_token;

typedef struct						s_dictionnary_word
{
	char							*string;
	struct s_dictionnary_word		*next;
}									t_dictionnary_word;

typedef	struct						s_vec3
{
	float							x;
	float							y;
	float							z;
}									t_vec3;

typedef struct						s_bmp_texture
{
	// Data read from the header of the BMP file
	unsigned char					header[54]; // Each BMP file begins by a 54-bytes header
	unsigned int					data_pos;     // Position in the file where the actual data begins
	unsigned int					width;
	unsigned int					height;
	unsigned int					image_size;   // = width*height*3
	// Actual RGB data
	unsigned char					*data;
}									t_bmp_texture;

typedef struct						s_color
{
	float							r;
	float							g;
	float							b;
	float							a;
}									t_color;

typedef struct						s_scop
{
	GLFWwindow						*window;
	//SDL_Window					*window;
	//SDL_GLContext					*main_context;
	//SDL_Renderer					*renderer;

	// File Lexer / parser
	FILE							*fp;
	t_token							*obj_token_list;
	t_token							*tmp;

	// file parsing datas
	t_dictionnary_word				*word_dictionnary_list;
	unsigned long int				nb_vertices; 					// v
	unsigned long int				nb_texture_vertices;			// vt
	unsigned long int				nb_normals_vertices;			// vn
	unsigned long int				nb_parameter_space_vertices;	// vp
	unsigned long int				nb_faces_3;						// f
	unsigned long int				nb_faces_4;
	unsigned long int				nb_faces_more;
	unsigned long int				nb_obj;
	unsigned long int				nb_groups;
	unsigned long int				nb_materials;

	unsigned long int				total_faces;


	t_token							*inline_token;
	int								inline_i;

	// actual variables
	float							*obj_vertices;
	int								itmp;

	float							*faces_vertices; // for rough faces.
	int								faces_vertices_itmp;

	unsigned int					*face_indices;
	int								indices_itmp;

	float							*obj_normals; // vn -> just the stocked values.
	int								normals_itmp;

	float							*faces_normals; // for each face(3 vertices) -> 3 float ordered.
	int								face_normals_itmp;


	float							*obj_tex_coords; // vt
	int								tex_coord_itmp;

	float							*faces_uv; // uv for faces. to push some textures.
	int								faces_uv_itmp;

	float							*vertex_color_values; // for faces of diff colors.
	int								vcolor_itmp;

	int								*transition_points;
	int								tpoints_i;
	int								transition_value;

	t_bmp_texture					default_texture;
	t_bmp_texture					second_texture;

	GLuint							main_shader_programme;

	// buffer references;
	GLuint							vao; // vertex array object
	GLuint							vbo; // vertex buffer object
	GLuint							nbo; // normals buffer object
	GLuint							cbo; // color buffer object
	GLuint							ubo; // uv buffer object
	GLuint							tbo; // transition flags buffer object

	GLuint							ebo; // element buffer objects -> indices.
	GLuint							fvbo; // face vertices buffer.

	// matrix handling
	float							matrix_identity[4][4];
	float							matrix_translation[4][4];
	float							matrix_scaling[4][4];

	float							matrix_x_rotation[4][4];
	float							matrix_y_rotation[4][4];
	float							matrix_z_rotation[4][4];

	float							matrix_view_orientation[4][4];
	float							matrix_view_translation[4][4];

	float							matrix_perspective_projection[4][4];
	float							matrix_orthographic_projection[4][4];

	// stocking shaders
	char							*vertex_shader_1;
	char							*fragment_shader_1;

	// scene settings
	t_vec3							camera_pos;
	t_vec3							camera_lookat;

	float							camera_near;
	float							camera_far;
	float							camera_left;
	float							camera_right;
	float							camera_top;
	float							camera_bottom;
	float							camera_fov;
	float							camera_aspect;

	t_vec3							light_pos;

	t_vec3							bounding_box_center;
	t_vec3							bounding_box_max;
	t_vec3							bounding_box_min;

	float							i_axis;

	// events
	int								escape_pressed;

	int								on_standby;
	int								in_transition;
	int								is_textured;
	int								using_array;

	int								transition_counter;
	int								buffer_i;

	int								is_rotating;
	int 							is_rotating_y;
	int 							is_rotating_x;
	int 							is_rotating_z;

}									t_scop;

/*
**	global access for GLFW.
*/
t_scop								*g_global_sc;

/*
**	Function Prototypes.
*/

/*
**	Get Object and parse it;
*/
int									get_obj(t_scop *sc, char *arg);

void								lex_obj_line(t_scop *sc, char *line, int line_number);
void								set_token_type(t_token *cur_token, char *token_str);
void								add_token_to_list(t_scop *sc, t_token *obj_token_list, t_token *cur_token);

int									regex_match(char *string_to_search, char *regex_str);

void								print_tokens(t_scop *sc);
void								print_parser_error(t_token *token, char *error_string);


void								init_dictionnaries(t_scop *sc);
void								add_word_to_dictionnary(t_scop *sc, char *word);
int									is_word_in_dictionnary(t_scop *sc, char *word);

void								parse_obj(t_scop *sc);
int									check_tokens(t_scop *sc);
void								change_token_indice_type(t_scop *sc);

// token steps
void								check_token_order(t_scop *sc);
void								dictionnary_comparison(t_scop *sc);

void								data_init(t_scop *sc);

void								count_values(t_scop *sc);
void								get_values(t_scop *sc);
void								fill_vertex(t_scop *sc, t_token *token);
void								fill_tex_coord(t_scop *sc, t_token *token);
void								fill_normals(t_scop *sc, t_token *token);
void								fill_face(t_scop *sc, t_token *token);
void								fill_face3(t_scop *sc, t_token *token);
void								fill_face4(t_scop *sc, t_token *token);


void								fill_face_split_indice(t_scop *sc, t_token *inline_token);
void								fill_face_vertices(t_scop *sc, unsigned int indice);


void								add_face_normal_from_indice(t_scop *sc, char *splitted_indice);
void								add_face_uv_from_indice(t_scop *sc, char *splitted_indice);

void								set_bounding_box_limits(t_scop *sc);
void								set_bounding_box_center(t_scop *sc);

void								set_model_colors(t_scop *sc);
void								generate_uvs(t_scop *sc);
void								generate_transition_points(t_scop *sc);

void								allocate_variables(t_scop *sc);
void								deallocate_variables(t_scop *sc);

// matrix handling
//	model matrices
void								init_identity_matrix(t_scop *sc);
void								init_translation_matrix(t_scop *sc);
void								set_translation_matrix(t_scop *sc, float x, float y, float z);
void								init_scaling_matrix(t_scop *sc);
void								set_scaling_matrix(t_scop *sc, float scale);

//	model rotation matrices
void								init_x_rotation_matrix(t_scop *sc);
void								init_y_rotation_matrix(t_scop *sc);
void								init_z_rotation_matrix(t_scop *sc);

void								set_x_rotation_matrix(t_scop *sc, float rot);
void								set_y_rotation_matrix(t_scop *sc, float rot);
void								set_z_rotation_matrix(t_scop *sc, float rot);

//	view matrices
void								init_view_orientation_matrix(t_scop *sc);
void								init_view_translation_matrix(t_scop *sc);

// projection matrices
void								init_perspective_projection_matrix(t_scop *sc);

void								load_textures(t_scop *sc);
t_bmp_texture						load_texture_file(t_bmp_texture *texture, char *path);

/*
**	Displaying the object -> glfw and open gl.
*/

char								*get_file_content(char *file_path);

int									initGLFW(t_scop *sc);
int									initOpenGL(t_scop *sc);

void								opengl_set_buffers(t_scop *sc);
void								opengl_load_shaders(t_scop *sc);
void								opengl_set_matrices(t_scop *sc);
void								opengl_load_textures(t_scop *sc);


void								opengl_drawing(t_scop *sc);

void								event_init(t_scop *sc);
void								event_process(t_scop *sc);
void								transition_one_face(t_scop *sc);

/*
**	utils
*/
void								set_vec(t_vec3 *v, float x, float y, float z);
t_vec3								normalize(t_vec3 v);
float								norme(t_vec3 v);
t_vec3								vec_sub(t_vec3 v1, t_vec3 v2);
t_vec3								vec_cross(t_vec3 v1, t_vec3 v2);
float								vec_magnitude(t_vec3 v);
float								vec_dot_product(t_vec3 v1, t_vec3 v2);
t_color								create_color(float r, float g, float b, float a);
t_color								set_color(t_color c, float r, float g, float b, float a);
float								set_gray_level(float color);

#endif