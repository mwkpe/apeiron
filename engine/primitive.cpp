#include "engine/primitive.h"


#include <type_traits>
#include <glm/gtc/matrix_access.hpp>


template<typename T> std::vector<T> apeiron::engine::primitive::quad_vertices(float width,
    float height, Face face, const glm::vec3& position)
{
  const float x = position.x;
  const float y = position.y;
  const float z = position.z;

  const float w = width * 0.5f;
  const float h = height * 0.5f;

  if constexpr (std::is_same<T, Vertex>::value) {
    switch (face) {
      case Face::Front:
        return {
          // x, y, z, nx, ny, nz, s, t, r, g, b, a
          // xy-plane
          {{-w + x, -h + y, z}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
          {{ w + x, -h + y, z}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
          {{ w + x,  h + y, z}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
          {{ w + x,  h + y, z}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
          {{-w + x,  h + y, z}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
          {{-w + x, -h + y, z}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}}
        };
      case Face::Back:
        return {
          // xy-plane
          {{ w + x, -h + y, z}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
          {{-w + x, -h + y, z}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
          {{-w + x,  h + y, z}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
          {{-w + x,  h + y, z}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
          {{ w + x,  h + y, z}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
          {{ w + x, -h + y, z}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}}
        };
      case Face::Left:
        return {
          // yz-plane
          {{x, -h + y, -w + z}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
          {{x, -h + y,  w + z}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
          {{x,  h + y,  w + z}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
          {{x,  h + y,  w + z}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
          {{x,  h + y, -w + z}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
          {{x, -h + y, -w + z}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}}
        };
      case Face::Right:
        return {
          // yz-plane
          {{x, -h + y,  w + z}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
          {{x, -h + y, -w + z}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
          {{x,  h + y, -w + z}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
          {{x,  h + y, -w + z}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
          {{x,  h + y,  w + z}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
          {{x, -h + y,  w + z}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}}
        };
      case Face::Up:
        return {
          // xz-plane
          {{-w + x, y,  h + z}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
          {{ w + x, y,  h + z}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
          {{ w + x, y, -h + z}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
          {{ w + x, y, -h + z}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
          {{-w + x, y, -h + z}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
          {{-w + x, y,  h + z}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}}
        };
      case Face::Down:
        return {
          // xz-plane
          {{-w + x, y, -h + z}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
          {{ w + x, y, -h + z}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
          {{ w + x, y,  h + z}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
          {{ w + x, y,  h + z}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
          {{-w + x, y,  h + z}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
          {{-w + x, y, -h + z}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}}
        };
    }
  }
  else if constexpr (std::is_same<T, Vertex_simple>::value) {
    switch (face) {
      case Face::Front:
        return {
          // x, y, z
          // xy-plane
          {{-w + x, -h + y, z}},
          {{ w + x, -h + y, z}},
          {{ w + x,  h + y, z}},
          {{ w + x,  h + y, z}},
          {{-w + x,  h + y, z}},
          {{-w + x, -h + y, z}}
        };
      case Face::Back:
        return {
          // xy-plane
          {{ w + x, -h + y, z}},
          {{-w + x, -h + y, z}},
          {{-w + x,  h + y, z}},
          {{-w + x,  h + y, z}},
          {{ w + x,  h + y, z}},
          {{ w + x, -h + y, z}}
        };
      case Face::Left:
        return {
          // yz-plane
          {{x, -h + y, -w + z}},
          {{x, -h + y,  w + z}},
          {{x,  h + y,  w + z}},
          {{x,  h + y,  w + z}},
          {{x,  h + y, -w + z}},
          {{x, -h + y, -w + z}}
        };
      case Face::Right:
        return {
          // yz-plane
          {{x, -h + y,  w + z}},
          {{x, -h + y, -w + z}},
          {{x,  h + y, -w + z}},
          {{x,  h + y, -w + z}},
          {{x,  h + y,  w + z}},
          {{x, -h + y,  w + z}}
        };
      case Face::Up:
        return {
          // xz-plane
          {{-w + x, y,  h + z}},
          {{ w + x, y,  h + z}},
          {{ w + x, y, -h + z}},
          {{ w + x, y, -h + z}},
          {{-w + x, y, -h + z}},
          {{-w + x, y,  h + z}}
        };
      case Face::Down:
        return {
          // xz-plane
          {{-w + x, y, -h + z}},
          {{ w + x, y, -h + z}},
          {{ w + x, y,  h + z}},
          {{ w + x, y,  h + z}},
          {{-w + x, y,  h + z}},
          {{-w + x, y, -h + z}}
        };
    }
  }
  else if constexpr (std::is_same<T, Vertex_normal>::value) {
    switch (face) {
      case Face::Front:
        return {
          // x, y, z, nx, ny, nz
          // xy-plane
          {{-w + x, -h + y, z}, {0.0f, 0.0f, 1.0f}},
          {{ w + x, -h + y, z}, {0.0f, 0.0f, 1.0f}},
          {{ w + x,  h + y, z}, {0.0f, 0.0f, 1.0f}},
          {{ w + x,  h + y, z}, {0.0f, 0.0f, 1.0f}},
          {{-w + x,  h + y, z}, {0.0f, 0.0f, 1.0f}},
          {{-w + x, -h + y, z}, {0.0f, 0.0f, 1.0f}}
        };
      case Face::Back:
        return {
          // xy-plane
          {{ w + x, -h + y, z}, {0.0f, 0.0f, -1.0f}},
          {{-w + x, -h + y, z}, {0.0f, 0.0f, -1.0f}},
          {{-w + x,  h + y, z}, {0.0f, 0.0f, -1.0f}},
          {{-w + x,  h + y, z}, {0.0f, 0.0f, -1.0f}},
          {{ w + x,  h + y, z}, {0.0f, 0.0f, -1.0f}},
          {{ w + x, -h + y, z}, {0.0f, 0.0f, -1.0f}}
        };
      case Face::Left:
        return {
          // yz-plane
          {{x, -h + y, -w + z}, {-1.0f, 0.0f, 0.0f}},
          {{x, -h + y,  w + z}, {-1.0f, 0.0f, 0.0f}},
          {{x,  h + y,  w + z}, {-1.0f, 0.0f, 0.0f}},
          {{x,  h + y,  w + z}, {-1.0f, 0.0f, 0.0f}},
          {{x,  h + y, -w + z}, {-1.0f, 0.0f, 0.0f}},
          {{x, -h + y, -w + z}, {-1.0f, 0.0f, 0.0f}}
        };
      case Face::Right:
        return {
          // yz-plane
          {{x, -h + y,  w + z}, {1.0f, 0.0f, 0.0f}},
          {{x, -h + y, -w + z}, {1.0f, 0.0f, 0.0f}},
          {{x,  h + y, -w + z}, {1.0f, 0.0f, 0.0f}},
          {{x,  h + y, -w + z}, {1.0f, 0.0f, 0.0f}},
          {{x,  h + y,  w + z}, {1.0f, 0.0f, 0.0f}},
          {{x, -h + y,  w + z}, {1.0f, 0.0f, 0.0f}}
        };
      case Face::Up:
        return {
          // xz-plane
          {{-w + x, y,  h + z}, {0.0f, 1.0f, 0.0f}},
          {{ w + x, y,  h + z}, {0.0f, 1.0f, 0.0f}},
          {{ w + x, y, -h + z}, {0.0f, 1.0f, 0.0f}},
          {{ w + x, y, -h + z}, {0.0f, 1.0f, 0.0f}},
          {{-w + x, y, -h + z}, {0.0f, 1.0f, 0.0f}},
          {{-w + x, y,  h + z}, {0.0f, 1.0f, 0.0f}}
        };
      case Face::Down:
        return {
          // xz-plane
          {{-w + x, y, -h + z}, {0.0f, -1.0f, 0.0f}},
          {{ w + x, y, -h + z}, {0.0f, -1.0f, 0.0f}},
          {{ w + x, y,  h + z}, {0.0f, -1.0f, 0.0f}},
          {{ w + x, y,  h + z}, {0.0f, -1.0f, 0.0f}},
          {{-w + x, y,  h + z}, {0.0f, -1.0f, 0.0f}},
          {{-w + x, y, -h + z}, {0.0f, -1.0f, 0.0f}}
        };
    }
  }
  else if constexpr (std::is_same<T, Vertex_texcoords>::value) {
    switch (face) {
      case Face::Front:
        return {
          // x, y, z, s, t
          // xy-plane
          {{-w + x, -h + y, z}, {0.0f, 0.0f}},
          {{ w + x, -h + y, z}, {1.0f, 0.0f}},
          {{ w + x,  h + y, z}, {1.0f, 1.0f}},
          {{ w + x,  h + y, z}, {1.0f, 1.0f}},
          {{-w + x,  h + y, z}, {0.0f, 1.0f}},
          {{-w + x, -h + y, z}, {0.0f, 0.0f}}
        };
      case Face::Back:
        return {
          // xy-plane
          {{ w + x, -h + y, z}, {0.0f, 0.0f}},
          {{-w + x, -h + y, z}, {1.0f, 0.0f}},
          {{-w + x,  h + y, z}, {1.0f, 1.0f}},
          {{-w + x,  h + y, z}, {1.0f, 1.0f}},
          {{ w + x,  h + y, z}, {0.0f, 1.0f}},
          {{ w + x, -h + y, z}, {0.0f, 0.0f}}
        };
      case Face::Left:
        return {
          // yz-plane
          {{x, -h + y, -w + z}, {0.0f, 0.0f}},
          {{x, -h + y,  w + z}, {1.0f, 0.0f}},
          {{x,  h + y,  w + z}, {1.0f, 1.0f}},
          {{x,  h + y,  w + z}, {1.0f, 1.0f}},
          {{x,  h + y, -w + z}, {0.0f, 1.0f}},
          {{x, -h + y, -w + z}, {0.0f, 0.0f}}
        };
      case Face::Right:
        return {
          // yz-plane
          {{x, -h + y,  w + z}, {0.0f, 0.0f}},
          {{x, -h + y, -w + z}, {1.0f, 0.0f}},
          {{x,  h + y, -w + z}, {1.0f, 1.0f}},
          {{x,  h + y, -w + z}, {1.0f, 1.0f}},
          {{x,  h + y,  w + z}, {0.0f, 1.0f}},
          {{x, -h + y,  w + z}, {0.0f, 0.0f}}
        };
      case Face::Up:
        return {
          // xz-plane
          {{-w + x, y,  h + z}, {0.0f, 0.0f}},
          {{ w + x, y,  h + z}, {1.0f, 0.0f}},
          {{ w + x, y, -h + z}, {1.0f, 1.0f}},
          {{ w + x, y, -h + z}, {1.0f, 1.0f}},
          {{-w + x, y, -h + z}, {0.0f, 1.0f}},
          {{-w + x, y,  h + z}, {0.0f, 0.0f}}
        };
      case Face::Down:
        return {
          // xz-plane
          {{-w + x, y, -h + z}, {0.0f, 0.0f}},
          {{ w + x, y, -h + z}, {1.0f, 0.0f}},
          {{ w + x, y,  h + z}, {1.0f, 1.0f}},
          {{ w + x, y,  h + z}, {1.0f, 1.0f}},
          {{-w + x, y,  h + z}, {0.0f, 1.0f}},
          {{-w + x, y, -h + z}, {0.0f, 0.0f}}
        };
    }
  }
  else if constexpr (std::is_same<T, Vertex_normal_texcoords>::value) {
    switch (face) {
      case Face::Front:
        return {
          // x, y, z, nx, ny, nz, s, t
          // xy-plane
          {{-w + x, -h + y, z}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
          {{ w + x, -h + y, z}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
          {{ w + x,  h + y, z}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
          {{ w + x,  h + y, z}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
          {{-w + x,  h + y, z}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
          {{-w + x, -h + y, z}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}}
        };
      case Face::Back:
        return {
          // xy-plane
          {{ w + x, -h + y, z}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}},
          {{-w + x, -h + y, z}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}},
          {{-w + x,  h + y, z}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}},
          {{-w + x,  h + y, z}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}},
          {{ w + x,  h + y, z}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}},
          {{ w + x, -h + y, z}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}}
        };
      case Face::Left:
        return {
          // yz-plane
          {{x, -h + y, -w + z}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
          {{x, -h + y,  w + z}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
          {{x,  h + y,  w + z}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
          {{x,  h + y,  w + z}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
          {{x,  h + y, -w + z}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},
          {{x, -h + y, -w + z}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}}
        };
      case Face::Right:
        return {
          // yz-plane
          {{x, -h + y,  w + z}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
          {{x, -h + y, -w + z}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
          {{x,  h + y, -w + z}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
          {{x,  h + y, -w + z}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
          {{x,  h + y,  w + z}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},
          {{x, -h + y,  w + z}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}}
        };
      case Face::Up:
        return {
          // xz-plane
          {{-w + x, y,  h + z}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
          {{ w + x, y,  h + z}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
          {{ w + x, y, -h + z}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
          {{ w + x, y, -h + z}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
          {{-w + x, y, -h + z}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},
          {{-w + x, y,  h + z}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}}
        };
      case Face::Down:
        return {
          // xz-plane
          {{-w + x, y, -h + z}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}},
          {{ w + x, y, -h + z}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f}},
          {{ w + x, y,  h + z}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}},
          {{ w + x, y,  h + z}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}},
          {{-w + x, y,  h + z}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f}},
          {{-w + x, y, -h + z}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}}
        };
    }
  }

  return {};
}


template<typename T> std::vector<T> apeiron::engine::primitive::quad_vertices(float width,
    float height, const glm::vec4& color, Face face, const glm::vec3& position)
{
  const float x = position.x;
  const float y = position.y;
  const float z = position.z;

  const float w = width * 0.5f;
  const float h = height * 0.5f;

  const float r = color.r;
  const float g = color.g;
  const float b = color.b;
  const float a = color.a;

  if constexpr (std::is_same<T, Vertex>::value) {
    switch (face) {
      case Face::Front:
        return {
          // x, y, z, nx, ny, nz, s, t, r, g, b, a
          // xy-plane
          {{-w + x, -h + y, z}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, {r, g, b, a}},
          {{ w + x, -h + y, z}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}, {r, g, b, a}},
          {{ w + x,  h + y, z}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}, {r, g, b, a}},
          {{ w + x,  h + y, z}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}, {r, g, b, a}},
          {{-w + x,  h + y, z}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}, {r, g, b, a}},
          {{-w + x, -h + y, z}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, {r, g, b, a}}
        };
      case Face::Back:
        return {
          // xy-plane
          {{ w + x, -h + y, z}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}, {r, g, b, a}},
          {{-w + x, -h + y, z}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}, {r, g, b, a}},
          {{-w + x,  h + y, z}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}, {r, g, b, a}},
          {{-w + x,  h + y, z}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}, {r, g, b, a}},
          {{ w + x,  h + y, z}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}, {r, g, b, a}},
          {{ w + x, -h + y, z}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}, {r, g, b, a}}
        };
      case Face::Left:
        return {
          // yz-plane
          {{x, -h + y, -w + z}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}, {r, g, b, a}},
          {{x, -h + y,  w + z}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}, {r, g, b, a}},
          {{x,  h + y,  w + z}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}, {r, g, b, a}},
          {{x,  h + y,  w + z}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}, {r, g, b, a}},
          {{x,  h + y, -w + z}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}, {r, g, b, a}},
          {{x, -h + y, -w + z}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}, {r, g, b, a}}
        };
      case Face::Right:
        return {
          // yz-plane
          {{x, -h + y,  w + z}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}, {r, g, b, a}},
          {{x, -h + y, -w + z}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}, {r, g, b, a}},
          {{x,  h + y, -w + z}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}, {r, g, b, a}},
          {{x,  h + y, -w + z}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}, {r, g, b, a}},
          {{x,  h + y,  w + z}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}, {r, g, b, a}},
          {{x, -h + y,  w + z}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}, {r, g, b, a}}
        };
      case Face::Up:
        return {
          // xz-plane
          {{-w + x, y,  h + z}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}, {r, g, b, a}},
          {{ w + x, y,  h + z}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}, {r, g, b, a}},
          {{ w + x, y, -h + z}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}, {r, g, b, a}},
          {{ w + x, y, -h + z}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}, {r, g, b, a}},
          {{-w + x, y, -h + z}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}, {r, g, b, a}},
          {{-w + x, y,  h + z}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}, {r, g, b, a}}
        };
      case Face::Down:
        return {
          // xz-plane
          {{-w + x, y, -h + z}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}, {r, g, b, a}},
          {{ w + x, y, -h + z}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f}, {r, g, b, a}},
          {{ w + x, y,  h + z}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}, {r, g, b, a}},
          {{ w + x, y,  h + z}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}, {r, g, b, a}},
          {{-w + x, y,  h + z}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f}, {r, g, b, a}},
          {{-w + x, y, -h + z}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}, {r, g, b, a}}
        };
    }
  }
  else if constexpr (std::is_same<T, Vertex_color>::value) {
    switch (face) {
      case Face::Front:
        return {
          // x, y, z, r, g, b, a
          // xy-plane
          {{-w + x, -h + y, z}, {r, g, b, a}},
          {{ w + x, -h + y, z}, {r, g, b, a}},
          {{ w + x,  h + y, z}, {r, g, b, a}},
          {{ w + x,  h + y, z}, {r, g, b, a}},
          {{-w + x,  h + y, z}, {r, g, b, a}},
          {{-w + x, -h + y, z}, {r, g, b, a}}
        };
      case Face::Back:
        return {
          // xy-plane
          {{ w + x, -h + y, z}, {r, g, b, a}},
          {{-w + x, -h + y, z}, {r, g, b, a}},
          {{-w + x,  h + y, z}, {r, g, b, a}},
          {{-w + x,  h + y, z}, {r, g, b, a}},
          {{ w + x,  h + y, z}, {r, g, b, a}},
          {{ w + x, -h + y, z}, {r, g, b, a}}
        };
      case Face::Left:
        return {
          // yz-plane
          {{x, -h + y, -w + z}, {r, g, b, a}},
          {{x, -h + y,  w + z}, {r, g, b, a}},
          {{x,  h + y,  w + z}, {r, g, b, a}},
          {{x,  h + y,  w + z}, {r, g, b, a}},
          {{x,  h + y, -w + z}, {r, g, b, a}},
          {{x, -h + y, -w + z}, {r, g, b, a}}
        };
      case Face::Right:
        return {
          // yz-plane
          {{x, -h + y,  w + z}, {r, g, b, a}},
          {{x, -h + y, -w + z}, {r, g, b, a}},
          {{x,  h + y, -w + z}, {r, g, b, a}},
          {{x,  h + y, -w + z}, {r, g, b, a}},
          {{x,  h + y,  w + z}, {r, g, b, a}},
          {{x, -h + y,  w + z}, {r, g, b, a}}
        };
      case Face::Up:
        return {
          // xz-plane
          {{-w + x, y,  h + z}, {r, g, b, a}},
          {{ w + x, y,  h + z}, {r, g, b, a}},
          {{ w + x, y, -h + z}, {r, g, b, a}},
          {{ w + x, y, -h + z}, {r, g, b, a}},
          {{-w + x, y, -h + z}, {r, g, b, a}},
          {{-w + x, y,  h + z}, {r, g, b, a}}
        };
      case Face::Down:
        return {
          // xz-plane
          {{-w + x, y, -h + z}, {r, g, b, a}},
          {{ w + x, y, -h + z}, {r, g, b, a}},
          {{ w + x, y,  h + z}, {r, g, b, a}},
          {{ w + x, y,  h + z}, {r, g, b, a}},
          {{-w + x, y,  h + z}, {r, g, b, a}},
          {{-w + x, y, -h + z}, {r, g, b, a}}
        };
    }
  }
  else if constexpr (std::is_same<T, Vertex_normal_color>::value) {
    switch (face) {
      case Face::Front:
        return {
          // x, y, z, nx, ny, nz, r, g, b, a
          // xy-plane
          {{-w + x, -h + y, z}, {0.0f, 0.0f, 1.0f}, {r, g, b, a}},
          {{ w + x, -h + y, z}, {0.0f, 0.0f, 1.0f}, {r, g, b, a}},
          {{ w + x,  h + y, z}, {0.0f, 0.0f, 1.0f}, {r, g, b, a}},
          {{ w + x,  h + y, z}, {0.0f, 0.0f, 1.0f}, {r, g, b, a}},
          {{-w + x,  h + y, z}, {0.0f, 0.0f, 1.0f}, {r, g, b, a}},
          {{-w + x, -h + y, z}, {0.0f, 0.0f, 1.0f}, {r, g, b, a}}
        };
      case Face::Back:
        return {
          // xy-plane
          {{ w + x, -h + y, z}, {0.0f, 0.0f, -1.0f}, {r, g, b, a}},
          {{-w + x, -h + y, z}, {0.0f, 0.0f, -1.0f}, {r, g, b, a}},
          {{-w + x,  h + y, z}, {0.0f, 0.0f, -1.0f}, {r, g, b, a}},
          {{-w + x,  h + y, z}, {0.0f, 0.0f, -1.0f}, {r, g, b, a}},
          {{ w + x,  h + y, z}, {0.0f, 0.0f, -1.0f}, {r, g, b, a}},
          {{ w + x, -h + y, z}, {0.0f, 0.0f, -1.0f}, {r, g, b, a}}
        };
      case Face::Left:
        return {
          // yz-plane
          {{x, -h + y, -w + z}, {-1.0f, 0.0f, 0.0f}, {r, g, b, a}},
          {{x, -h + y,  w + z}, {-1.0f, 0.0f, 0.0f}, {r, g, b, a}},
          {{x,  h + y,  w + z}, {-1.0f, 0.0f, 0.0f}, {r, g, b, a}},
          {{x,  h + y,  w + z}, {-1.0f, 0.0f, 0.0f}, {r, g, b, a}},
          {{x,  h + y, -w + z}, {-1.0f, 0.0f, 0.0f}, {r, g, b, a}},
          {{x, -h + y, -w + z}, {-1.0f, 0.0f, 0.0f}, {r, g, b, a}}
        };
      case Face::Right:
        return {
          // yz-plane
          {{x, -h + y,  w + z}, {1.0f, 0.0f, 0.0f}, {r, g, b, a}},
          {{x, -h + y, -w + z}, {1.0f, 0.0f, 0.0f}, {r, g, b, a}},
          {{x,  h + y, -w + z}, {1.0f, 0.0f, 0.0f}, {r, g, b, a}},
          {{x,  h + y, -w + z}, {1.0f, 0.0f, 0.0f}, {r, g, b, a}},
          {{x,  h + y,  w + z}, {1.0f, 0.0f, 0.0f}, {r, g, b, a}},
          {{x, -h + y,  w + z}, {1.0f, 0.0f, 0.0f}, {r, g, b, a}}
        };
      case Face::Up:
        return {
          // xz-plane
          {{-w + x, y,  h + z}, {0.0f, 1.0f, 0.0f}, {r, g, b, a}},
          {{ w + x, y,  h + z}, {0.0f, 1.0f, 0.0f}, {r, g, b, a}},
          {{ w + x, y, -h + z}, {0.0f, 1.0f, 0.0f}, {r, g, b, a}},
          {{ w + x, y, -h + z}, {0.0f, 1.0f, 0.0f}, {r, g, b, a}},
          {{-w + x, y, -h + z}, {0.0f, 1.0f, 0.0f}, {r, g, b, a}},
          {{-w + x, y,  h + z}, {0.0f, 1.0f, 0.0f}, {r, g, b, a}}
        };
      case Face::Down:
        return {
          // xz-plane
          {{-w + x, y, -h + z}, {0.0f, -1.0f, 0.0f}, {r, g, b, a}},
          {{ w + x, y, -h + z}, {0.0f, -1.0f, 0.0f}, {r, g, b, a}},
          {{ w + x, y,  h + z}, {0.0f, -1.0f, 0.0f}, {r, g, b, a}},
          {{ w + x, y,  h + z}, {0.0f, -1.0f, 0.0f}, {r, g, b, a}},
          {{-w + x, y,  h + z}, {0.0f, -1.0f, 0.0f}, {r, g, b, a}},
          {{-w + x, y, -h + z}, {0.0f, -1.0f, 0.0f}, {r, g, b, a}}
        };
    }
  }

  return {};
}


template<typename T> std::vector<T> apeiron::engine::primitive::quad_vertices(float width,
    float height, const glm::mat4& color, Face face, const glm::vec3& position)
{
  const float x = position.x;
  const float y = position.y;
  const float z = position.z;

  const float w = width * 0.5f;
  const float h = height * 0.5f;

  const float r = glm::column(color, 0).r;
  const float g = glm::column(color, 0).g;
  const float b = glm::column(color, 0).b;
  const float a = glm::column(color, 0).a;

  if constexpr (std::is_same<T, Vertex>::value) {
    switch (face) {
      case Face::Front:
        return {
          // x, y, z, nx, ny, nz, s, t, r, g, b, a
          // xy-plane
          {{-w + x, -h + y, z}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, glm::column(color, 0)},  // Top left
          {{ w + x, -h + y, z}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}, glm::column(color, 1)},  // Top right
          {{ w + x,  h + y, z}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}, glm::column(color, 2)},  // Bottom right
          {{ w + x,  h + y, z}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}, glm::column(color, 2)},  // Bottom right
          {{-w + x,  h + y, z}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}, glm::column(color, 3)},  // Bottom left
          {{-w + x, -h + y, z}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, glm::column(color, 0)}  // Top left
        };
      case Face::Back:
        return {
          // xy-plane
          {{ w + x, -h + y, z}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}, {r, g, b, a}},
          {{-w + x, -h + y, z}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}, {r, g, b, a}},
          {{-w + x,  h + y, z}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}, {r, g, b, a}},
          {{-w + x,  h + y, z}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}, {r, g, b, a}},
          {{ w + x,  h + y, z}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}, {r, g, b, a}},
          {{ w + x, -h + y, z}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}, {r, g, b, a}}
        };
      case Face::Left:
        return {
          // yz-plane
          {{x, -h + y, -w + z}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}, {r, g, b, a}},
          {{x, -h + y,  w + z}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}, {r, g, b, a}},
          {{x,  h + y,  w + z}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}, {r, g, b, a}},
          {{x,  h + y,  w + z}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}, {r, g, b, a}},
          {{x,  h + y, -w + z}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}, {r, g, b, a}},
          {{x, -h + y, -w + z}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}, {r, g, b, a}}
        };
      case Face::Right:
        return {
          // yz-plane
          {{x, -h + y,  w + z}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}, {r, g, b, a}},
          {{x, -h + y, -w + z}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}, {r, g, b, a}},
          {{x,  h + y, -w + z}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}, {r, g, b, a}},
          {{x,  h + y, -w + z}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}, {r, g, b, a}},
          {{x,  h + y,  w + z}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}, {r, g, b, a}},
          {{x, -h + y,  w + z}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}, {r, g, b, a}}
        };
      case Face::Up:
        return {
          // xz-plane
          {{-w + x, y,  h + z}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}, {r, g, b, a}},
          {{ w + x, y,  h + z}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}, {r, g, b, a}},
          {{ w + x, y, -h + z}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}, {r, g, b, a}},
          {{ w + x, y, -h + z}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}, {r, g, b, a}},
          {{-w + x, y, -h + z}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}, {r, g, b, a}},
          {{-w + x, y,  h + z}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}, {r, g, b, a}}
        };
      case Face::Down:
        return {
          // xz-plane
          {{-w + x, y, -h + z}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}, {r, g, b, a}},
          {{ w + x, y, -h + z}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f}, {r, g, b, a}},
          {{ w + x, y,  h + z}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}, {r, g, b, a}},
          {{ w + x, y,  h + z}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}, {r, g, b, a}},
          {{-w + x, y,  h + z}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f}, {r, g, b, a}},
          {{-w + x, y, -h + z}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}, {r, g, b, a}}
        };
    }
  }
  else if constexpr (std::is_same<T, Vertex_color>::value) {
    switch (face) {
      case Face::Front:
        return {
          // x, y, z, r, g, b, a
          // xy-plane
          {{-w + x, -h + y, z}, {r, g, b, a}},
          {{ w + x, -h + y, z}, {r, g, b, a}},
          {{ w + x,  h + y, z}, {r, g, b, a}},
          {{ w + x,  h + y, z}, {r, g, b, a}},
          {{-w + x,  h + y, z}, {r, g, b, a}},
          {{-w + x, -h + y, z}, {r, g, b, a}}
        };
      case Face::Back:
        return {
          // xy-plane
          {{ w + x, -h + y, z}, {r, g, b, a}},
          {{-w + x, -h + y, z}, {r, g, b, a}},
          {{-w + x,  h + y, z}, {r, g, b, a}},
          {{-w + x,  h + y, z}, {r, g, b, a}},
          {{ w + x,  h + y, z}, {r, g, b, a}},
          {{ w + x, -h + y, z}, {r, g, b, a}}
        };
      case Face::Left:
        return {
          // yz-plane
          {{x, -h + y, -w + z}, {r, g, b, a}},
          {{x, -h + y,  w + z}, {r, g, b, a}},
          {{x,  h + y,  w + z}, {r, g, b, a}},
          {{x,  h + y,  w + z}, {r, g, b, a}},
          {{x,  h + y, -w + z}, {r, g, b, a}},
          {{x, -h + y, -w + z}, {r, g, b, a}}
        };
      case Face::Right:
        return {
          // yz-plane
          {{x, -h + y,  w + z}, {r, g, b, a}},
          {{x, -h + y, -w + z}, {r, g, b, a}},
          {{x,  h + y, -w + z}, {r, g, b, a}},
          {{x,  h + y, -w + z}, {r, g, b, a}},
          {{x,  h + y,  w + z}, {r, g, b, a}},
          {{x, -h + y,  w + z}, {r, g, b, a}}
        };
      case Face::Up:
        return {
          // xz-plane
          {{-w + x, y,  h + z}, {r, g, b, a}},
          {{ w + x, y,  h + z}, {r, g, b, a}},
          {{ w + x, y, -h + z}, {r, g, b, a}},
          {{ w + x, y, -h + z}, {r, g, b, a}},
          {{-w + x, y, -h + z}, {r, g, b, a}},
          {{-w + x, y,  h + z}, {r, g, b, a}}
        };
      case Face::Down:
        return {
          // xz-plane
          {{-w + x, y, -h + z}, {r, g, b, a}},
          {{ w + x, y, -h + z}, {r, g, b, a}},
          {{ w + x, y,  h + z}, {r, g, b, a}},
          {{ w + x, y,  h + z}, {r, g, b, a}},
          {{-w + x, y,  h + z}, {r, g, b, a}},
          {{-w + x, y, -h + z}, {r, g, b, a}}
        };
    }
  }
  else if constexpr (std::is_same<T, Vertex_normal_color>::value) {
    switch (face) {
      case Face::Front:
        return {
          // x, y, z, nx, ny, nz, r, g, b, a
          // xy-plane
          {{-w + x, -h + y, z}, {0.0f, 0.0f, 1.0f}, {r, g, b, a}},
          {{ w + x, -h + y, z}, {0.0f, 0.0f, 1.0f}, {r, g, b, a}},
          {{ w + x,  h + y, z}, {0.0f, 0.0f, 1.0f}, {r, g, b, a}},
          {{ w + x,  h + y, z}, {0.0f, 0.0f, 1.0f}, {r, g, b, a}},
          {{-w + x,  h + y, z}, {0.0f, 0.0f, 1.0f}, {r, g, b, a}},
          {{-w + x, -h + y, z}, {0.0f, 0.0f, 1.0f}, {r, g, b, a}}
        };
      case Face::Back:
        return {
          // xy-plane
          {{ w + x, -h + y, z}, {0.0f, 0.0f, -1.0f}, {r, g, b, a}},
          {{-w + x, -h + y, z}, {0.0f, 0.0f, -1.0f}, {r, g, b, a}},
          {{-w + x,  h + y, z}, {0.0f, 0.0f, -1.0f}, {r, g, b, a}},
          {{-w + x,  h + y, z}, {0.0f, 0.0f, -1.0f}, {r, g, b, a}},
          {{ w + x,  h + y, z}, {0.0f, 0.0f, -1.0f}, {r, g, b, a}},
          {{ w + x, -h + y, z}, {0.0f, 0.0f, -1.0f}, {r, g, b, a}}
        };
      case Face::Left:
        return {
          // yz-plane
          {{x, -h + y, -w + z}, {-1.0f, 0.0f, 0.0f}, {r, g, b, a}},
          {{x, -h + y,  w + z}, {-1.0f, 0.0f, 0.0f}, {r, g, b, a}},
          {{x,  h + y,  w + z}, {-1.0f, 0.0f, 0.0f}, {r, g, b, a}},
          {{x,  h + y,  w + z}, {-1.0f, 0.0f, 0.0f}, {r, g, b, a}},
          {{x,  h + y, -w + z}, {-1.0f, 0.0f, 0.0f}, {r, g, b, a}},
          {{x, -h + y, -w + z}, {-1.0f, 0.0f, 0.0f}, {r, g, b, a}}
        };
      case Face::Right:
        return {
          // yz-plane
          {{x, -h + y,  w + z}, {1.0f, 0.0f, 0.0f}, {r, g, b, a}},
          {{x, -h + y, -w + z}, {1.0f, 0.0f, 0.0f}, {r, g, b, a}},
          {{x,  h + y, -w + z}, {1.0f, 0.0f, 0.0f}, {r, g, b, a}},
          {{x,  h + y, -w + z}, {1.0f, 0.0f, 0.0f}, {r, g, b, a}},
          {{x,  h + y,  w + z}, {1.0f, 0.0f, 0.0f}, {r, g, b, a}},
          {{x, -h + y,  w + z}, {1.0f, 0.0f, 0.0f}, {r, g, b, a}}
        };
      case Face::Up:
        return {
          // xz-plane
          {{-w + x, y,  h + z}, {0.0f, 1.0f, 0.0f}, {r, g, b, a}},
          {{ w + x, y,  h + z}, {0.0f, 1.0f, 0.0f}, {r, g, b, a}},
          {{ w + x, y, -h + z}, {0.0f, 1.0f, 0.0f}, {r, g, b, a}},
          {{ w + x, y, -h + z}, {0.0f, 1.0f, 0.0f}, {r, g, b, a}},
          {{-w + x, y, -h + z}, {0.0f, 1.0f, 0.0f}, {r, g, b, a}},
          {{-w + x, y,  h + z}, {0.0f, 1.0f, 0.0f}, {r, g, b, a}}
        };
      case Face::Down:
        return {
          // xz-plane
          {{-w + x, y, -h + z}, {0.0f, -1.0f, 0.0f}, {r, g, b, a}},
          {{ w + x, y, -h + z}, {0.0f, -1.0f, 0.0f}, {r, g, b, a}},
          {{ w + x, y,  h + z}, {0.0f, -1.0f, 0.0f}, {r, g, b, a}},
          {{ w + x, y,  h + z}, {0.0f, -1.0f, 0.0f}, {r, g, b, a}},
          {{-w + x, y,  h + z}, {0.0f, -1.0f, 0.0f}, {r, g, b, a}},
          {{-w + x, y, -h + z}, {0.0f, -1.0f, 0.0f}, {r, g, b, a}}
        };
    }
  }

  return {};
}


template<typename T> std::vector<T> apeiron::engine::primitive::cuboid_vertices(const glm::vec3& size,
    const glm::vec3& position)
{
  const float x = position.x;
  const float y = position.y;
  const float z = position.z;

  const float w = size.x * 0.5f;
  const float h = size.y * 0.5f;
  const float l = size.z * 0.5f;

  if constexpr (std::is_same<T, Vertex>::value) {
    return {
      {
        // x, y, z, nx, ny, nz, s, t, r, g, b, a
        // Front (xy-plane)
        {{-w + x, -h + y, l + z}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
        {{ w + x, -h + y, l + z}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
        {{ w + x,  h + y, l + z}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
        {{ w + x,  h + y, l + z}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
        {{-w + x,  h + y, l + z}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
        {{-w + x, -h + y, l + z}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
        // Back (xy-plane)
        {{ w + x, -h + y, -l + z}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
        {{-w + x, -h + y, -l + z}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
        {{-w + x,  h + y, -l + z}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
        {{-w + x,  h + y, -l + z}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
        {{ w + x,  h + y, -l + z}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
        {{ w + x, -h + y, -l + z}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
        // Left (yz-plane)
        {{-w + x, -h + y, -l + z}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
        {{-w + x, -h + y,  l + z}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
        {{-w + x,  h + y,  l + z}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
        {{-w + x,  h + y,  l + z}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
        {{-w + x,  h + y, -l + z}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
        {{-w + x, -h + y, -l + z}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
        // Right (yz-plane)
        {{w + x, -h + y,  l + z}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
        {{w + x, -h + y, -l + z}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
        {{w + x,  h + y, -l + z}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
        {{w + x,  h + y, -l + z}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
        {{w + x,  h + y,  l + z}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
        {{w + x, -h + y,  l + z}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
        // Top (xz-plane)
        {{-w + x, h + y,  l + z}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
        {{ w + x, h + y,  l + z}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
        {{ w + x, h + y, -l + z}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
        {{ w + x, h + y, -l + z}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
        {{-w + x, h + y, -l + z}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
        {{-w + x, h + y,  l + z}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
        // Bottom (xz-plane)
        {{-w + x, -h + y, -l + z}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
        {{ w + x, -h + y, -l + z}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
        {{ w + x, -h + y,  l + z}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
        {{ w + x, -h + y,  l + z}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
        {{-w + x, -h + y,  l + z}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
        {{-w + x, -h + y, -l + z}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}}
      }
    };
  }
  else if constexpr (std::is_same<T, Vertex_simple>::value) {
    return {
      {
        // x, y, z
        // Front (xy-plane)
        {{-w + x, -h + y, l + z}},
        {{ w + x, -h + y, l + z}},
        {{ w + x,  h + y, l + z}},
        {{ w + x,  h + y, l + z}},
        {{-w + x,  h + y, l + z}},
        {{-w + x, -h + y, l + z}},
        // Back (xy-plane)
        {{ w + x, -h + y, -l + z}},
        {{-w + x, -h + y, -l + z}},
        {{-w + x,  h + y, -l + z}},
        {{-w + x,  h + y, -l + z}},
        {{ w + x,  h + y, -l + z}},
        {{ w + x, -h + y, -l + z}},
        // Left (yz-plane)
        {{-w + x, -h + y, -l + z}},
        {{-w + x, -h + y,  l + z}},
        {{-w + x,  h + y,  l + z}},
        {{-w + x,  h + y,  l + z}},
        {{-w + x,  h + y, -l + z}},
        {{-w + x, -h + y, -l + z}},
        // Right (yz-plane)
        {{w + x, -h + y,  l + z}},
        {{w + x, -h + y, -l + z}},
        {{w + x,  h + y, -l + z}},
        {{w + x,  h + y, -l + z}},
        {{w + x,  h + y,  l + z}},
        {{w + x, -h + y,  l + z}},
        // Top (xz-plane)
        {{-w + x, h + y,  l + z}},
        {{ w + x, h + y,  l + z}},
        {{ w + x, h + y, -l + z}},
        {{ w + x, h + y, -l + z}},
        {{-w + x, h + y, -l + z}},
        {{-w + x, h + y,  l + z}},
        // Bottom (xz-plane)
        {{-w + x, -h + y, -l + z}},
        {{ w + x, -h + y, -l + z}},
        {{ w + x, -h + y,  l + z}},
        {{ w + x, -h + y,  l + z}},
        {{-w + x, -h + y,  l + z}},
        {{-w + x, -h + y, -l + z}}
      }
    };
  }
  else if constexpr (std::is_same<T, Vertex_normal>::value) {
    return {
      {
        // x, y, z, nx, ny, nz
        // Front (xy-plane)
        {{-w + x, -h + y, l + z}, {0.0f, 0.0f, 1.0f}},
        {{ w + x, -h + y, l + z}, {0.0f, 0.0f, 1.0f}},
        {{ w + x,  h + y, l + z}, {0.0f, 0.0f, 1.0f}},
        {{ w + x,  h + y, l + z}, {0.0f, 0.0f, 1.0f}},
        {{-w + x,  h + y, l + z}, {0.0f, 0.0f, 1.0f}},
        {{-w + x, -h + y, l + z}, {0.0f, 0.0f, 1.0f}},
        // Back (xy-plane)
        {{ w + x, -h + y, -l + z}, {0.0f, 0.0f, -1.0f}},
        {{-w + x, -h + y, -l + z}, {0.0f, 0.0f, -1.0f}},
        {{-w + x,  h + y, -l + z}, {0.0f, 0.0f, -1.0f}},
        {{-w + x,  h + y, -l + z}, {0.0f, 0.0f, -1.0f}},
        {{ w + x,  h + y, -l + z}, {0.0f, 0.0f, -1.0f}},
        {{ w + x, -h + y, -l + z}, {0.0f, 0.0f, -1.0f}},
        // Left (yz-plane)
        {{-w + x, -h + y, -l + z}, {-1.0f, 0.0f, 0.0f}},
        {{-w + x, -h + y,  l + z}, {-1.0f, 0.0f, 0.0f}},
        {{-w + x,  h + y,  l + z}, {-1.0f, 0.0f, 0.0f}},
        {{-w + x,  h + y,  l + z}, {-1.0f, 0.0f, 0.0f}},
        {{-w + x,  h + y, -l + z}, {-1.0f, 0.0f, 0.0f}},
        {{-w + x, -h + y, -l + z}, {-1.0f, 0.0f, 0.0f}},
        // Right (yz-plane)
        {{w + x, -h + y,  l + z}, {1.0f, 0.0f, 0.0f}},
        {{w + x, -h + y, -l + z}, {1.0f, 0.0f, 0.0f}},
        {{w + x,  h + y, -l + z}, {1.0f, 0.0f, 0.0f}},
        {{w + x,  h + y, -l + z}, {1.0f, 0.0f, 0.0f}},
        {{w + x,  h + y,  l + z}, {1.0f, 0.0f, 0.0f}},
        {{w + x, -h + y,  l + z}, {1.0f, 0.0f, 0.0f}},
        // Top (xz-plane)
        {{-w + x, h + y,  l + z}, {0.0f, 1.0f, 0.0f}},
        {{ w + x, h + y,  l + z}, {0.0f, 1.0f, 0.0f}},
        {{ w + x, h + y, -l + z}, {0.0f, 1.0f, 0.0f}},
        {{ w + x, h + y, -l + z}, {0.0f, 1.0f, 0.0f}},
        {{-w + x, h + y, -l + z}, {0.0f, 1.0f, 0.0f}},
        {{-w + x, h + y,  l + z}, {0.0f, 1.0f, 0.0f}},
        // Bottom (xz-plane)
        {{-w + x, -h + y, -l + z}, {0.0f, -1.0f, 0.0f}},
        {{ w + x, -h + y, -l + z}, {0.0f, -1.0f, 0.0f}},
        {{ w + x, -h + y,  l + z}, {0.0f, -1.0f, 0.0f}},
        {{ w + x, -h + y,  l + z}, {0.0f, -1.0f, 0.0f}},
        {{-w + x, -h + y,  l + z}, {0.0f, -1.0f, 0.0f}},
        {{-w + x, -h + y, -l + z}, {0.0f, -1.0f, 0.0f}}
      }
    };
  }
  else if constexpr (std::is_same<T, Vertex_texcoords>::value) {
    return {
      {
        // x, y, z, s, t
        // Front (xy-plane)
        {{-w + x, -h + y, l + z}, {0.0f, 0.0f}},
        {{ w + x, -h + y, l + z}, {1.0f, 0.0f}},
        {{ w + x,  h + y, l + z}, {1.0f, 1.0f}},
        {{ w + x,  h + y, l + z}, {1.0f, 1.0f}},
        {{-w + x,  h + y, l + z}, {0.0f, 1.0f}},
        {{-w + x, -h + y, l + z}, {0.0f, 0.0f}},
        // Back (xy-plane)
        {{ w + x, -h + y, -l + z}, {0.0f, 0.0f}},
        {{-w + x, -h + y, -l + z}, {1.0f, 0.0f}},
        {{-w + x,  h + y, -l + z}, {1.0f, 1.0f}},
        {{-w + x,  h + y, -l + z}, {1.0f, 1.0f}},
        {{ w + x,  h + y, -l + z}, {0.0f, 1.0f}},
        {{ w + x, -h + y, -l + z}, {0.0f, 0.0f}},
        // Left (yz-plane)
        {{-w + x, -h + y, -l + z}, {0.0f, 0.0f}},
        {{-w + x, -h + y,  l + z}, {1.0f, 0.0f}},
        {{-w + x,  h + y,  l + z}, {1.0f, 1.0f}},
        {{-w + x,  h + y,  l + z}, {1.0f, 1.0f}},
        {{-w + x,  h + y, -l + z}, {0.0f, 1.0f}},
        {{-w + x, -h + y, -l + z}, {0.0f, 0.0f}},
        // Right (yz-plane)
        {{w + x, -h + y,  l + z}, {0.0f, 0.0f}},
        {{w + x, -h + y, -l + z}, {1.0f, 0.0f}},
        {{w + x,  h + y, -l + z}, {1.0f, 1.0f}},
        {{w + x,  h + y, -l + z}, {1.0f, 1.0f}},
        {{w + x,  h + y,  l + z}, {0.0f, 1.0f}},
        {{w + x, -h + y,  l + z}, {0.0f, 0.0f}},
        // Top (xz-plane)
        {{-w + x, h + y,  l + z}, {0.0f, 0.0f}},
        {{ w + x, h + y,  l + z}, {1.0f, 0.0f}},
        {{ w + x, h + y, -l + z}, {1.0f, 1.0f}},
        {{ w + x, h + y, -l + z}, {1.0f, 1.0f}},
        {{-w + x, h + y, -l + z}, {0.0f, 1.0f}},
        {{-w + x, h + y,  l + z}, {0.0f, 0.0f}},
        // Bottom (xz-plane)
        {{-w + x, -h + y, -l + z}, {0.0f, 0.0f}},
        {{ w + x, -h + y, -l + z}, {1.0f, 0.0f}},
        {{ w + x, -h + y,  l + z}, {1.0f, 1.0f}},
        {{ w + x, -h + y,  l + z}, {1.0f, 1.0f}},
        {{-w + x, -h + y,  l + z}, {0.0f, 1.0f}},
        {{-w + x, -h + y, -l + z}, {0.0f, 0.0f}}
      }
    };
  }
  else if constexpr (std::is_same<T, Vertex_normal_texcoords>::value) {
    return {
      {
        // x, y, z, nx, ny, nz, s, t
        // Front (xy-plane)
        {{-w + x, -h + y, l + z}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
        {{ w + x, -h + y, l + z}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
        {{ w + x,  h + y, l + z}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
        {{ w + x,  h + y, l + z}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
        {{-w + x,  h + y, l + z}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
        {{-w + x, -h + y, l + z}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
        // Back (xy-plane)
        {{ w + x, -h + y, -l + z}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}},
        {{-w + x, -h + y, -l + z}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}},
        {{-w + x,  h + y, -l + z}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}},
        {{-w + x,  h + y, -l + z}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}},
        {{ w + x,  h + y, -l + z}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}},
        {{ w + x, -h + y, -l + z}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}},
        // Left (yz-plane)
        {{-w + x, -h + y, -l + z}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        {{-w + x, -h + y,  l + z}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
        {{-w + x,  h + y,  l + z}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
        {{-w + x,  h + y,  l + z}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
        {{-w + x,  h + y, -l + z}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},
        {{-w + x, -h + y, -l + z}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        // Right (yz-plane)
        {{w + x, -h + y,  l + z}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        {{w + x, -h + y, -l + z}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
        {{w + x,  h + y, -l + z}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
        {{w + x,  h + y, -l + z}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
        {{w + x,  h + y,  l + z}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},
        {{w + x, -h + y,  l + z}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        // Top (xz-plane)
        {{-w + x, h + y,  l + z}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
        {{ w + x, h + y,  l + z}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
        {{ w + x, h + y, -l + z}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
        {{ w + x, h + y, -l + z}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
        {{-w + x, h + y, -l + z}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},
        {{-w + x, h + y,  l + z}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
        // Bottom (xz-plane)
        {{-w + x, -h + y, -l + z}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}},
        {{ w + x, -h + y, -l + z}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f}},
        {{ w + x, -h + y,  l + z}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}},
        {{ w + x, -h + y,  l + z}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}},
        {{-w + x, -h + y,  l + z}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f}},
        {{-w + x, -h + y, -l + z}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}}
      }
    };
  }

  return {};
}


template<typename T> std::vector<T> apeiron::engine::primitive::cuboid_vertices(
    const glm::vec3& size, const glm::vec4& color, const glm::vec3& position)
{
  const float x = position.x;
  const float y = position.y;
  const float z = position.z;

  const float w = size.x * 0.5f;
  const float h = size.y * 0.5f;
  const float l = size.z * 0.5f;

  const float r = color.r;
  const float g = color.g;
  const float b = color.b;
  const float a = color.a;

  if constexpr (std::is_same<T, Vertex>::value) {
    return {
      {
        // x, y, z, nx, ny, nz, s, t, r, g, b, a
        // Front (xy-plane)
        {{-w + x, -h + y, l + z}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, {r, g, b, a}},
        {{ w + x, -h + y, l + z}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}, {r, g, b, a}},
        {{ w + x,  h + y, l + z}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}, {r, g, b, a}},
        {{ w + x,  h + y, l + z}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}, {r, g, b, a}},
        {{-w + x,  h + y, l + z}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}, {r, g, b, a}},
        {{-w + x, -h + y, l + z}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, {r, g, b, a}},
        // Back (xy-plane)
        {{ w + x, -h + y, -l + z}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}, {r, g, b, a}},
        {{-w + x, -h + y, -l + z}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}, {r, g, b, a}},
        {{-w + x,  h + y, -l + z}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}, {r, g, b, a}},
        {{-w + x,  h + y, -l + z}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}, {r, g, b, a}},
        {{ w + x,  h + y, -l + z}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}, {r, g, b, a}},
        {{ w + x, -h + y, -l + z}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}, {r, g, b, a}},
        // Left (yz-plane)
        {{-w + x, -h + y, -l + z}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}, {r, g, b, a}},
        {{-w + x, -h + y,  l + z}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}, {r, g, b, a}},
        {{-w + x,  h + y,  l + z}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}, {r, g, b, a}},
        {{-w + x,  h + y,  l + z}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}, {r, g, b, a}},
        {{-w + x,  h + y, -l + z}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}, {r, g, b, a}},
        {{-w + x, -h + y, -l + z}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}, {r, g, b, a}},
        // Right (yz-plane)
        {{w + x, -h + y,  l + z}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}, {r, g, b, a}},
        {{w + x, -h + y, -l + z}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}, {r, g, b, a}},
        {{w + x,  h + y, -l + z}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}, {r, g, b, a}},
        {{w + x,  h + y, -l + z}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}, {r, g, b, a}},
        {{w + x,  h + y,  l + z}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}, {r, g, b, a}},
        {{w + x, -h + y,  l + z}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}, {r, g, b, a}},
        // Top (xz-plane)
        {{-w + x, h + y,  l + z}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}, {r, g, b, a}},
        {{ w + x, h + y,  l + z}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}, {r, g, b, a}},
        {{ w + x, h + y, -l + z}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}, {r, g, b, a}},
        {{ w + x, h + y, -l + z}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}, {r, g, b, a}},
        {{-w + x, h + y, -l + z}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}, {r, g, b, a}},
        {{-w + x, h + y,  l + z}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}, {r, g, b, a}},
        // Bottom (xz-plane)
        {{-w + x, -h + y, -l + z}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}, {r, g, b, a}},
        {{ w + x, -h + y, -l + z}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f}, {r, g, b, a}},
        {{ w + x, -h + y,  l + z}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}, {r, g, b, a}},
        {{ w + x, -h + y,  l + z}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}, {r, g, b, a}},
        {{-w + x, -h + y,  l + z}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f}, {r, g, b, a}},
        {{-w + x, -h + y, -l + z}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}, {r, g, b, a}}
      }
    };
  }
  else if constexpr (std::is_same<T, Vertex_color>::value) {
    return {
      {
        // x, y, z, r, g, b, a
        // Front (xy-plane)
        {{-w + x, -h + y, l + z}, {r, g, b, a}},
        {{ w + x, -h + y, l + z}, {r, g, b, a}},
        {{ w + x,  h + y, l + z}, {r, g, b, a}},
        {{ w + x,  h + y, l + z}, {r, g, b, a}},
        {{-w + x,  h + y, l + z}, {r, g, b, a}},
        {{-w + x, -h + y, l + z}, {r, g, b, a}},
        // Back (xy-plane)
        {{ w + x, -h + y, -l + z}, {r, g, b, a}},
        {{-w + x, -h + y, -l + z}, {r, g, b, a}},
        {{-w + x,  h + y, -l + z}, {r, g, b, a}},
        {{-w + x,  h + y, -l + z}, {r, g, b, a}},
        {{ w + x,  h + y, -l + z}, {r, g, b, a}},
        {{ w + x, -h + y, -l + z}, {r, g, b, a}},
        // Left (yz-plane)
        {{-w + x, -h + y, -l + z}, {r, g, b, a}},
        {{-w + x, -h + y,  l + z}, {r, g, b, a}},
        {{-w + x,  h + y,  l + z}, {r, g, b, a}},
        {{-w + x,  h + y,  l + z}, {r, g, b, a}},
        {{-w + x,  h + y, -l + z}, {r, g, b, a}},
        {{-w + x, -h + y, -l + z}, {r, g, b, a}},
        // Right (yz-plane)
        {{w + x, -h + y,  l + z}, {r, g, b, a}},
        {{w + x, -h + y, -l + z}, {r, g, b, a}},
        {{w + x,  h + y, -l + z}, {r, g, b, a}},
        {{w + x,  h + y, -l + z}, {r, g, b, a}},
        {{w + x,  h + y,  l + z}, {r, g, b, a}},
        {{w + x, -h + y,  l + z}, {r, g, b, a}},
        // Top (xz-plane)
        {{-w + x, h + y,  l + z}, {r, g, b, a}},
        {{ w + x, h + y,  l + z}, {r, g, b, a}},
        {{ w + x, h + y, -l + z}, {r, g, b, a}},
        {{ w + x, h + y, -l + z}, {r, g, b, a}},
        {{-w + x, h + y, -l + z}, {r, g, b, a}},
        {{-w + x, h + y,  l + z}, {r, g, b, a}},
        // Bottom (xz-plane)
        {{-w + x, -h + y, -l + z}, {r, g, b, a}},
        {{ w + x, -h + y, -l + z}, {r, g, b, a}},
        {{ w + x, -h + y,  l + z}, {r, g, b, a}},
        {{ w + x, -h + y,  l + z}, {r, g, b, a}},
        {{-w + x, -h + y,  l + z}, {r, g, b, a}},
        {{-w + x, -h + y, -l + z}, {r, g, b, a}}
      }
    };
  }
  else if constexpr (std::is_same<T, Vertex_normal_color>::value) {
    return {
      {
        // x, y, z, nx, ny, nz, r, g, b, a
        // Front (xy-plane)
        {{-w + x, -h + y, l + z}, {0.0f, 0.0f, 1.0f}, {r, g, b, a}},
        {{ w + x, -h + y, l + z}, {0.0f, 0.0f, 1.0f}, {r, g, b, a}},
        {{ w + x,  h + y, l + z}, {0.0f, 0.0f, 1.0f}, {r, g, b, a}},
        {{ w + x,  h + y, l + z}, {0.0f, 0.0f, 1.0f}, {r, g, b, a}},
        {{-w + x,  h + y, l + z}, {0.0f, 0.0f, 1.0f}, {r, g, b, a}},
        {{-w + x, -h + y, l + z}, {0.0f, 0.0f, 1.0f}, {r, g, b, a}},
        // Back (xy-plane)
        {{ w + x, -h + y, -l + z}, {0.0f, 0.0f, -1.0f}, {r, g, b, a}},
        {{-w + x, -h + y, -l + z}, {0.0f, 0.0f, -1.0f}, {r, g, b, a}},
        {{-w + x,  h + y, -l + z}, {0.0f, 0.0f, -1.0f}, {r, g, b, a}},
        {{-w + x,  h + y, -l + z}, {0.0f, 0.0f, -1.0f}, {r, g, b, a}},
        {{ w + x,  h + y, -l + z}, {0.0f, 0.0f, -1.0f}, {r, g, b, a}},
        {{ w + x, -h + y, -l + z}, {0.0f, 0.0f, -1.0f}, {r, g, b, a}},
        // Left (yz-plane)
        {{-w + x, -h + y, -l + z}, {-1.0f, 0.0f, 0.0f}, {r, g, b, a}},
        {{-w + x, -h + y,  l + z}, {-1.0f, 0.0f, 0.0f}, {r, g, b, a}},
        {{-w + x,  h + y,  l + z}, {-1.0f, 0.0f, 0.0f}, {r, g, b, a}},
        {{-w + x,  h + y,  l + z}, {-1.0f, 0.0f, 0.0f}, {r, g, b, a}},
        {{-w + x,  h + y, -l + z}, {-1.0f, 0.0f, 0.0f}, {r, g, b, a}},
        {{-w + x, -h + y, -l + z}, {-1.0f, 0.0f, 0.0f}, {r, g, b, a}},
        // Right (yz-plane)
        {{w + x, -h + y,  l + z}, {1.0f, 0.0f, 0.0f}, {r, g, b, a}},
        {{w + x, -h + y, -l + z}, {1.0f, 0.0f, 0.0f}, {r, g, b, a}},
        {{w + x,  h + y, -l + z}, {1.0f, 0.0f, 0.0f}, {r, g, b, a}},
        {{w + x,  h + y, -l + z}, {1.0f, 0.0f, 0.0f}, {r, g, b, a}},
        {{w + x,  h + y,  l + z}, {1.0f, 0.0f, 0.0f}, {r, g, b, a}},
        {{w + x, -h + y,  l + z}, {1.0f, 0.0f, 0.0f}, {r, g, b, a}},
        // Top (xz-plane)
        {{-w + x, h + y,  l + z}, {0.0f, 1.0f, 0.0f}, {r, g, b, a}},
        {{ w + x, h + y,  l + z}, {0.0f, 1.0f, 0.0f}, {r, g, b, a}},
        {{ w + x, h + y, -l + z}, {0.0f, 1.0f, 0.0f}, {r, g, b, a}},
        {{ w + x, h + y, -l + z}, {0.0f, 1.0f, 0.0f}, {r, g, b, a}},
        {{-w + x, h + y, -l + z}, {0.0f, 1.0f, 0.0f}, {r, g, b, a}},
        {{-w + x, h + y,  l + z}, {0.0f, 1.0f, 0.0f}, {r, g, b, a}},
        // Bottom (xz-plane)
        {{-w + x, -h + y, -l + z}, {0.0f, -1.0f, 0.0f}, {r, g, b, a}},
        {{ w + x, -h + y, -l + z}, {0.0f, -1.0f, 0.0f}, {r, g, b, a}},
        {{ w + x, -h + y,  l + z}, {0.0f, -1.0f, 0.0f}, {r, g, b, a}},
        {{ w + x, -h + y,  l + z}, {0.0f, -1.0f, 0.0f}, {r, g, b, a}},
        {{-w + x, -h + y,  l + z}, {0.0f, -1.0f, 0.0f}, {r, g, b, a}},
        {{-w + x, -h + y, -l + z}, {0.0f, -1.0f, 0.0f}, {r, g, b, a}}
      }
    };
  }
  
  return {};
}


template<typename T> std::vector<T> apeiron::engine::primitive::disk_vertices(float radius,
    int points, Face face, const glm::vec3& position)
{
  constexpr float pi = 3.141592f;
  constexpr float tau = 2.0f * pi;

  const float x = position.x;
  const float y = position.y;
  const float z = position.z;

  std::vector<glm::vec4> vertices;

  for (int i=0; i<=points; ++i) {
    const float angle = static_cast<float>(i) / points * tau;
    const float p1 = x + radius * std::cos(angle);
    const float p2 = y + radius * std::sin(angle);
    const float p3 = z + radius * std::sin(angle);
    const float p4 = y + radius * std::cos(angle);
    vertices.emplace_back(p1, p2, p3, p4);
  }

  std::vector<T> triangle_vertices;

  for (int i=1; i<=points; ++i) {
    switch (face) {
      case Face::Front:
      case Face::Back: {
        const auto& v1 = face == Face::Front ? vertices[i-1] : vertices[i];
        const auto& v2 = face == Face::Front ? vertices[i] : vertices[i-1];

        // Direction of normal
        float n = face == Face::Front ? 1.0f : -1.0f;

        if constexpr (std::is_same<T, Vertex>::value) {
          // x, y, z, nx, ny, nz, s, t, r, g, b, a (texcoords s and t are not provided and kept zero)
          triangle_vertices.emplace_back(v1.x, v1.y, z, 0.0f, 0.0f, n, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
          triangle_vertices.emplace_back(v2.x, v2.y, z, 0.0f, 0.0f, n, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
          triangle_vertices.emplace_back(x,       y, z, 0.0f, 0.0f, n, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
        }
        else if constexpr (std::is_same<T, Vertex_simple>::value) {
          // x, y, z
          triangle_vertices.emplace_back(v1.x, v1.y, z);
          triangle_vertices.emplace_back(v2.x, v2.y, z);
          triangle_vertices.emplace_back(x,       y, z);
        }
        else if constexpr (std::is_same<T, Vertex_normal>::value) {
          // x, y, z, nx, ny, nz
          triangle_vertices.emplace_back(v1.x, v1.y, z, 0.0f, 0.0f, n);
          triangle_vertices.emplace_back(v2.x, v2.y, z, 0.0f, 0.0f, n);
          triangle_vertices.emplace_back(x,       y, z, 0.0f, 0.0f, n);
        }
      }
      break;
      case Face::Up:
      case Face::Down: {
        const auto& v1 = face == Face::Down ? vertices[i-1] : vertices[i];
        const auto& v2 = face == Face::Down ? vertices[i] : vertices[i-1];

        // Direction of normal
        float n = face == Face::Up ? 1.0f : -1.0f;

        if constexpr (std::is_same<T, Vertex>::value) {
          // x, y, z, nx, ny, nz, s, t, r, g, b, a (texcoords s and t are not provided and kept zero)
          triangle_vertices.emplace_back(v1.x, y, v1.z, 0.0f, n, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
          triangle_vertices.emplace_back(v2.x, y, v2.z, 0.0f, n, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
          triangle_vertices.emplace_back(x,    y,    z, 0.0f, n, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
        }
        else if constexpr (std::is_same<T, Vertex_simple>::value) {
          // x, y, z
          triangle_vertices.emplace_back(v1.x, y, v1.z);
          triangle_vertices.emplace_back(v2.x, y, v2.z);
          triangle_vertices.emplace_back(x,    y,    z);
        }
        else if constexpr (std::is_same<T, Vertex_normal>::value) {
          // x, y, z, nx, ny, nz
          triangle_vertices.emplace_back(v1.x, y, v1.z, 0.0f, n, 0.0f);
          triangle_vertices.emplace_back(v2.x, y, v2.z, 0.0f, n, 0.0f);
          triangle_vertices.emplace_back(x,    y,    z, 0.0f, n, 0.0f);
        }
      }
      break;
      case Face::Left:
      case Face::Right: {
        const auto& v1 = face == Face::Left ? vertices[i] : vertices[i-1];
        const auto& v2 = face == Face::Left ? vertices[i-1] : vertices[i];

        // Direction of normal
        float n = face == Face::Right ? 1.0f : -1.0f;

        if constexpr (std::is_same<T, Vertex>::value) {
          // x, y, z, nx, ny, nz, s, t, r, g, b, a (texcoords s and t are not provided and kept zero)
          triangle_vertices.emplace_back(x, v1.w, v1.z, n, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
          triangle_vertices.emplace_back(x, v2.w, v2.z, n, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
          triangle_vertices.emplace_back(x,    y,    z, n, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
        }
        else if constexpr (std::is_same<T, Vertex_simple>::value) {
          // x, y, z
          triangle_vertices.emplace_back(x, v1.w, v1.z);
          triangle_vertices.emplace_back(x, v2.w, v2.z);
          triangle_vertices.emplace_back(x,    y,    z);
        }
        else if constexpr (std::is_same<T, Vertex_normal>::value) {
          // x, y, z, nx, ny, nz
          triangle_vertices.emplace_back(x, v1.w, v1.z, n, 0.0f, 0.0f);
          triangle_vertices.emplace_back(x, v2.w, v2.z, n, 0.0f, 0.0f);
          triangle_vertices.emplace_back(x,    y,    z, n, 0.0f, 0.0f);
        }
      }
      break;
    }
  }

  return triangle_vertices;
}


template<typename T> std::vector<T> apeiron::engine::primitive::disk_vertices(float radius,
    int points, const glm::vec4& color, Face face, const glm::vec3& position)
{
  constexpr float pi = 3.141592f;
  constexpr float tau = 2.0f * pi;

  const float x = position.x;
  const float y = position.y;
  const float z = position.z;

  const float r = color.r;
  const float g = color.g;
  const float b = color.b;
  const float a = color.a;

  std::vector<glm::vec4> vertices;

  for (int i=0; i<=points; ++i) {
    const float angle = static_cast<float>(i) / points * tau;
    const float p1 = x + radius * std::cos(angle);
    const float p2 = y + radius * std::sin(angle);
    const float p3 = z + radius * std::sin(angle);
    const float p4 = y + radius * std::cos(angle);
    vertices.emplace_back(p1, p2, p3, p4);
  }

  std::vector<T> triangle_vertices;

  for (int i=1; i<=points; ++i) {
    switch (face) {
      case Face::Front:
      case Face::Back: {
        const auto& v1 = face == Face::Front ? vertices[i-1] : vertices[i];
        const auto& v2 = face == Face::Front ? vertices[i] : vertices[i-1];

        // Direction of normal
        float n = face == Face::Front ? 1.0f : -1.0f;

        if constexpr (std::is_same<T, Vertex>::value) {
          // x, y, z, nx, ny, nz, s, t, r, g, b, a (texcoords s and t are not provided and kept zero)
          triangle_vertices.emplace_back(v1.x, v1.y, z, 0.0f, 0.0f, n, 0.0f, 0.0f, r, g, b, a);
          triangle_vertices.emplace_back(v2.x, v2.y, z, 0.0f, 0.0f, n, 0.0f, 0.0f, r, g, b, a);
          triangle_vertices.emplace_back(x,       y, z, 0.0f, 0.0f, n, 0.0f, 0.0f, r, g, b, a);
        }
        else if constexpr (std::is_same<T, Vertex_color>::value) {
          // x, y, z, r, g, b, a
          triangle_vertices.emplace_back(v1.x, v1.y, z, r, g, b, a);
          triangle_vertices.emplace_back(v2.x, v2.y, z, r, g, b, a);
          triangle_vertices.emplace_back(x,       y, z, r, g, b, a);
        }
        else if constexpr (std::is_same<T, Vertex_normal_color>::value) {
          // x, y, z, nx, ny, nz, r, g, b, a
          triangle_vertices.emplace_back(v1.x, v1.y, z, 0.0f, 0.0f, n, r, g, b, a);
          triangle_vertices.emplace_back(v2.x, v2.y, z, 0.0f, 0.0f, n, r, g, b, a);
          triangle_vertices.emplace_back(x,       y, z, 0.0f, 0.0f, n, r, g, b, a);
        }
      }
      break;
      case Face::Up:
      case Face::Down: {
        const auto& v1 = face == Face::Down ? vertices[i-1] : vertices[i];
        const auto& v2 = face == Face::Down ? vertices[i] : vertices[i-1];

        // Direction of normal
        float n = face == Face::Up ? 1.0f : -1.0f;

        if constexpr (std::is_same<T, Vertex>::value) {
          // x, y, z, nx, ny, nz, s, t, r, g, b, a (texcoords s and t are not provided and kept zero)
          triangle_vertices.emplace_back(v1.x, y, v1.z, 0.0f, n, 0.0f, 0.0f, 0.0f, r, g, b, a);
          triangle_vertices.emplace_back(v2.x, y, v2.z, 0.0f, n, 0.0f, 0.0f, 0.0f, r, g, b, a);
          triangle_vertices.emplace_back(x,    y,    z, 0.0f, n, 0.0f, 0.0f, 0.0f, r, g, b, a);
        }
        else if constexpr (std::is_same<T, Vertex_color>::value) {
          // x, y, z, r, g, b, a
          triangle_vertices.emplace_back(v1.x, y, v1.z, r, g, b, a);
          triangle_vertices.emplace_back(v2.x, y, v2.z, r, g, b, a);
          triangle_vertices.emplace_back(x,    y,    z, r, g, b, a);
        }
        else if constexpr (std::is_same<T, Vertex_normal_color>::value) {
          // x, y, z, nx, ny, nz, r, g, b, a
          triangle_vertices.emplace_back(v1.x, y, v1.z, 0.0f, n, 0.0f, r, g, b, a);
          triangle_vertices.emplace_back(v2.x, y, v2.z, 0.0f, n, 0.0f, r, g, b, a);
          triangle_vertices.emplace_back(x,    y,    z, 0.0f, n, 0.0f, r, g, b, a);
        }
      }
      break;
      case Face::Left:
      case Face::Right: {
        const auto& v1 = face == Face::Left ? vertices[i] : vertices[i-1];
        const auto& v2 = face == Face::Left ? vertices[i-1] : vertices[i];

        // Direction of normal
        float n = face == Face::Right ? 1.0f : -1.0f;

        if constexpr (std::is_same<T, Vertex>::value) {
          // x, y, z, nx, ny, nz, s, t, r, g, b, a (texcoords s and t are not provided and kept zero)
          triangle_vertices.emplace_back(x, v1.w, v1.z, n, 0.0f, 0.0f, 0.0f, 0.0f, r, g, b, a);
          triangle_vertices.emplace_back(x, v2.w, v2.z, n, 0.0f, 0.0f, 0.0f, 0.0f, r, g, b, a);
          triangle_vertices.emplace_back(x,    y,    z, n, 0.0f, 0.0f, 0.0f, 0.0f, r, g, b, a);
        }
        else if constexpr (std::is_same<T, Vertex_color>::value) {
          // x, y, z, r, g, b, a
          triangle_vertices.emplace_back(x, v1.w, v1.z, r, g, b, a);
          triangle_vertices.emplace_back(x, v2.w, v2.z, r, g, b, a);
          triangle_vertices.emplace_back(x, y, z, r, g, b, a);
        }
        else if constexpr (std::is_same<T, Vertex_normal_color>::value) {
          // x, y, z, nx, ny, nz, r, g, b, a
          triangle_vertices.emplace_back(x, v1.w, v1.z, n, 0.0f, 0.0f, r, g, b, a);
          triangle_vertices.emplace_back(x, v2.w, v2.z, n, 0.0f, 0.0f, r, g, b, a);
          triangle_vertices.emplace_back(x,    y,    z, n, 0.0f, 0.0f, r, g, b, a);
        }
      }
      break;
    }
  }

  return triangle_vertices;
}


template std::vector<apeiron::engine::Vertex> apeiron::engine::primitive::quad_vertices(float, float, apeiron::engine::Face, const glm::vec3&);
template std::vector<apeiron::engine::Vertex> apeiron::engine::primitive::quad_vertices(float, float, const glm::vec4&, apeiron::engine::Face, const glm::vec3&);
template std::vector<apeiron::engine::Vertex> apeiron::engine::primitive::quad_vertices(float, float, const glm::mat4&, apeiron::engine::Face, const glm::vec3&);
template std::vector<apeiron::engine::Vertex_simple> apeiron::engine::primitive::quad_vertices(float, float, apeiron::engine::Face, const glm::vec3&);
template std::vector<apeiron::engine::Vertex_normal> apeiron::engine::primitive::quad_vertices(float, float, apeiron::engine::Face, const glm::vec3&);
template std::vector<apeiron::engine::Vertex_color> apeiron::engine::primitive::quad_vertices(float, float, const glm::vec4&, apeiron::engine::Face, const glm::vec3&);
template std::vector<apeiron::engine::Vertex_color> apeiron::engine::primitive::quad_vertices(float, float, const glm::mat4&, apeiron::engine::Face, const glm::vec3&);
template std::vector<apeiron::engine::Vertex_texcoords> apeiron::engine::primitive::quad_vertices(float, float, apeiron::engine::Face, const glm::vec3&);
template std::vector<apeiron::engine::Vertex_normal_color> apeiron::engine::primitive::quad_vertices(float, float, const glm::vec4&, apeiron::engine::Face, const glm::vec3&);
template std::vector<apeiron::engine::Vertex_normal_texcoords> apeiron::engine::primitive::quad_vertices(float, float, apeiron::engine::Face, const glm::vec3&);

template std::vector<apeiron::engine::Vertex> apeiron::engine::primitive::cuboid_vertices(const glm::vec3&, const glm::vec3&);
template std::vector<apeiron::engine::Vertex> apeiron::engine::primitive::cuboid_vertices(const glm::vec3&, const glm::vec4&, const glm::vec3&);
template std::vector<apeiron::engine::Vertex_simple> apeiron::engine::primitive::cuboid_vertices(const glm::vec3&, const glm::vec3&);
template std::vector<apeiron::engine::Vertex_normal> apeiron::engine::primitive::cuboid_vertices(const glm::vec3&, const glm::vec3&);
template std::vector<apeiron::engine::Vertex_color> apeiron::engine::primitive::cuboid_vertices(const glm::vec3&, const glm::vec4&, const glm::vec3&);
template std::vector<apeiron::engine::Vertex_texcoords> apeiron::engine::primitive::cuboid_vertices(const glm::vec3&, const glm::vec3&);
template std::vector<apeiron::engine::Vertex_normal_color> apeiron::engine::primitive::cuboid_vertices(const glm::vec3&, const glm::vec4&, const glm::vec3&);
template std::vector<apeiron::engine::Vertex_normal_texcoords> apeiron::engine::primitive::cuboid_vertices(const glm::vec3&, const glm::vec3&);

template std::vector<apeiron::engine::Vertex> apeiron::engine::primitive::disk_vertices(float, int, apeiron::engine::Face, const glm::vec3&);
template std::vector<apeiron::engine::Vertex> apeiron::engine::primitive::disk_vertices(float, int, const glm::vec4&, apeiron::engine::Face, const glm::vec3&);
template std::vector<apeiron::engine::Vertex_simple> apeiron::engine::primitive::disk_vertices(float, int, apeiron::engine::Face, const glm::vec3&);
template std::vector<apeiron::engine::Vertex_normal> apeiron::engine::primitive::disk_vertices(float, int, apeiron::engine::Face, const glm::vec3&);
template std::vector<apeiron::engine::Vertex_color> apeiron::engine::primitive::disk_vertices(float, int, const glm::vec4&, apeiron::engine::Face, const glm::vec3&);
template std::vector<apeiron::engine::Vertex_normal_color> apeiron::engine::primitive::disk_vertices(float, int, const glm::vec4&, apeiron::engine::Face, const glm::vec3&);
