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
#include <sys/types.h>
#include <sys/stat.h>

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
	}								t_token;

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
	unsigned char					header[54];
	unsigned int					data_pos;
	unsigned int					width;
	unsigned int					height;
	unsigned int					image_size;

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

	FILE							*fp;
	t_token							*obj_token_list;
	t_token							*tmp;

	t_dictionnary_word				*word_dictionnary_list;
	unsigned long int				nb_vertices;
	unsigned long int				nb_texture_vertices;
	unsigned long int				nb_normals_vertices;
	unsigned long int				nb_parameter_space_vertices;
	unsigned long int				nb_faces_3;
	unsigned long int				nb_faces_4;
	unsigned long int				nb_faces_more;
	unsigned long int				nb_indices_more;
	unsigned long int				nb_obj;
	unsigned long int				nb_groups;
	unsigned long int				nb_materials;

	unsigned long int				total_faces;


	t_token							*inline_token;
	int								inline_i;

	// actual variables
	float							*obj_vertices;
	int								itmp;

	float							*faces_vertices;
	int								faces_vertices_itmp;

	unsigned int					*face_indices;
	int								indices_itmp;

	float							*obj_normals;
	int								normals_itmp;

	float							*faces_normals;
	int								face_normals_itmp;


	float							*obj_tex_coords;
	int								tex_coord_itmp;

	float							*faces_uv;
	int								faces_uv_itmp;

	float							*vertex_color_values;
	int								vcolor_itmp;

	int								*transition_points;
	int								tpoints_i;
	int								transition_value;

	t_bmp_texture					default_texture;
	t_bmp_texture					second_texture;

	GLuint							main_shader_programme;

	GLuint							vao;
	GLuint							vbo;
	GLuint							nbo;
	GLuint							cbo;
	GLuint							ubo;
	GLuint							tbo;

	GLuint							ebo;
	GLuint							fvbo;

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

	char							*vertex_shader_1;
	char							*fragment_shader_1;

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

	int								escape_pressed;

	int								on_standby;
	int								in_transition;
	int								is_textured;
	int								using_array;
	int								cur_texture_id;
	float							zoom_level;

	int								transition_counter;
	unsigned int					buffer_i;

	int								is_rotating;
	int 							is_rotating_y;
	int 							is_rotating_x;
	int 							is_rotating_z;

	int								has_stepped_back;

}									t_scop;

/*
**	global access for GLFW.
*/

t_scop								*g_global_sc;

/*
**	Function Prototypes.
*/

/*
**	Get Object and parse it -> Input.
*/

int									get_obj(t_scop *sc, char *arg);
int									is_directory(const char *path);

void								process_opened_file(t_scop *sc, FILE *fp);

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

void								check_token_order(t_scop *sc);
void								dictionnary_comparison(t_scop *sc);

/*
**	Data initiatlization
*/

void								data_init(t_scop *sc);
void								init_obj_value_counters(t_scop *sc);
void								init_simple_counters(t_scop *sc);
void								init_scene(t_scop *sc);

/*
**	obj value filling
*/

void								count_values(t_scop *sc);
void								count_face_values(t_scop *sc, t_token *token);
void								print_obj_value_numbers(t_scop *sc);

void								get_values(t_scop *sc);
void								fill_vertex(t_scop *sc, t_token *token);
void								fill_tex_coord(t_scop *sc, t_token *token);
void								fill_normals(t_scop *sc, t_token *token);
void								fill_face(t_scop *sc, t_token *token);
void								fill_face3(t_scop *sc, t_token *token);
void								fill_face4(t_scop *sc, t_token *token);
void								fill_face_more(t_scop *sc, t_token *token);

void								fill_face_split_indice(t_scop *sc, t_token *inline_token);
void								fill_face_indice_vertex(t_scop *sc, char *splitted_indice);
void								fill_face_vertices(t_scop *sc, unsigned int indice);


void								add_face_normal_from_indice(t_scop *sc, char *splitted_indice);
void								add_one_face_normal_from_indice(t_scop *sc, int indice_val);
void								add_face_uv_from_indice(t_scop *sc, char *splitted_indice);

/*
**	obj value to generate
*/

void								set_bounding_box_limits(t_scop *sc);
void								set_bounding_box_center(t_scop *sc);

void								set_model_colors(t_scop *sc);
void								add_one_face_color(t_scop *sc, float cur_color);

void								generate_uvs(t_scop *sc);
void								add_one_uv(t_scop *sc, float u, float v);
void								generate_transition_points(t_scop *sc);

/*
**	programm memory allocations
*/

void								allocate_variables(t_scop *sc);
void								allocate_variables_2(t_scop *sc);
void								error_allocation(char *msg_string);
void								deallocate_variables(t_scop *sc);

/*
**	Matrice initialization.
*/

void								init_identity_matrix(t_scop *sc);
void								init_translation_matrix(t_scop *sc);
void								set_translation_matrix(t_scop *sc, float x, float y, float z);
void								init_scaling_matrix(t_scop *sc);
void								set_scaling_matrix(t_scop *sc, float scale);

void								init_x_rotation_matrix(t_scop *sc);
void								init_y_rotation_matrix(t_scop *sc);
void								init_z_rotation_matrix(t_scop *sc);

void								set_x_rotation_matrix(t_scop *sc, float rot);
void								set_y_rotation_matrix(t_scop *sc, float rot);
void								set_z_rotation_matrix(t_scop *sc, float rot);

void								init_view_orientation_matrix(t_scop *sc);
void								init_view_translation_matrix(t_scop *sc);
void								init_view_orientation_matrix_part2(t_scop *sc, t_vec3 xaxis,
										t_vec3 yaxis, t_vec3 zaxis);

void								init_perspective_projection_matrix(t_scop *sc);
void								perspective_projection_matrix_part1(t_scop *sc);

/*
**	Texture handling.
*/

void								load_textures(t_scop *sc);
t_bmp_texture						load_texture_file(t_bmp_texture *texture, char *path);
void								check_bmp_format(t_bmp_texture *texture, FILE *file);

/*
**	Displaying the object -> glfw and open gl.
*/

char								*get_file_content(char *file_path);
char								*process_shader_opened_file(FILE *fp);

void								scop(t_scop *sc);

int									init_glfw(t_scop *sc);
int									init_opengl(t_scop *sc);
void								check_opengl_errors(t_scop *sc);
void								int_handler(int sig);

void								opengl_set_buffers(t_scop *sc);
void								opengl_set_gen_buffers(t_scop *sc);
void								opengl_set_vertice_buffers(t_scop *sc);
void								opengl_set_color_buffers(t_scop *sc);
void								opengl_load_shaders(t_scop *sc);
void								opengl_create_shader_programme(t_scop *sc, GLuint vs, GLuint fs);
void								opengl_set_matrices(t_scop *sc);
void								opengl_set_model_matrices(t_scop *sc);
void								opengl_set_view_matrices(t_scop *sc);
void								opengl_set_projection_matrices(t_scop *sc);

void								opengl_load_textures(t_scop *sc);
void								opengl_load_default_tex(t_scop *sc);
void								opengl_load_second_tex(t_scop *sc);

void								opengl_drawing(t_scop *sc);
void								opengl_drawing_enable_arrays(void);
void								opengl_drawing_set_zero_attribute(t_scop *sc);
void								opengl_drawing_disable_arrays(void);

/*
**	Events and key handling.
*/

void								event_init(t_scop *sc);
void								event_process(t_scop *sc);

void								events_rotations(t_scop *sc);
void								modify_uniform_matrice(t_scop *sc, float *matrice, char *uniform_string);

void								events_transition(t_scop *sc);
void								transition_n_faces(t_scop *sc, int n);
void								transition_one_face(t_scop *sc);

void								toggle_rotation(t_scop *sc, int key, int action);
void								toggle_rotation_change_1(t_scop *sc, int key, int action);
void								toggle_rotation_change_2(t_scop *sc, int key, int action);
void								toggle_transition_and_tswitch(t_scop *sc, int key, int action);
void								set_zoom_level(t_scop *sc, int key, int action);
void								apply_step_back(t_scop *sc, int key, int action);

/*
**	utils functions.
*/

void								set_vec(t_vec3 *v, float x, float y, float z);
t_vec3								normalize(t_vec3 v);
float								norme(t_vec3 v);
t_vec3								vec_sub(t_vec3 v1, t_vec3 v2);
t_vec3								vec_cross(t_vec3 v1, t_vec3 v2);
float								vec_magnitude(t_vec3 v);
float								vec_dot_product(t_vec3 v1, t_vec3 v2);
t_color								create_color(float r, float g, float b, float a);
t_color								set_color(float r, float g, float b, float a);
float								set_gray_level(float color);

#endif