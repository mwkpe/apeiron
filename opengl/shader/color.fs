#version 330 core

uniform int color_mode;
uniform int light_mode;
uniform bool colorize;
uniform sampler2D texture2d;
uniform vec4 color;
uniform vec3 light_color;
uniform vec3 light_position;

out vec4 frag_color;
in vec3 frag_position;
in vec3 normal;
in vec2 texcoord;
in vec4 vertex_color;

void main()
{
  vec4 object_color;
  float ambient = 0.2;

  switch (color_mode) {
    case 0:
      object_color = texture(texture2d, texcoord);
      break;
    case 1:
      object_color = vertex_color;
      break;
    case 2:
      object_color = color;
      break;
    default:
      object_color = vec4(1.0, 0.0, 1.0, 1.0);
  }

  if (colorize) {
    object_color = object_color * color;
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
