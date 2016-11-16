/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/25 17:35:24 by aleung-c          #+#    #+#             */
/*   Updated: 2016/10/25 17:35:27 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

// lets cut the line into tokens.
void lex_obj_line(t_scop *sc, char *line, int line_number)
{
	char			*token_str;
	int				col_number;
	t_token			*cur_token;

	col_number = 0;
	token_str = strtok(line, " \t\n");
	while (token_str != NULL)
	{
		cur_token = (t_token *)malloc(sizeof(t_token));
		cur_token->line_number = line_number;
		cur_token->col_number = col_number;
		cur_token->value = (char *)malloc(sizeof(char) * strlen(token_str));
		cur_token->value = strcpy(cur_token->value, token_str);
		set_token_type(cur_token, token_str);
		add_token_to_list(sc, sc->obj_token_list, cur_token);

		token_str = strtok(NULL, " \t\n");
		col_number++;
	}
}

void set_token_type(t_token *cur_token, char *token_str)
{
	if (regex_match(token_str, "^[a-zA-Z]+$"))
	{
		//printf("match word\n");
		cur_token->token_type = word;
	}
	else if (regex_match(token_str, "^[a-zA-Z0-9_,\\r\\n\\t\\f\\v-]+\\.[A-Za-z]+$"))
	{
		cur_token->token_type = file_name;
	}
	else if (regex_match(token_str, "^[-]?[0-9]*\\.?[0-9]*$"))
	{
		//printf("match num val\n");
		cur_token->token_type = numeric_value;
	}
	else if (regex_match(token_str, "^[-]?[0-9]+\\/?[-]?[0-9]*\\/?[-]?[0-9]*$")
			&& token_str[strlen(token_str) - 1] != '/')
	{
		// ne peut pas voir / en dernier char.
		// pour les cas
		// 1//
		// 1/43/
		//printf("match indice\n");
		cur_token->token_type = indices;
	}
	else
	{
		//printf("no match - error token\n");
		cur_token->token_type = error;
	}
	// sleep(2);
}

// utility function: return 1 for match founds, 0 for no match founds
int			regex_match(char *string_to_search, char *regex_str)
{
	int				err;
	int				match;
	regex_t			regex;

	// compile regex
	err = regcomp(&regex, regex_str, REG_NOSUB | REG_EXTENDED);
	if (err)
	{
		printf("Could not compile regex.\n");
		exit(1);
	}
	else
	{
		/* Execute regular expression */
		match = regexec(&regex, string_to_search, 0, NULL, 0);
		if (match == 0)
		{
			regfree(&regex);
			return (1);
		}
		else if (match == REG_NOMATCH)
		{
			regfree(&regex);
			return (0);
		}
		else
		{
			fprintf(stderr, "Regex match failed.\n");
			regfree(&regex);
			exit(1);
		}
	}
	return (0);
}

void		add_token_to_list(t_scop *sc, t_token *obj_token_list, t_token *cur_token)
{
	cur_token->next = NULL;
	if (obj_token_list == NULL)
	{
		sc->obj_token_list = cur_token;
		return ;
	}
	else
	{
		sc->tmp = sc->obj_token_list;
		while (sc->tmp->next)
		{
			sc->tmp = sc->tmp->next;
		}
		sc->tmp->next = cur_token;
		return ;
	}
}