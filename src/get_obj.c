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
	FILE			*fp;
	char			*buf;
	size_t			buf_size;
	int				line_number;

	if ((fp = fopen(arg, "r")) == NULL)
	{
		ft_putendl("File opening error");
		return (-1);
	}
	else
	{
		sc->fp = fp;
		buf = NULL;
		buf_size = 0;
		line_number = 0;
		// ret_str = (char *)malloc(sizeof(char) * 1);
		// ret_str[0] = '\0';
		// ret_str_size = 1;
		sc->obj_token_list = NULL;
		while ((getline(&buf, &buf_size, fp)) > 0)
		{
			lex_obj_line(sc, buf, line_number);
			// ret_str_size += getline_ret;
			// ret_str = (char *)realloc(ret_str, ret_str_size + 1);
			// ft_strncat(ret_str, buf, strlen(buf));
			// ret_str[ret_str_size] = '\n';
			free(buf);
			buf = NULL;
			line_number++;
		}
		// sc->file_str = ret_str;
		fclose(fp);
		//  Print file content;
		// printf("%s \n", sc->file_str);
		// sleep(10);
		return (0);
	}
	return (0);
}

/*
**	Pass 1's objective is to get number of vertices, textures vertices, faces, etc... for allocation purpose;
*/
void		parse_pass1(t_scop *sc, FILE *fp)
{
	/*int							fd2;
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
			ft_putstr(line);
			parse_line_counting(sc, line);
			free(line); // clean
			line_number += 1;
			char_count = 0;
			//sleep(1);
		}
	}*/

	int			ret;
	char		buffer[40];
	char		*line;
	int			buff_size;
	int 		line_number;

	buff_size = 100;
	line_number = 0;
	while (!feof(fp))
	{
		line = (char *)malloc(sizeof(char) * buff_size);
		fgets(line, buff_size, fp);
		parse_line_counting(sc, line);
		line_number += 1;
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

void		allocate_variables(t_scop *sc)
{
	if (!(sc->obj_vertices = (float *)malloc(sizeof(float) * sc->nb_vertices * 3)))
	{
		ft_putendl("vertices allocation failed.");
		exit (-1);
	}
	if (!(sc->obj_faces = (float *)malloc(sizeof(float) * (sc->nb_faces * 3) * 3)))
	{
		ft_putendl("face vertices allocation failed.");
		exit (-1);
	}
	ft_putendl("- All model variables allocated.");
}

/*
**	Pass 2 takes the values and put them in variables.
*/
void		parse_pass2(t_scop *sc, FILE *fp)
{
	char						*line2;
	int							buff_size;

	fseek(fp, 0, SEEK_SET);
	buff_size = 100;
	while (!feof(fp))
	{
		line2 = (char *)malloc(sizeof(char) * buff_size);
		fgets(line2, buff_size, fp);
		parse_line_filling(sc, line2);
	}
	//ft_putchar('\n');
}
