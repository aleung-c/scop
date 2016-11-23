#version 410

in vec4					vertex_position;
in vec3					vertex_normal;
flat in vec3					color;
in vec2					texture_coordinates;
flat in int				t_flag;



uniform bool			has_texture = false;
uniform bool			is_transitionning = false;
uniform sampler2D		tex;

// the final color the fragment will take.
out vec4				frag_colour;

void main ()
{
	if (t_flag == 0)
	{
		//frag_colour = vertex_position;
		frag_colour = vec4(color, 1.0);
	}
	else
	{
		//vec2 tex_UV = vec2(vertex_normal.x, vertex_normal.y);
		vec4	texel = texture(tex, texture_coordinates);
		frag_colour = texel;
		//frag_colour = vec4(color, 1.0);
		
	}
}

// #version 410

// uniform mat4 view_mat;
// uniform vec4 ambiant_light;
// uniform float coeff;

// in vec2 texture_coordinates;
// in vec3 color;
// in vec3 position_eye;
// in vec3 normal_eye;

// //fixed point light
// vec3 light_position_world = vec3(0.0, 3.0, 2.0);
// vec3 ls = vec3(1.0, 1.0, 1.0);
// vec3 ld = vec3(1.0, 1.0, 1.0);
// vec3 la = ambiant_light.rgb;

// //surface reflectance
// vec3 ks = vec3(1.0, 1.0, 1.0);
// vec3 kd = vec3(1.0, 1.0, 1.0);
// vec3 ka = la + la;
// float specular_exponent = 1000.0;

// vec4 spec_lvl_0 = vec4 (0.0, 0.0, 0.0, 1.0);
// vec4 spec_lvl_1 = mix(vec4 (0.3, 0.3, 0.3, 1.0), ambiant_light, 0.3);
// vec4 spec_lvl_2 = mix(vec4 (0.6, 0.6, 0.6, 1.0), ambiant_light, 0.6);
// vec4 spec_lvl_3 = vec4 (1.0, 1.0, 1.0, 1.0);

// out vec4 frag_color;

// uniform sampler2D basic_texture;

// void main () {
//     vec3 light_position_eye = vec3 (view_mat * vec4 (light_position_world, 1.0));
//     vec3 distance_to_light_eye = light_position_eye - position_eye;
//     vec3 direction_to_light_eye = normalize(distance_to_light_eye);
//     float dot_prod = dot(direction_to_light_eye, normal_eye);
//     dot_prod = max(dot_prod, 0.0);
//     vec3 surface_to_viewer_eye = normalize(-position_eye);
//     vec3 half_way_eye = normalize(surface_to_viewer_eye + direction_to_light_eye);
//     float dot_prot_specular = dot(half_way_eye, normal_eye);
//     float specular_factor = pow(dot_prot_specular, specular_exponent);
//     vec3 ia = la * ka;
//     vec3 id = ld * kd * dot_prod;
//     vec3 is = ls * ks * specular_factor;
//     vec4 texel = texture(basic_texture, texture_coordinates);
//     vec4 specular = vec4 (is + id + ia, 1.0);
// 	/*
// 	** Dequote for tooonshiding shader
// 	*/
// /*
//     if (specular.x >= spec_lvl_0.x && specular.x < spec_lvl_1.x)
//         specular = spec_lvl_0;
//     else if (specular.x >= spec_lvl_1.x && specular.x < spec_lvl_2.x)
//         specular = spec_lvl_1;
//     else if (specular.x >= spec_lvl_2.x && specular.x < spec_lvl_3.x)
//         specular = spec_lvl_2;
//     else
//         specular = spec_lvl_3;
// */
//     vec4 mixed_color = mix(texel, vec4(color, 1.0), coeff);
//     frag_color = mixed_color * specular;
// }