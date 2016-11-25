/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 12:05:19 by aleung-c          #+#    #+#             */
/*   Updated: 2016/09/28 12:05:24 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

int get_obj(t_scop *sc, char *arg)
{
	FILE			*fp;
	char			*buf;
	size_t			buf_size;
	int				line_number;
	char			*pch;

	if ((fp = fopen(arg, "r")) == NULL)
	{
		ft_putendl("File opening error");
		return (-1);
	}
	else
	{
		sc->fp = fp;
		buf = NULL;
		buf_size = 0;
		line_number = 0;
		sc->obj_token_list = NULL;
		while ((getline(&buf, &buf_size, fp)) > 0)
		{
			// comment check;
			pch = strchr(buf,'#');
			if (pch)
			{
				buf[pch - buf] = '\0'; // delete everything after #
			}
			lex_obj_line(sc, buf, line_number); // create token list
			free(buf);
			buf = NULL;
			line_number++;
		}
		free(buf);
		// sc->file_str = ret_str;
		fclose(fp);
		//  Print file content;
		// printf("%s \n", sc->file_str);
		// sleep(10);
		return (0);
	}
	return (0);
}
