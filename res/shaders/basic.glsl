#shader vertex    
#version 330 core

layout(location = 0) in vec2 in_position;
layout(location = 1) in vec2 in_tex_coord;

out vec2 v_tex_coord;

uniform mat4 u_mvp; // model view projection matrix

void main()
{
   gl_Position = u_mvp * vec4(in_position, 0.0, 1.0);
   v_tex_coord = in_tex_coord;
}


#shader fragment
#version 330 core

in vec2 v_tex_coord;

out vec4 f_color;

uniform sampler2D u_texture;

void main()
{
   f_color = texture(u_texture, v_tex_coord);
}