/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 16:25:41 by aleung-c          #+#    #+#             */
/*   Updated: 2016/11/09 16:25:43 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

char		*get_file_content(char *file_path)
{
	FILE *fp;
	long lsize;
	char *buffer;

	fp = fopen(file_path, "rb" );
	if (!fp)
	{
		printf("Error opening file\n");
		exit(-1);
	}

	fseek(fp, 0L, SEEK_END);
	lsize = ftell(fp);
	rewind(fp);

	buffer = (char *)malloc(sizeof(char) * lsize);
	if (!buffer)
	{
		printf("Error allocating vertex shader memory\n");
		exit(-1);
	}

	if (fread(buffer, lsize, 1, fp) != 1)
	{
		fclose(fp);
		free(buffer);
		printf("entire read fails\n");
		exit(1);
	}
	buffer[lsize] = '\0';
	fclose(fp);
	return (buffer);
}
