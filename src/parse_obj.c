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

void			parse_obj(t_scop *sc)
{
	if (check_tokens(sc) == -1)
	{
		printf("Error in tokens\n");
		exit(-1);
	}
	change_token_indice_type(sc);
	check_token_order(sc);
	dictionnary_comparison(sc);
	return ;
}

int				check_tokens(t_scop *sc)
{
	int			i;

	i = 0;
	sc->tmp = sc->obj_token_list;
	while (sc->tmp)
	{
		if (sc->tmp->token_type == error)
		{
			printf("token error:\nvalue = %s\nline nb = %d\ncol nb = %d\n",
				sc->tmp->value,
				sc->tmp->line_number,
				sc->tmp->col_number);
			return (-1);
		}
		sc->tmp = sc->tmp->next;
	}
	return (0);
}

/*
**	STEP 1: Line by line check of token orders.
*/

void			check_token_order(t_scop *sc)
{
	t_token		*tmp;
	int			cur_line;

	cur_line = 0;
	tmp = sc->obj_token_list;
	while (tmp)
	{
		if (tmp->col_number == 0)
		{
			if (tmp->token_type != word)
			{
				print_parser_error(tmp, "First value of line must be a word");
			}
		}
		tmp = tmp->next;
	}
}

/*
**	STEP 2: Check if token is in dictionnary;
*/

void			dictionnary_comparison(t_scop *sc)
{
	t_token		*tmp;
	int			cur_line;

	cur_line = 0;
	tmp = sc->obj_token_list;
	while (tmp)
	{
		if (tmp->token_type == word && tmp->line_number == 0)
		{
			if (!is_word_in_dictionnary(sc, tmp->value))
			{
				print_parser_error(tmp, "Unknown word one line start");
			}
		}
		tmp = tmp->next;
	}
}

void			change_token_indice_type(t_scop *sc)
{
	int			cur_line;

	cur_line = 0;
	sc->tmp = sc->obj_token_list;
	while (sc->tmp)
	{
		if (strcmp(sc->tmp->value, "f") == 0)
		{
			cur_line = sc->tmp->line_number;
			sc->tmp = sc->tmp->next;
			while (sc->tmp && sc->tmp->line_number == cur_line)
			{
				sc->tmp->token_type = indices;
				sc->tmp = sc->tmp->next;
			}
		}
		else
		{
			sc->tmp = sc->tmp->next;
		}
	}
}
