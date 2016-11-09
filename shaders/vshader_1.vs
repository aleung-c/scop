#version 410
in vec4 vp;
uniform mat4	identity_matrix;
uniform mat4	translation_matrix;
uniform mat4	scaling_matrix;
uniform mat4	rotation_x_matrix;
uniform mat4	rotation_y_matrix;
uniform mat4	rotation_z_matrix;

void main ()
{
	mat4	model_matrice = translation_matrix * rotation_x_matrix * rotation_y_matrix * rotation_z_matrix * scaling_matrix * identity_matrix;

	gl_Position = model_matrice * vp;
}
