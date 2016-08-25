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

SRC = src/scop.c

OBJ = $(SRC:.c=.o)

LIB = ./libft/

MLX = -lmlx -I/Library/Frameworks/OpenGL.framework/Headers -framework OpenGL -I/Library/Frameworks/SDL2.framework/Headers -framework SDL2 -framework AppKit

CC = gcc -g -Wall -Werror -Wextra -Ofast 

all : Lib $(NAME) 

$(NAME) : $(OBJ)
	$(CC) -o $(NAME) $(OBJ) -L./libft/ -lft $(MLX)

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