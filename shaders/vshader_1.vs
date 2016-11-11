#version 410
in vec4 vp;

// model matrices
uniform mat4	identity_matrix;
uniform mat4	model_recenter_translation_matrix;
uniform mat4	model_translation_matrix;
uniform mat4	scaling_matrix;
uniform mat4	rotation_x_matrix;
uniform mat4	rotation_y_matrix;
uniform mat4	rotation_z_matrix;

// view matrices
uniform mat4	view_translation_matrix;
uniform mat4	view_orientation_matrix;

// projection matrices
uniform mat4	perspective_projection_matrix;

void main ()
{
	mat4	model_matrice =
		model_translation_matrix * 
		rotation_x_matrix * rotation_y_matrix * rotation_z_matrix * 
		scaling_matrix * model_recenter_translation_matrix * identity_matrix ;

	mat4	view_matrice = view_orientation_matrix * view_translation_matrix;

	gl_Position = perspective_projection_matrix * view_matrice * model_matrice * vp;
}
