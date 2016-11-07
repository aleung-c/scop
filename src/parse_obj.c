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

void						parse_obj(t_scop *sc)
{
	if (check_tokens(sc) == -1)
	{
		printf("Error in tokens\n");
		exit(-1);
	}
	// PRE STEP: change all f numeric_value to indices.
	change_token_indice_type(sc);
	
	// STEP 1: check token order.
	check_token_order(sc);
	// STEP 2: check if tokens are in dictionnary.
	dictionnary_comparison(sc);
	// STEP 3: check particular cases. (optional);
	// STEP 4: check if token values are correct (optional);

	//print_tokens(sc);

	return ;
}

void						print_tokens(t_scop *sc)
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
		{
			printf("token type = word\n");
		}
		else if (tmp->token_type == numeric_value)
		{
			printf("token type = numeric_value\n");
		}
		else if (tmp->token_type == indices)
		{
			printf("token type = indices\n");
		}
		ft_putchar('\n');
		// sleep(1);
		tmp = tmp->next;
		i++;
	}
}

int			check_tokens(t_scop *sc)
{
	t_token		*tmp; // run through token list.
	int			i;

	i = 0;
	tmp = sc->obj_token_list;
	while (tmp)
	{
		if (tmp->token_type == error)
		{
			return (-1);
		}
		tmp = tmp->next;
	}
	return (0);	
}

/*
**	STEP 1: Line by line check of token orders.
*/
void		check_token_order(t_scop *sc)
{
	t_token		*tmp;
	int			cur_line;

	cur_line = 0;
	tmp = sc->obj_token_list;
	while (tmp)
	{
		// token in position 0 -> first token of line
		if (tmp->col_number == 0)
		{
			// cant have value in pos zero;
			if (tmp->token_type != word)
			{
				print_parser_error(tmp, "First value of line must be a word");
			}
			if (tmp->next == NULL || tmp->next->line_number != tmp->line_number)
			{
				print_parser_error(tmp, "Solo word on a line");
			}
		}
		tmp = tmp->next;
	}
}

/*
**	STEP 2: Check if token is in dictionnary;
*/
void		dictionnary_comparison(t_scop *sc)
{
	t_token		*tmp;
	int			cur_line;

	cur_line = 0;
	tmp = sc->obj_token_list;
	while (tmp)
	{
		if (tmp->token_type == word)
		{
			if (!is_word_in_dictionnary(sc, tmp->value))
			{
				print_parser_error(tmp, "Unknown word");
			}
		}
		tmp = tmp->next;
	}
}

void		print_parser_error(t_token *token, char *error_string)
{
	printf("Parse Error: line %d column %d : %s : %s\n",
		token->line_number, token->col_number, error_string, token->value);
}

void	change_token_indice_type(t_scop *sc)
{
	t_token		*tmp;
	int			cur_line;

	cur_line = 0;
	tmp = sc->obj_token_list;
	while (tmp)
	{
		if (strcmp(tmp->value, "f") == 0)
		{
			//printf("found f \n");
			cur_line = tmp->line_number;
			tmp = tmp->next;
			while (tmp && tmp->line_number == cur_line)
			{
				// pour chaque token sur une ligne.
				tmp->token_type = indices;
				tmp = tmp->next;
			}
		}
		else
		{
			tmp = tmp->next;
		}
	}
}

void	put_vertex_in_var(t_scop *sc, char *line, int position)
{
	int		i;
	char	*tmp;

	i = position;
	tmp = line;
	/*while (line[i] && sc->itmp < sc->nb_vertices)
	{
		while (line[i] && (isspace(line[i]) == 1) && line[i] != '\n')
			i++;
		if (isdigit(line[i]) == 1 || line[i] == '-')
		{
			sc->obj_vertices[sc->itmp] = strtof(&(line[i]), NULL);
			printf("val =  %f \n", sc->obj_vertices[sc->itmp]);	
			sc->itmp += 1;
			while (isdigit(line[i]) || line[i] == '.' || line[i] == '-')
				i++;
		}
		else
			i++;
	}*/

	while (*tmp && sc->itmp < (sc->nb_vertices * 3))
	{
		while (*tmp && (isspace(*tmp) == 1))
			tmp++;
		if (*tmp && ((isdigit(*tmp) == 1) || *tmp == '-'))
		{
			sc->obj_vertices[sc->itmp] = strtof(&(*tmp), &tmp);
			//printf("val =  %f\n", sc->obj_vertices[sc->itmp]);
			sc->itmp += 1;
		}
		else
			tmp++;
	}
}

void	put_faces_in_var(t_scop *sc, char *line, int position)
{
	int i;
	int total_floats;
	char *tmp;

	i = position;
	total_floats = (sc->nb_faces_3 * 3) * 3;
	tmp = line;

	while (*tmp && sc->faces_itmp < total_floats)
	{
		while (*tmp && (isspace(*tmp) == 1))
			tmp++;
		if (*tmp && (isdigit(*tmp) == 1))
		{
			sc->obj_faces_3[sc->faces_itmp] = sc->obj_vertices[((strtol(&(*tmp), NULL, 10)) * 3)];
			sc->faces_itmp += 1;
			sc->obj_faces_3[sc->faces_itmp] = sc->obj_vertices[((strtol(&(*tmp), NULL, 10)) * 3) + 1];
			sc->faces_itmp += 1;
			sc->obj_faces_3[sc->faces_itmp] = sc->obj_vertices[((strtol(&(*tmp), &tmp, 10)) * 3) + 2];
			sc->faces_itmp += 1;
			//sc->obj_vertices[sc->itmp] = strtof(&(*tmp), &tmp);
			//printf("val =  %f\n", sc->obj_vertices[sc->itmp]);
			
		}
		else
			tmp++;
	}


}

void	parse_line_filling(t_scop *sc, char *line)
{
	int i;

	i = 0;
	//i = advance_till_char(line, 0);

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