#version 330 core

layout(location =0) in vec2 v_position;

uniform mat4 projection;

void main()
{
  gl_Position = projection*vec4(v_position , 1.0 , 1.0);
}