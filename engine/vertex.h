#ifndef APEIRON_VERTEX_H
#define APEIRON_VERTEX_H


#include <glm/glm.hpp>


namespace apeiron::engine {


struct Vertex
{
  Vertex() = default;
  Vertex(glm::vec3 position, glm::vec3 normal, glm::vec2 texcoords, glm::vec4 color)
      : position{position}, normal{normal}, texcoords{texcoords}, color{color} {}
  glm::vec3 position;
  glm::vec3 normal;
  glm::vec2 texcoords;
  glm::vec4 color;
};


struct Vertex_simple
{
  Vertex_simple() = default;
  Vertex_simple(glm::vec3 position) : position{position} {}
  glm::vec3 position;
};


struct Vertex_normal
{
  Vertex_normal() = default;
  Vertex_normal(glm::vec3 position, glm::vec3 normal)
      : position{position}, normal{normal} {}
  glm::vec3 position;
  glm::vec3 normal;
};


struct Vertex_color
{
  Vertex_color() = default;
  Vertex_color(glm::vec3 position, glm::vec4 color)
      : position{position}, color{color} {}
  glm::vec3 position;
  glm::vec4 color;
};


struct Vertex_texcoords
{
  Vertex_texcoords() = default;
  Vertex_texcoords(glm::vec3 position, glm::vec2 texcoords)
      : position{position}, texcoords{texcoords} {}
  glm::vec3 position;
  glm::vec2 texcoords;
};


struct Vertex_normal_color
{
  Vertex_normal_color() = default;
  Vertex_normal_color(glm::vec3 position, glm::vec3 normal, glm::vec4 color)
      : position{position}, normal{normal}, color{color} {}
  glm::vec3 position;
  glm::vec3 normal;
  glm::vec4 color;
};


struct Vertex_normal_texcoords
{
  Vertex_normal_texcoords() = default;
  Vertex_normal_texcoords(glm::vec3 position, glm::vec3 normal, glm::vec2 texcoords)
      : position{position}, normal{normal}, texcoords{texcoords} {}
  glm::vec3 position;
  glm::vec3 normal;
  glm::vec2 texcoords;
};


}  // namespace apeiron::engine


#endif  // APEIRON_VERTEX_H
