/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_values.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 17:25:29 by aleung-c          #+#    #+#             */
/*   Updated: 2016/11/16 17:25:31 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

void fill_face3(t_scop *sc, t_token *token)
{
	char			*splitted_indice;
	int				pos_in_indice;
	char			*t_val_cpy;
	char			*free_tmp;

	pos_in_indice = 0;
	sc->inline_token = token->next;

	
	
	//printf("str =  %s\n", sc->inline_token->value);
	while (sc->inline_token && sc->inline_token->line_number == token->line_number)
	{
		// for each indice x/x/x or x//x
		// get copy of the string;
		t_val_cpy = malloc(sizeof(char) * strlen(sc->inline_token->value));
		t_val_cpy = strcpy(t_val_cpy, sc->inline_token->value);

		splitted_indice = strtok(t_val_cpy, "/");

		while (splitted_indice != NULL)
		{
			//printf("splited indice = %s\n", splitted_indice);
			if (pos_in_indice == 0)
			{
				//printf("splitted_indice = %s\n", splitted_indice);
				// get the indice 1
				sc->face_indices[sc->indices_itmp] = strtol(splitted_indice, NULL, 10) - 1; // -1 cause indices start at 1...
				sc->indices_itmp += 1;
			}
			else if (pos_in_indice == 1 && regex_match(sc->inline_token->value, "^[-]?[0-9]+\\/\\/[-]?[0-9]*$"))
			{
				add_face_normal_from_indice(sc, splitted_indice);
				//printf("added normal face\n");
			}
			else if (pos_in_indice == 2)
			{
				add_face_normal_from_indice(sc, splitted_indice);
			}
			else // pos = 1, regularly filled indice.
			{
				add_face_uv_from_indice(sc, splitted_indice);
			}
			splitted_indice = strtok(NULL, "/");
			pos_in_indice++;
		}
		// moving to next indice;
		pos_in_indice = 0;
		sc->inline_token = sc->inline_token->next;
		//printf("\n");
	}
	//printf("\n");
}

void	fill_face4(t_scop *sc, t_token *token)
{
	sc->inline_token = token->next;
	// first triangle
	sc->face_indices[sc->indices_itmp] = strtol(sc->inline_token->value, NULL, 10) - 1; // [0]
	sc->indices_itmp++;
	sc->face_indices[sc->indices_itmp] = strtol(sc->inline_token->next->value, NULL, 10) - 1; // [1]
	sc->indices_itmp++;
	sc->face_indices[sc->indices_itmp] = strtol(sc->inline_token->next->next->value, NULL, 10) - 1; // [2]
	sc->indices_itmp++;

	// second triangle
	sc->face_indices[sc->indices_itmp] = strtol(sc->inline_token->next->next->next->value, NULL, 10) - 1; // [3]
	sc->indices_itmp++;
	sc->face_indices[sc->indices_itmp] = strtol(sc->inline_token->next->next->value, NULL, 10) - 1; // [2]
	sc->indices_itmp++;
	sc->face_indices[sc->indices_itmp] = strtol(sc->inline_token->value, NULL, 10) - 1; // [0]
	sc->indices_itmp++;
}

void	add_face_normal_from_indice(t_scop *sc, char *splitted_indice)
{
	int				indice_val;

	// get vn
	indice_val = strtol(splitted_indice, NULL, 10) - 1;
	//printf("indice_val = %d\n", indice_val);
	// the same for every vertex of the face.
	sc->faces_normals[sc->face_normals_itmp] = sc->obj_normals[indice_val * 3];
	sc->face_normals_itmp++;
	sc->faces_normals[sc->face_normals_itmp] = sc->obj_normals[indice_val * 3 + 1];
	sc->face_normals_itmp++;
	sc->faces_normals[sc->face_normals_itmp] = sc->obj_normals[indice_val * 3 + 2];
	sc->face_normals_itmp++;

	sc->faces_normals[sc->face_normals_itmp] = sc->obj_normals[indice_val * 3];
	sc->face_normals_itmp++;
	sc->faces_normals[sc->face_normals_itmp] = sc->obj_normals[indice_val * 3 + 1];
	sc->face_normals_itmp++;
	sc->faces_normals[sc->face_normals_itmp] = sc->obj_normals[indice_val * 3 + 2];
	sc->face_normals_itmp++;

	sc->faces_normals[sc->face_normals_itmp] = sc->obj_normals[indice_val * 3];
	sc->face_normals_itmp++;
	sc->faces_normals[sc->face_normals_itmp] = sc->obj_normals[indice_val * 3 + 1];
	sc->face_normals_itmp++;
	sc->faces_normals[sc->face_normals_itmp] = sc->obj_normals[indice_val * 3 + 2];
	sc->face_normals_itmp++;
}

void add_face_uv_from_indice(t_scop *sc, char *splitted_indice)
{
	int				indice_val;

	// get uv = vt;
	indice_val = strtol(splitted_indice, NULL, 10) - 1;
	
	sc->faces_uv[sc->faces_uv_itmp] = sc->obj_tex_coords[indice_val * 2];
	sc->faces_uv_itmp++;
	sc->faces_uv[sc->faces_uv_itmp] = sc->obj_tex_coords[indice_val * 2 + 1];
	sc->faces_uv_itmp++;

	sc->faces_uv[sc->faces_uv_itmp] = sc->obj_tex_coords[indice_val * 2];
	sc->faces_uv_itmp++;
	sc->faces_uv[sc->faces_uv_itmp] = sc->obj_tex_coords[indice_val * 2 + 1];
	sc->faces_uv_itmp++;

	sc->faces_uv[sc->faces_uv_itmp] = sc->obj_tex_coords[indice_val * 2];
	sc->faces_uv_itmp++;
	sc->faces_uv[sc->faces_uv_itmp] = sc->obj_tex_coords[indice_val * 2 + 1];
	sc->faces_uv_itmp++;
}
