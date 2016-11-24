/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 14:13:34 by aleung-c          #+#    #+#             */
/*   Updated: 2016/11/24 14:14:28 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

void		data_init(t_scop *sc)
{
	// obj value counters.
	sc->nb_vertices = 0;
	sc->nb_texture_vertices = 0;
	sc->nb_normals_vertices = 0;
	sc->nb_parameter_space_vertices = 0;
	sc->nb_faces_3 = 0;
	sc->nb_faces_4 = 0;
	sc->nb_faces_more = 0;
	sc->nb_indices_more = 0;
	sc->nb_obj = 0;
	sc->nb_groups = 0;
	sc->nb_materials = 0;

	// counters
	sc->itmp = 0;
	sc->faces_vertices_itmp = 0;
	sc->indices_itmp = 0;
	sc->normals_itmp = 0;
	sc->face_normals_itmp = 0;
	sc->faces_uv_itmp = 0;
	sc->vcolor_itmp = 0;
	sc->tpoints_i = 0;

	// matrices.
	init_translation_matrix(sc);
	init_scaling_matrix(sc);
	init_identity_matrix(sc);
	init_x_rotation_matrix(sc);
	init_y_rotation_matrix(sc);
	init_z_rotation_matrix(sc);

	// scene settings
	sc->zoom_level = 0.2;
	sc->camera_pos.x = 0.0;
	sc->camera_pos.y = 0.0;
	sc->camera_pos.z = 0.0;
	sc->camera_lookat.x = 0.0;
	sc->camera_lookat.y = 0.0;
	sc->camera_lookat.z = 1.0;
	init_view_orientation_matrix(sc);
	init_view_translation_matrix(sc);
	sc->camera_near = 0.1;
	sc->camera_far = 100.0;
	sc->camera_fov = 60.0;
	sc->camera_aspect = 1.33; // 4/3, 16/9, etc 1 = 4/4
	init_perspective_projection_matrix(sc);
	set_vec(&sc->bounding_box_center, 0.0, 0.0, 0.0);
	set_vec(&sc->bounding_box_max, 0.0, 0.0, 0.0);
	set_vec(&sc->bounding_box_min, 0.0, 0.0, 0.0);
	set_vec(&sc->light_pos, 2.0, 0.0, 0.0);
}
