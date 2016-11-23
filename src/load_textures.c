/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 17:51:46 by aleung-c          #+#    #+#             */
/*   Updated: 2016/11/11 17:51:48 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

void		load_textures(t_scop *sc)
{
	sc->default_texture = load_texture_file(&(sc->default_texture), "resources/default_texture.bmp");
	sc->second_texture = load_texture_file(&(sc->second_texture), "resources/cat_texture.bmp");
    return ;
}

t_bmp_texture	load_texture_file(t_bmp_texture *texture, char *path)
{
	// Open the file
	FILE	*file;

	file = fopen(path,"rb");
	if (!file)
	{
		printf("Image could not be opened\n");
		exit (-1);
	}
	if (fread(texture->header, 1, 54, file) != 54)
	{ // If not 54 bytes read : problem
    	printf("Not a correct BMP file\n");
    	exit (-1);
	}
	texture->data_pos = *(int*)&(texture->header[10]);
	texture->image_size = *(int*)&(texture->header[34]);
	texture->width = *(int*)&(texture->header[18]);
	texture->height = *(int*)&(texture->header[22]);

	if ( texture->header[0] != 'B' || texture->header[1] != 'M' )
	{
		printf("Not a correct BMP file\n");
		exit (-1);
	}

	printf("default_texture infos:\nimage_size: %d \nwidth: %d \nheight: %d\n",
		texture->image_size, texture->width, texture->height);

	// Create a buffer
	texture->data = (unsigned char *)malloc(sizeof(unsigned char) * texture->image_size);

	// Read the actual data from the file into the buffer
	fread(texture->data, 1, texture->image_size, file);

	//Everything is in memory now, the file can be closed
	fclose(file);
	return (*texture);
}
