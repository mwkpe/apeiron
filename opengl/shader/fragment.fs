#version 330 core

uniform int color_mode;
uniform sampler2D texture2d;
uniform vec4 color;

out vec4 frag_color;
in vec3 normal;
in vec2 tex_coord;
in vec3 vertex_color;

void main()
{
  switch (color_mode) {
    case 0:
      frag_color = texture(texture2d, tex_coord);
      break;
    case 1:
      frag_color = vec4(vertex_color, 1.0);
      break;
    case 2:
      frag_color = color;
      break;
    default:
      frag_color = vec4(1.0, 0.0, 1.0, 1.0);
  }
}
