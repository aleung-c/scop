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

int			get_obj(t_scop *sc, char *arg)
{
	FILE			*fp;

	if ((fp = fopen(arg, "r")) == NULL || is_directory(arg))
	{
		ft_putendl("File opening error");
		return (-1);
	}
	else
	{
		process_opened_file(sc, fp);
		return (0);
	}
	return (0);
}

void		process_opened_file(t_scop *sc, FILE *fp)
{
	char			*buf;
	char			*pch;
	size_t			buf_size;
	int				line_number;

	sc->fp = fp;
	buf = NULL;
	buf_size = 0;
	line_number = 0;
	sc->obj_token_list = NULL;
	while ((getline(&buf, &buf_size, fp)) > 0)
	{
		pch = strchr(buf, '#');
		if (pch)
			buf[pch - buf] = '\0';
		lex_obj_line(sc, buf, line_number);
		free(buf);
		buf = NULL;
		line_number++;
	}
	free(buf);
	fclose(fp);
}

int			is_directory(const char *path)
{
	struct stat statbuf;

	if (stat(path, &statbuf) != 0)
		return 0;
	return S_ISDIR(statbuf.st_mode);
}
