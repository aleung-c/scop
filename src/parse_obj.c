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
	while ((line[i] == ' ' || line[i] == '\t'))
		i++;
	return (i);
}

void	parse_line_couting(t_scop *sc, char *line)
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
	else if (ft_strncmp(&(line[i]), "usemtl", 5) == 0) // TODO: a revoir.
	{
		sc->nb_materials += 1;
	}
	return ;
}

void	parse_line_filling(t_scop *sc, char *line)
{


}