# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/08/25 14:45:31 by aleung-c          #+#    #+#              #
#    Updated: 2016/08/25 14:45:34 by aleung-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = scop

HEADER = includes/scop.h

SRC = src/scop.c \
src/data_init.c \
src/get_obj.c \
src/count_values.c \
src/parse_obj.c \
src/lex_obj.c \
src/dictionnary.c \
src/get_values.c \
src/matrix_identity.c \
src/matrix_translation.c \
src/matrix_scaling.c \
src/matrix_rotation.c \
src/matrix_view.c \
src/matrix_projection.c \
src/shader_handling.c \
src/vector_utils.c \
src/load_textures.c \
src/color.c \
src/fill_values.c \
src/set_colors.c \
src/opengl_set_buffers.c \
src/opengl_set_matrices.c \
src/opengl_load_shaders.c \
src/opengl_load_textures.c \
src/opengl_drawing.c \
src/events.c \
src/generate_uvs.c \
src/generate_transition_points.c \
src/allocate_variables.c


OBJ = $(SRC:.c=.o)

LIB = ./libft/

GL = -framework OpenGL
GLFW = -framework Cocoa -framework CoreVideo -framework IOKit -framework GLUT -L./glfw-3.2.1/src -lglfw3

SDL2 = -framework OpenGL -I/Library/Frameworks/SDL2.framework/Headers -framework SDL2 -framework AppKit

CC = gcc -g -O2 -Wall -Werror -Wextra
#-march=native


all : Lib $(NAME) 

$(NAME) : $(OBJ)
	$(CC) -o $(NAME) $(OBJ) -L./libft/ -lft $(GL) $(GLFW)

Lib :
	make -C $(LIB)

clean :
	rm -rf $(OBJ)
	cd $(LIB) ; make clean

fclean : clean
	rm -rf $(NAME)
	cd $(LIB) ; make fclean

re : fclean all

.PHONY : all clean fclean re