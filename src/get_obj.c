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

char *get_nchar(int *fd2, int char_count)
{
	int			ret;
	char		*buffer;

	buffer = (char *)malloc(sizeof(char) * char_count);
	buffer[char_count] = '\0';
	ret = read(*fd2, buffer, char_count);
	return (buffer);

}

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
		// sc->file_str = ret_str;
		fclose(fp);
		//  Print file content;
		// printf("%s \n", sc->file_str);
		// sleep(10);
		return (0);
	}
	return (0);
}

/*
**	Pass 1's objective is to get number of vertices, textures vertices, faces, etc... for allocation purpose;
*/
void		parse_pass1(t_scop *sc, FILE *fp)
{
	/*int							fd2;
	int							ret;
	int							line_number;
	char						*line;
	char						cur_char;
	int							char_count;

	line_number = 0;
	fd2 = open(arg, O_RDONLY);
	char_count = 0;
	cur_char = 'a';
	ret = 1;

	while ((ret = read(fd, &cur_char, 1)))
	{
		if (cur_char != '\n' && cur_char != '\0' && cur_char != EOF)
		{
			char_count += 1;
		}
		if (cur_char == '\0' || cur_char == EOF || ret == 0)
			break;
		if (cur_char == '\n')
		{
			line = get_nchar(&fd2, char_count + 1);
			ft_putstr(line);
			parse_line_counting(sc, line);
			free(line); // clean
			line_number += 1;
			char_count = 0;
			//sleep(1);
		}
	}*/

	int			ret;
	char		buffer[40];
	char		*line;
	int			buff_size;
	int 		line_number;

	buff_size = 100;
	line_number = 0;
	while (!feof(fp))
	{
		line = (char *)malloc(sizeof(char) * buff_size);
		fgets(line, buff_size, fp);
		//parse_line_counting(sc, line);
		line_number += 1;
	}

	
}


/*
**	Pass 2 takes the values and put them in variables.
*/
void		parse_pass2(t_scop *sc, FILE *fp)
{
	char						*line2;
	int							buff_size;

	fseek(fp, 0, SEEK_SET);
	buff_size = 100;
	while (!feof(fp))
	{
		line2 = (char *)malloc(sizeof(char) * buff_size);
		fgets(line2, buff_size, fp);
		parse_line_filling(sc, line2);
	}
	//ft_putchar('\n');
}
