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

	pos_in_indice = 0;
	sc->inline_token = token->next;
	while (sc->inline_token && sc->inline_token->line_number == token->line_number)
	{
		// for each indice x/x/x or x//x
		splitted_indice = strtok(sc->inline_token->value, "/");
	
		while (splitted_indice != NULL)
		{
			
			if (pos_in_indice == 0)
			{
				//printf("splitted_indice 1 = %s\n", splitted_indice);
				// get the indice 1
				sc->face_indices[sc->indices_itmp] = strtol(sc->inline_token->value, NULL, 10) - 1; // -1 cause indices start at 1...
				sc->indices_itmp += 1;
			}
			else if (pos_in_indice == 1)
			{
				//printf("splitted_indice 2 = %s\n", splitted_indice);
			}
			splitted_indice = strtok(NULL, "/");
			pos_in_indice++;
		}
		// moving to next indice;
		pos_in_indice = 0;
		sc->inline_token = sc->inline_token->next;
	}
}

void fill_face4(t_scop *sc, t_token *token)
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