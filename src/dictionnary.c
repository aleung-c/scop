/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionnary.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 15:14:56 by aleung-c          #+#    #+#             */
/*   Updated: 2016/11/07 15:14:58 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

void		init_dictionnaries(t_scop *sc)
{
	sc->word_dictionnary_list = NULL;
	add_word_to_dictionnary(sc, "v");
	add_word_to_dictionnary(sc, "vt");
	add_word_to_dictionnary(sc, "vn");
	add_word_to_dictionnary(sc, "f");
	add_word_to_dictionnary(sc, "o");
}

void		add_word_to_dictionnary(t_scop *sc, char *word)
{
	t_dictionnary_word	*new_word;
	t_dictionnary_word	*tmp;

	new_word = (t_dictionnary_word *)malloc(sizeof(t_dictionnary_word));
	new_word->string = (char *)malloc(sizeof(char) * strlen(word) + 1);
	new_word->string[strlen(word)] = '\0';
	new_word->string = strcpy(new_word->string, word);
	new_word->next = NULL;


	if (sc->word_dictionnary_list == NULL)
	{
		sc->word_dictionnary_list = new_word;
		return ;
	}
	else
	{
		tmp = sc->word_dictionnary_list;
		while (tmp->next)
		{
			tmp = tmp->next;
		}
		tmp->next = new_word;
	}
}

int		is_word_in_dictionnary(t_scop *sc, char *word)
{
	t_dictionnary_word	*tmp;
	
	if (sc->word_dictionnary_list == NULL)
	{
		printf("Error: dictionnary empty\n");
		exit (-1);
	}
	else
	{
		tmp = sc->word_dictionnary_list;
		while (tmp)
		{
			if (strcmp(tmp->string, word) == 0)
			{
				return (1); // word is in dico
			}
			tmp = tmp->next;
		}
	}
	return (0); // word is NOT in dico.
}