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

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		//glBindVertexArray (vao);

		// draw points 0-3 from the currently bound VAO with current in-use shader
		//glDrawArrays (GL_POINTS, 0, sc->nb_vertices * 4);
		
		//glDrawArrays (GL_TRIANGLES, 0, ((sc->nb_faces_3 * 3) * 3));
		glDrawElements(GL_TRIANGLES, (sc->nb_faces_3 * 3 + (sc->nb_faces_4 * 2) * 3), GL_UNSIGNED_INT, (void *)0);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

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

