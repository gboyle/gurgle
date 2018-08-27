#shader vertex    
#version 330 core

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_color;

out vec3 v_color;

uniform mat4 u_mvp; // model view projection matrix

void main()
{
   gl_Position = u_mvp * vec4(in_position, 1.0);
   v_color = in_color;
}


#shader fragment
#version 330 core

in vec3 v_color;

out vec4 f_color;

void main()
{
   f_color = vec4(v_color, 1.0);
}