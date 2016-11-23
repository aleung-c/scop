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

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	t_scop *sc = g_global_sc;

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
		deallocate_variables(sc);
		exit (0);
	}
	// rotation toggle
	else if (key == GLFW_KEY_F && action == GLFW_PRESS)
	{
		if (sc->is_rotating == 1)
			sc->is_rotating = 0;
		else
			sc->is_rotating = 1;
	}
	// rotations changing
	else if (key == GLFW_KEY_W && action == GLFW_PRESS) // up
	{
		sc->is_rotating_x = -1;
		sc->is_rotating_y = 0;
		sc->is_rotating_z = 0;
	}
	else if (key == GLFW_KEY_S && action == GLFW_PRESS) // down
	{
		sc->is_rotating_x = 1;
		sc->is_rotating_y = 0;
		sc->is_rotating_z = 0;
	}
	else if (key == GLFW_KEY_A && action == GLFW_PRESS) // left
	{
		sc->is_rotating_x = 0;
		sc->is_rotating_y = -1;
		sc->is_rotating_z = 0;
	}
	else if (key == GLFW_KEY_D && action == GLFW_PRESS) // right
	{
		sc->is_rotating_x = 0;
		sc->is_rotating_y = 1;
		sc->is_rotating_z = 0;
	}
	else if (key == GLFW_KEY_Q && action == GLFW_PRESS) // left z
	{
		sc->is_rotating_x = 0;
		sc->is_rotating_y = 0;
		sc->is_rotating_z = 1;
	}
	else if (key == GLFW_KEY_E && action == GLFW_PRESS) // right z
	{
		sc->is_rotating_x = 0;
		sc->is_rotating_y = 0;
		sc->is_rotating_z = -1;
	}
	// go to transition
	else if (key == GLFW_KEY_R && action == GLFW_PRESS && sc->on_standby == 1)
	{
		sc->on_standby = 0; // cant press transition button now until transition done
		sc->in_transition = 1;
		sc->buffer_i = 0; // reset array change counter.
		if (sc->transition_value == 0)
			sc->transition_value = 1;
		else
			sc->transition_value = 0;
		//printf("goto transition\n");
	}
	// bonus : using ebo.
	else if (key == GLFW_KEY_T && action == GLFW_PRESS)
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
void		opengl_drawing(t_scop *sc)
{
	while (!glfwWindowShouldClose(sc->window))
	{
		// wipe the drawing surface clear
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(sc->main_shader_programme);

		event_process(sc);

		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glEnableVertexAttribArray(4);
		glEnableVertexAttribArray(5);

		// draw points 0-3 from the currently bound VAO with current in-use shader
		//glDrawArrays (GL_POINTS, 0, sc->nb_vertices * 4);
		
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
			glDrawElements(GL_TRIANGLES, (sc->total_faces * 3), GL_UNSIGNED_INT, (void *)0);
		}
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(3);
		glDisableVertexAttribArray(4);
		glDisableVertexAttribArray(5);

		glfwSetKeyCallback(sc->window, key_callback);
		// update other events like input handling 
		glfwPollEvents();
		// put the stuff we've been drawing onto the display
		glfwSwapBuffers(sc->window);
	}
}


// ggaubin's code.	
/*
	static void		fifty_fifty(t_object *o, t_mat4 p, t_mat4 view)
{
	update_mat(&o->model, o->translation, o->rotation, o->scale);
	glUseProgram(o->program);
	glUniformMatrix4fv(o->view_matrix_id, 1, GL_FALSE, (void *)&view);
	glUniformMatrix4fv(o->projection_matrix_id, 1, GL_FALSE,\
						(void *)&p);
	glUniformMatrix4fv(o->model_matrix_id, 1, GL_FALSE, (void *)&(o->model));
	glUniform1f(o->texture_mix_id, o->texture_mix_coeff);
	set_ambiant_color(o);
	glBindTexture(GL_TEXTURE_2D, o->texture);
	glBindBuffer(GL_ARRAY_BUFFER, o->vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, o->cvbo);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}

void			draw(t_object *o, GLenum mode, t_mat4 projection, t_mat4 view)
{
	fifty_fifty(o, projection, view);
	glBindBuffer(GL_ARRAY_BUFFER, o->nbo);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, o->ubo);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glDrawArrays(mode, 0, o->size_mesh / 3);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
}
*/

