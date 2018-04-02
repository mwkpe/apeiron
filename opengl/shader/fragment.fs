#version 330 core

uniform int color_mode;
uniform int light_mode;
uniform sampler2D texture2d;
uniform vec4 color;
uniform vec3 light_color;
uniform vec3 light_position;

out vec4 frag_color;
in vec3 frag_position;
in vec3 normal;
in vec2 tex_coord;
in vec3 vertex_color;

void main()
{
  vec4 object_color;
  float ambient = 0.2;

  switch (color_mode) {
    case 0:
      object_color = texture(texture2d, tex_coord);
      break;
    case 1:
      object_color = vec4(vertex_color, 1.0);
      break;
    case 2:
      object_color = color;
      break;
    default:
      object_color = vec4(1.0, 0.0, 1.0, 1.0);
  }

  switch (light_mode) {
    case 1:
      vec3 n = normalize(normal);
      vec3 dir = normalize(light_position - frag_position);
      vec3 diffuse = max(dot(n, dir), 0.0) * light_color;
      frag_color = vec4(object_color.rgb * (ambient + diffuse), object_color.a);
      break;
    default:
      frag_color = object_color;
  }
}
