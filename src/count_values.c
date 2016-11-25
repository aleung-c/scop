/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_values.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 14:08:31 by aleung-c          #+#    #+#             */
/*   Updated: 2016/11/24 14:08:33 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

void	count_values(t_scop *sc)
{
	t_token		*token;

	token = sc->obj_token_list;
	while (token)
	{
		if (token->col_number == 0)
		{
			if (!strcmp(token->value, "v"))
				sc->nb_vertices++;
			else if (!strcmp(token->value, "vt"))
				sc->nb_texture_vertices++;
			else if (!strcmp(token->value, "vn"))
				sc->nb_normals_vertices++;
			else if (!strcmp(token->value, "vp"))
				sc->nb_parameter_space_vertices++;
			else if (strcmp(token->value, "f") == 0)
			{
				count_face_values(sc, token);
			}
		}
		token = token->next;
	}
	print_obj_value_numbers(sc);
}

void	count_face_values(t_scop *sc, t_token *token)
{
	int			inline_i;

	inline_i = 0;
	sc->inline_token = token->next;
	while (sc->inline_token && sc->inline_token->line_number
		== token->line_number)
	{
		inline_i++;
		sc->inline_token = sc->inline_token->next;
	}
	if (inline_i == 3)
		sc->nb_faces_3++;
	else if (inline_i == 4)
		sc->nb_faces_4++;
	else if (inline_i > 4)
	{
		sc->nb_faces_more += 1;
		sc->nb_indices_more += inline_i;
	}
}

void	print_obj_value_numbers(t_scop *sc)
{
	ft_putstr(KGRN "Object file datas:" KRESET);
	ft_putchar('\n');
	printf("Nb of v  = %lu\n", sc->nb_vertices);
	printf("Nb of vt = %lu\n", sc->nb_texture_vertices);
	printf("Nb of vn = %lu\n", sc->nb_normals_vertices);
	printf("Nb of vp = %lu\n", sc->nb_parameter_space_vertices);
	printf("Nb of faces 3 = %lu\n", sc->nb_faces_3);
	printf("Nb of faces 4 = %lu\n", sc->nb_faces_4);
	printf("Nb of faces more = %lu\n", sc->nb_faces_more);
	printf("Nb of added indices = %lu\n", sc->nb_indices_more);
	printf("Nb of obj = %lu\n", sc->nb_obj);
	printf("Nb of groups = %lu\n", sc->nb_groups);
	printf("Nb of materials = %lu\n", sc->nb_materials);
	ft_putchar('\n');
}
