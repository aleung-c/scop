/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 12:05:19 by aleung-c          #+#    #+#             */
/*   Updated: 2016/09/28 12:05:24 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

char *get_nchar(int *fd2, int char_count)
{
	int			ret;
	char		*buffer;

	buffer = (char *)malloc(sizeof(char) * char_count);
	buffer[char_count] = '\0';
	ret = read(*fd2, buffer, char_count);
	return (buffer);

}

int get_obj(t_scop *sc, char *arg)
{
	int							fd;

	if ((fd = open(arg, O_RDONLY)) == -1)
	{
		ft_putendl("File opening error");
		return (-1);
	}
	else
	{
		data_init(sc);
		parse_pass1(sc, fd, arg);
		allocate_variables(sc);
		parse_pass2(sc, fd, arg);
	}
	return (0);
}

void		data_init(t_scop *sc)
{
	sc->nb_vertices = 0;
	sc->nb_texture_vertices = 0;
	sc->nb_normals_vertices = 0;
	sc->nb_parameter_space_vertices = 0;
	sc->nb_faces = 0;
	sc->nb_obj = 0;
	sc->nb_groups = 0;
	sc->nb_materials = 0;
}

/*
**	Pass 1's objective is to get number of vertices, textures vertices, faces, etc... for allocation purpose;
*/
void		parse_pass1(t_scop *sc, int fd, char *arg)
{
	int							fd2;
	int							ret;
	int							line_number;
	char						*line;
	char						cur_char;
	int							char_count;

	line_number = 0;
	fd2 = open(arg, O_RDONLY);
	char_count = 0;
	cur_char = 'a';
	ret = 1;
	while ((ret = read(fd, &cur_char, 1)))
	{
		if (cur_char != '\n' && cur_char != '\0' && cur_char != EOF)
		{
			char_count += 1;
		}
		if (cur_char == '\0' || cur_char == EOF || ret == 0)
			break;
		if (cur_char == '\n')
		{
			line = get_nchar(&fd2, char_count + 1);
			//ft_putstr(line);
			parse_line_couting(sc, line);
			free(line); // clean
			line_number += 1;
			char_count = 0;
		}
	}
	ft_putstr(KGRN "Object file datas:" KRESET);
	ft_putchar('\n');
	ft_putstr("total nb of line = ");
	ft_putnbr(line_number);
	ft_putchar('\n');

	ft_putstr("Nb of vertices = ");
	ft_putnbr(sc->nb_vertices);
	ft_putchar('\n');
	ft_putstr("Nb of tex vertices = ");
	ft_putnbr(sc->nb_texture_vertices);
	ft_putchar('\n');
	ft_putstr("Nb of normals vertices = ");
	ft_putnbr(sc->nb_normals_vertices);
	ft_putchar('\n');
	ft_putstr("Nb of parameter space vertices = ");
	ft_putnbr(sc->nb_parameter_space_vertices);
	ft_putchar('\n');
	ft_putstr("Nb of faces = ");
	ft_putnbr(sc->nb_faces);
	ft_putchar('\n');
	ft_putstr("Nb of obj = ");
	ft_putnbr(sc->nb_obj);
	ft_putchar('\n');
	ft_putstr("Nb of groups = ");
	ft_putnbr(sc->nb_groups);
	ft_putchar('\n');
	ft_putstr("Nb of materials = ");
	ft_putnbr(sc->nb_materials);
	ft_putchar('\n');
	ft_putchar('\n');
}

void	allocate_variables(t_scop *sc)
{
	sc->obj_vertices = (float *)malloc(sizeof(float) * sc->nb_vertices);
}

/*
**	Pass 2 takes the values and put them in variables.
*/
void		parse_pass2(t_scop *sc, int fd, char *arg)
{
	int							fd2;
	int							ret;
	int							line_number;
	char						*line;
	char						cur_char;
	int							char_count;

	fd2 = open(arg, O_RDONLY);
	char_count = 0;
	cur_char = 'a';
	ret = 1;
	while ((ret = read(fd, &cur_char, 1)))
	{
		if (cur_char != '\n' && cur_char != '\0' && cur_char != EOF)
		{
			char_count += 1;
		}
		if (cur_char == '\0' || cur_char == EOF || ret == 0)
			break;
		if (cur_char == '\n')
		{
			line = get_nchar(&fd2, char_count + 1);
			//ft_putstr(line);
			parse_line_filling(sc, line); // actual obj format line parsing;
			free(line); // clean
			line_number += 1;
			char_count = 0;
		}
	}
	//ft_putchar('\n');
}
