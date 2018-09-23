#version 330 core

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_texcoord;
layout (location = 3) in vec4 a_color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 frag_position;
out vec3 normal;
out vec2 texcoord;
out vec4 vertex_color;

void main()
{
  gl_Position = projection * view * model * vec4(a_position, 1.0);
  frag_position = vec3(model * vec4(a_position, 1.0));
  normal = a_normal;
  texcoord = a_texcoord;
  vertex_color = a_color;
}