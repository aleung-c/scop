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
	// Open the file
	FILE	*file;

	file = fopen("resources/checker_texture.bmp","rb");
	if (!file)
	{
		printf("Image could not be opened\n");
		exit (-1);
	}
	if (fread(sc->default_texture.header, 1, 54, file) != 54)
	{ // If not 54 bytes read : problem
    	printf("Not a correct BMP file\n");
    	exit (-1);
	}
	sc->default_texture.data_pos = *(int*)&(sc->default_texture.header[0x0A]);
	sc->default_texture.image_size = *(int*)&(sc->default_texture.header[0x22]);
	sc->default_texture.width = *(int*)&(sc->default_texture.header[0x12]);
	sc->default_texture.height = *(int*)&(sc->default_texture.header[0x16]);

	printf("default_texture infos:\nimage_size: %d \nwidth: %d \nheight: %d\n",
		sc->default_texture.image_size, sc->default_texture.width, sc->default_texture.height);

	// Create a buffer
	sc->default_texture.data = (unsigned char *)malloc(sizeof(unsigned char) * sc->default_texture.image_size);

	// Read the actual data from the file into the buffer
	fread(sc->default_texture.data, 1, sc->default_texture.image_size, file);

	//Everything is in memory now, the file can be closed
	fclose(file);

    return ;
}
