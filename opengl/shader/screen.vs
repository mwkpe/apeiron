#version 330 core

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_texcoord;
layout (location = 3) in vec4 a_color;

uniform vec2 screen_center;
uniform vec3 scale;
uniform vec3 translation;
uniform mat4 projection;

out vec3 frag_position;
out vec3 normal;
out vec2 texcoord;
out vec4 vertex_color;

void main()
{
  vec3 pos = a_position * scale + translation;
  vec2 clip_pos = pos.xy - screen_center;
  clip_pos /= screen_center;
  gl_Position = projection * vec4(clip_pos, pos.z, 1.0);
  texcoord = a_texcoord;
  vertex_color = a_color;
}
