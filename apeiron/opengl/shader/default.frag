#version 330 core


out vec4 frag_color;
in vec3 frag_position;
in vec3 normal;
in vec2 texcoord;
in vec4 vertex_color;


uniform int color_mode;
uniform bool lighting_enabled;
uniform bool color_multiplication_enabled;
uniform bool color_inversion_enabled;
uniform bool color_desaturation_enabled;
uniform float color_desaturation_strength;
uniform sampler2D texture2d;
uniform vec4 color;
uniform vec4 light_color;
uniform vec3 light_position;


void main()
{
  vec4 object_color;
  float ambient_strength = 0.15;

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

  if (color_multiplication_enabled) {
    object_color = object_color * color;
  }

  if (lighting_enabled) {
    vec3 dir = normalize(light_position - frag_position);
    vec3 diffuse = max(dot(normalize(normal), dir), 0.0) * light_color.rgb;
    vec3 ambient = ambient_strength * light_color.rgb;
    object_color = vec4(object_color.rgb * (ambient + diffuse), object_color.a);
  }

  if (color_desaturation_enabled) {
    vec3 grayscale = vec3(dot(object_color.rgb, vec3(0.2126, 0.7152, 0.0722)));
    object_color = vec4(mix(object_color.rgb, grayscale, color_desaturation_strength),
        object_color.a);
  }

  if (color_inversion_enabled) {
    object_color = vec4(vec3(1.0, 1.0, 1.0) - object_color.rgb, object_color.a);
  }

  frag_color = object_color;
}
