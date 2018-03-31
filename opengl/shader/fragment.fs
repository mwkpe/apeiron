#version 330 core

uniform bool draw_texture;
uniform sampler2D texture2d;
uniform vec4 color;

out vec4 frag_color;
in vec2 tex_coord;

void main()
{
  if (draw_texture) {
    frag_color = texture(texture2d, tex_coord);
  }
  else {
    frag_color = color;
  }
}
