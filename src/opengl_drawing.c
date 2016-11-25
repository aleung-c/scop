/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opengl_drawing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 15:01:58 by aleung-c          #+#    #+#             */
/*   Updated: 2016/11/21 15:02:00 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

static void		key_callback(GLFWwindow *window, int key, int scancode,
							int action, int mods)
{
	t_scop	*sc;

	sc = g_global_sc;
	if (scancode && mods)
	{
	}
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
		deallocate_variables(sc);
		exit(0);
	}
	toggle_rotation(sc, key, action);
	toggle_rotation_change_1(sc, key, action);
	toggle_rotation_change_2(sc, key, action);
	toggle_transition_and_tswitch(sc, key, action);
	set_zoom_level(sc, key, action);
	apply_step_back(sc, key, action);
	if (key == GLFW_KEY_T && action == GLFW_PRESS)
	{
		if (sc->using_array == 1)
			sc->using_array = 0;
		else
			sc->using_array = 1;
	}
}

/*
**	GLFW/GL drawing loop.
*/

void			opengl_drawing(t_scop *sc)
{
	while (!glfwWindowShouldClose(sc->window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(sc->main_shader_programme);
		event_process(sc);
		opengl_drawing_enable_arrays();
		opengl_drawing_set_zero_attribute(sc);
		opengl_drawing_disable_arrays();
		glfwSetKeyCallback(sc->window, key_callback);
		glfwPollEvents();
		glfwSwapBuffers(sc->window);
	}
}

void			opengl_drawing_enable_arrays(void)
{
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(4);
	glEnableVertexAttribArray(5);
}

void			opengl_drawing_set_zero_attribute(t_scop *sc)
{
	if (sc->using_array == 1)
	{
		glBindBuffer(GL_ARRAY_BUFFER, sc->fvbo);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(0);
		glDrawArrays(GL_TRIANGLES, 0, (((sc->total_faces * 3) * 4)));
	}
	else
	{
		glBindBuffer(GL_ARRAY_BUFFER, sc->vbo);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(0);
		glDrawElements(GL_TRIANGLES, (sc->total_faces * 3),
						GL_UNSIGNED_INT, (void *)0);
	}
}

void			opengl_drawing_disable_arrays(void)
{
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(4);
	glDisableVertexAttribArray(5);
}
