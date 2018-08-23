#shader vertex    
#version 330 core

layout(location = 0) in vec2 in_position;
layout(location = 1) in vec3 in_color;
layout(location = 2) in vec2 in_tex_coord;

out vec3 v_color;
out vec2 v_tex_coord;

uniform mat4 u_mvp; // model view projection matrix

void main()
{
   gl_Position = u_mvp * vec4(in_position, 0.0, 1.0);
   v_tex_coord = in_tex_coord;
   v_color = in_color;

   // hack to make the texture coordinates into colors for debugging
   // v_color = vec3(in_tex_coord,0.0);
}


#shader fragment
#version 330 core

in vec3 v_color;
in vec2 v_tex_coord;

out vec4 f_color;

uniform vec4 u_color;
uniform sampler2D u_texture;

void main()
{
   // gradient color
   vec4 f_color1 = vec4(v_color, 1.0);

   // rotating color
   vec4 f_color2 = u_color;

   // texture color
   vec4 f_color3 = texture(u_texture, v_tex_coord);

   f_color = f_color1 * f_color2 * f_color3;
}