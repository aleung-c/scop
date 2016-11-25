/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 14:13:52 by aleung-c          #+#    #+#             */
/*   Updated: 2016/11/16 14:13:55 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

t_color		create_color(float r, float g, float b, float a)
{
	t_color		ret;

	ret.r = r;
	ret.g = g;
	ret.b = b;
	ret.a = a;
	return (ret);
}

t_color		set_color(float r, float g, float b, float a)
{
	t_color c;

	c.r = r;
	c.g = g;
	c.b = b;
	c.a = a;
	return (c);
}
