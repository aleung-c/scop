/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 15:16:36 by aleung-c          #+#    #+#             */
/*   Updated: 2016/09/28 15:16:38 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

int		advance_till_char(char *line, int position)
{
	int i;

	i = position;
	while (line[i] && isspace(line[i]) == 1)
		i++;
	return (i);
}

void	parse_line_counting(t_scop *sc, char *line) // TODO: a revoir. envisager strcmp;
{
	int i;

	i = 0;
	i = advance_till_char(line, 0);
	if (line[i] == '\0' || line[i] == '#')
	{
		return ;
	}
	else if (line[i] == 'v')
	{
		if (line[i + 1])
		{
			if (line[i + 1] == 't')
				sc->nb_texture_vertices += 1;
			else if (line[i + 1] == 'n')
				sc->nb_normals_vertices += 1;
			else if (line[i + 1] == 'p')
				sc->nb_parameter_space_vertices += 1;
			else
				sc->nb_vertices += 1;
		}
		else
		{
			sc->nb_vertices += 1;
		}
	}
	else if (line[i] == 'f')
	{
		sc->nb_faces += 1;
	}
	else if (line[i] == 'o')
	{
		sc->nb_obj += 1;
	}
	else if (line[i] == 'g')
	{
		sc->nb_groups += 1;
	}
	else if (ft_strncmp(&(line[i]), "usemtl", 5) == 0) 
	{
		sc->nb_materials += 1;
	}
	return ;
}

void	put_vertex_in_var(t_scop *sc, char *line, int position)
{
	int i;

	i = position;
	while (line[i] && sc->itmp < sc->nb_vertices)
	{
		while (line[i] && (isspace(line[i]) == 1))
			i++;
		if (isdigit(line[i]) == 1 || line[i] == '-')
		{
			sc->obj_vertices[sc->itmp] = strtof(&(line[i]), NULL);
			sc->itmp += 1;
			//printf("val =  %f \n", sc->obj_vertices[sc->itmp]);	
			while (isdigit(line[i]) || line[i] == '.' || line[i] == '-')
				i++;
		}
		else
			i++;
	}
}

void	put_faces_in_var(t_scop *sc, char *line, int position)
{
	int i;

	i = position;

	while (line[i] && sc->faces_itmp < sc->nb_faces)
	{
		while (line[i] && (isspace(line[i]) == 1))
			i++;
		if (isdigit(line[i]) == 1)
		{
			sc->obj_faces[sc->faces_itmp] = sc->obj_vertices[strtol(&(line[i]), NULL, 10) - 1];
			//printf("val =  %f \n", sc->obj_faces[sc->faces_itmp]);
			sc->faces_itmp += 1;
			sc->obj_faces[sc->faces_itmp] = sc->obj_vertices[strtol(&(line[i]), NULL, 10)];
			//printf("val =  %f \n", sc->obj_faces[sc->faces_itmp]);
			sc->faces_itmp += 1;
			sc->obj_faces[sc->faces_itmp] = sc->obj_vertices[strtol(&(line[i]), NULL, 10) + 1];
			//printf("val =  %f \n", sc->obj_faces[sc->faces_itmp]);
			sc->faces_itmp += 1;
			//sleep(2);
			while (isdigit(line[i]))
				i++;
		}
		else
			i++;
	}
	return ;
}

void	parse_line_filling(t_scop *sc, char *line)
{
	int i;

	i = 0;
	i = advance_till_char(line, 0);

	if (line[i] == '\0' || line[i] == '#')
	{
		return ;
	}
	else if (line[i] == 'v')
	{
		// fill vertex;
		if (line[i + 1])
		{
			if (line[i + 1] == 't')
				{}
			else if (line[i + 1] == 'n')
				{}
			else if (line[i + 1] == 'p')
				{}
			else
				put_vertex_in_var(sc, line, i);
		}
	}
	else if (line[i] == 'f')
	{
		put_faces_in_var(sc, line, i);
	}
}