#ifndef APEIRON_VERTEX_H
#define APEIRON_VERTEX_H


#include <cstdint>
#include <glm/glm.hpp>


namespace apeiron::engine {


struct Vertex
{
  Vertex() = default;
  constexpr Vertex(float x, float y, float z,
      float nx, float ny, float nz,
      float s, float t,
      float r, float g, float b, float a = 1.0f)
      : position{x, y, z},
        normal{nx, ny, nz},
        texcoords{s, t},
        color{r, g, b, a} {}
  constexpr Vertex(const glm::vec3& position,
      const glm::vec3& normal,
      const glm::vec2& texcoords,
      const glm::vec4& color)
      : position{position},
        normal{normal},
        texcoords{texcoords},
        color{color} {}
  glm::vec3 position;
  glm::vec3 normal;
  glm::vec2 texcoords;
  glm::vec4 color;
};


struct Vertex_simple
{
  Vertex_simple() = default;
  Vertex_simple(float x, float y, float z) : position{x, y, z} {}
  constexpr explicit Vertex_simple(const glm::vec3& position) : position{position} {}
  glm::vec3 position;
};


struct Vertex_normal
{
  Vertex_normal() = default;
  constexpr Vertex_normal(float x, float y, float z, float nx, float ny, float nz)
      : position{x, y, z}, normal{nx, ny, nz} {}
  constexpr Vertex_normal(const glm::vec3& position, const glm::vec3& normal)
      : position{position}, normal{normal} {}
  glm::vec3 position;
  glm::vec3 normal;
};


struct Vertex_color
{
  Vertex_color() = default;
  constexpr Vertex_color(float x, float y, float z, float r, float g, float b, float a = 1.0f)
      : position{x, y, z}, color{r, g, b, a} {}
  constexpr Vertex_color(const glm::vec3& position, const glm::vec4& color)
      : position{position}, color{color} {}
  glm::vec3 position;
  glm::vec4 color;
};


struct Vertex_texcoords
{
  Vertex_texcoords() = default;
  constexpr Vertex_texcoords(float x, float y, float z, float s, float t)
      : position{x, y, z}, texcoords{s, t} {}
  constexpr Vertex_texcoords(const glm::vec3& position, const glm::vec2& texcoords)
      : position{position}, texcoords{texcoords} {}
  glm::vec3 position;
  glm::vec2 texcoords;
};


struct Vertex_normal_color
{
  Vertex_normal_color() = default;
  constexpr Vertex_normal_color(float x, float y, float z,
      float nx, float ny, float nz,
      float r, float g, float b, float a = 1.0f)
      : position{x, y, z},
        normal{nx, ny, nz},
        color{r, g, b, a} {}
  constexpr Vertex_normal_color(const glm::vec3& position,
      const glm::vec3& normal,
      const glm::vec4& color)
      : position{position},
        normal{normal},
        color{color} {}
  glm::vec3 position;
  glm::vec3 normal;
  glm::vec4 color;
};


struct Vertex_normal_texcoords
{
  Vertex_normal_texcoords() = default;
  constexpr Vertex_normal_texcoords(float x, float y, float z,
      float nx, float ny, float nz,
      float s, float t)
      : position{x, y, z},
        normal{nx, ny, nz},
        texcoords{s, t} {}
  constexpr Vertex_normal_texcoords(const glm::vec3& position,
      const glm::vec3& normal,
      const glm::vec2& texcoords)
      : position{position},
        normal{normal},
        texcoords{texcoords} {}
  glm::vec3 position;
  glm::vec3 normal;
  glm::vec2 texcoords;
};


struct Vertex_index
{
  std::uint16_t index;
  std::uint8_t color;
  std::uint8_t material;
};


}  // namespace apeiron::engine


#endif  // APEIRON_VERTEX_H
