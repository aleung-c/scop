/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 18:12:34 by aleung-c          #+#    #+#             */
/*   Updated: 2016/11/25 18:12:36 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

void			print_parser_error(t_token *token, char *error_string)
{
	printf(KRED "Parse Error: line %d column %d : %s : %s\n" KRESET,
		token->line_number, token->col_number, error_string, token->value);
}

void			print_tokens(t_scop *sc)
{
	t_token		*tmp;
	int			i;

	i = 0;
	tmp = sc->obj_token_list;
	while (tmp)
	{
		printf("token %d\nvalue = %s\nline nb = %d\ncol nb = %d\n",
				i,
				tmp->value,
				tmp->line_number,
				tmp->col_number);
		if (tmp->token_type == word)
			printf("token type = word\n");
		else if (tmp->token_type == numeric_value)
			printf("token type = numeric_value\n");
		else if (tmp->token_type == indices)
			printf("token type = indices\n");
		ft_putchar('\n');
		tmp = tmp->next;
		i++;
	}
}
