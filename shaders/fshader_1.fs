#version 410

in vec4					vertex_position;
out vec4				frag_colour;

uniform bool			has_texture = false;
uniform sampler2D		tex;

void main ()
{
	if (!has_texture)
	{
		frag_colour = vertex_position;
	}
	else
	{
		vec4 normalized_v = normalize(vertex_position);
		vec2 tex_UV = vec2(1.0 / vertex_position.x, 1.0 / vertex_position.y);
		frag_colour = texture(tex, tex_UV);
	}
}
