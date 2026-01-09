#version 460 core

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_texcoord;
layout (location = 3) in vec4 a_color;

uniform int render_mode;

// World
uniform mat4 model;
uniform mat4 view_projection;

// Screen
uniform vec3 scale;
uniform vec3 translation;
uniform mat4 projection;

out vec3 frag_position;
out vec3 normal;
out vec2 texcoord;
out vec4 vertex_color;

void main()
{
  if (render_mode == 0) {
    vec4 world_position = model * vec4(a_position, 1.0);
    gl_Position = view_projection * world_position;
    frag_position = vec3(model * vec4(a_position, 1.0));
    normal = vec3(model * vec4(a_normal, 0.0));
  }
  else {
    vec3 pos = a_position * scale + translation;
    gl_Position = projection * vec4(pos, 1.0);
  }

  texcoord = a_texcoord;
  vertex_color = a_color;
}
