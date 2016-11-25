/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 18:37:15 by aleung-c          #+#    #+#             */
/*   Updated: 2016/11/25 18:37:17 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

float		vec_magnitude(t_vec3 v)
{
	float			ret;

	ret = sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
	return (ret);
}

float		vec_dot_product(t_vec3 v1, t_vec3 v2)
{
	float	ret;

	ret = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return (ret);
}
