#ifndef APEIRON_VERTEX_H
#define APEIRON_VERTEX_H


#include <glm/glm.hpp>


namespace apeiron::engine::vertex {


struct Position
{
  Position() = default;
  Position(float x, float y, float z) : x{x}, y{y}, z{z} {}
  Position(glm::vec3 position) : x{position.x}, y{position.y}, z{position.z} {}
  float x;
  float y;
  float z;
};


struct Texcoords
{
  Texcoords() = default;
  Texcoords(float s, float t) : s{s}, t{t} {}
  Texcoords(glm::vec2 texcoords) : s{texcoords.s}, t{texcoords.t} {}
  float s;
  float t;
};


struct Color
{
  Color() = default;
  Color(float r, float g, float b) : r{r}, g{g}, b{b}, a{1.0f} {}
  Color(float r, float g, float b, float a) : r{r}, g{g}, b{b}, a{a} {}
  Color(glm::vec3 color) : r{color.r}, g{color.g}, b{color.b}, a{1.0f} {}
  Color(glm::vec4 color) : r{color.r}, g{color.g}, b{color.b}, a{color.a} {}
  float r;
  float g;
  float b;
  float a;
};


}  // namespace apeiron::engine::vertex


namespace apeiron::engine {


struct Vertex
{
  Vertex() = default;
  Vertex(float x, float y, float z, float nx, float ny, float nz,
      float s, float t, float r, float g, float b, float a)
      : position{x, y, z}, normal{nx, ny, nz}, texcoords{s, t}, color{r, g, b, a} {}
  Vertex(glm::vec3 position, glm::vec3 normal, glm::vec2 texcoords, glm::vec4 color)
      : position{position}, normal{normal}, texcoords{texcoords}, color{color} {}
  Vertex(glm::vec3 position, glm::vec3 normal, glm::vec2 texcoords, glm::vec3 color)
      : position{position}, normal{normal}, texcoords{texcoords}, color{color} {}
  vertex::Position position;
  vertex::Position normal;
  vertex::Texcoords texcoords;
  vertex::Color color;
};


struct Vertex_simple
{
  Vertex_simple() = default;
  Vertex_simple(float x, float y, float z) : position{x, y, z} {}
  Vertex_simple(glm::vec3 position) : position{position} {}
  vertex::Position position;
};


struct Vertex_normal
{
  Vertex_normal() = default;
  Vertex_normal(float x, float y, float z, float nx, float ny, float nz)
      : position{x, y, z}, normal{nx, ny, nz} {}
  Vertex_normal(glm::vec3 position, glm::vec3 normal)
      : position{position}, normal{normal} {}
  vertex::Position position;
  vertex::Position normal;
};


struct Vertex_color
{
  Vertex_color() = default;
  Vertex_color(float x, float y, float z, float r, float g, float b)
      : position{x, y, z}, color{r, g, b, 1.0f} {}
  Vertex_color(float x, float y, float z, float r, float g, float b, float a)
      : position{x, y, z}, color{r, g, b, a} {}
  Vertex_color(glm::vec3 position, glm::vec4 color)
      : position{position}, color{color} {}
  Vertex_color(glm::vec3 position, glm::vec3 color)
      : position{position}, color{color} {}
  vertex::Position position;
  vertex::Color color;
};


struct Vertex_texcoords
{
  Vertex_texcoords() = default;
  Vertex_texcoords(float x, float y, float z, float s, float t)
      : position{x, y, z}, texcoords{s, t} {}
  Vertex_texcoords(glm::vec3 position, glm::vec2 texcoords)
      : position{position}, texcoords{texcoords} {}
  vertex::Position position;
  vertex::Texcoords texcoords;
};


struct Vertex_normal_color
{
  Vertex_normal_color() = default;
  Vertex_normal_color(float x, float y, float z, float nx, float ny, float nz,
      float r, float g, float b, float a)
      : position{x, y, z}, normal{nx, ny, nz}, color{r, g, b, a} {}
  Vertex_normal_color(glm::vec3 position, glm::vec3 normal, glm::vec3 color)
      : position{position}, normal{normal}, color{color} {}
  Vertex_normal_color(glm::vec3 position, glm::vec3 normal, glm::vec4 color)
      : position{position}, normal{normal}, color{color} {}
  vertex::Position position;
  vertex::Position normal;
  vertex::Color color;
};


struct Vertex_normal_texcoords
{
  Vertex_normal_texcoords() = default;
  Vertex_normal_texcoords(float x, float y, float z, float nx, float ny, float nz,
      float s, float t) : position{x, y, z}, normal{nx, ny, nz}, texcoords{s, t} {}
  Vertex_normal_texcoords(glm::vec3 position, glm::vec3 normal, glm::vec2 texcoords)
      : position{position}, normal{normal}, texcoords{texcoords} {}
  vertex::Position position;
  vertex::Position normal;
  vertex::Texcoords texcoords;
};


}  // namespace apeiron::engine


#endif  // APEIRON_VERTEX_H
