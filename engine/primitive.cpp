#include "engine/primitive.h"


#include <type_traits>


template<typename T> std::vector<T> apeiron::engine::primitive::quad_vertices(float width,
    float height, Face face, glm::vec3 position)
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
          // x, y, z, nx, ny, nz, s, t
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
          // x, y, z, nx, ny, nz, s, t
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
          // x, y, z, nx, ny, nz, s, t
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
          // x, y, z, nx, ny, nz, s, t
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
    float height, glm::vec4 color, Face face, glm::vec3 position)
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
          // x, y, z, nx, ny, nz, s, t
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
          // x, y, z, nx, ny, nz, s, t
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
          // x, y, z, nx, ny, nz, s, t
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


template<typename T> std::vector<T> apeiron::engine::primitive::cuboid_vertices(glm::vec3 size,
    glm::vec3 position)
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
        // x, y, z, nx, ny, nz, s, t, r, g, b, a
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


template<typename T> std::vector<T> apeiron::engine::primitive::cuboid_vertices(glm::vec3 size,
    glm::vec4 color, glm::vec3 position)
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


using namespace apeiron::engine;
using namespace apeiron::engine::primitive;

template std::vector<Vertex> quad_vertices(float, float, Face, glm::vec3);
template std::vector<Vertex> quad_vertices(float, float, glm::vec4, Face, glm::vec3);
template std::vector<Vertex_simple> quad_vertices(float, float, Face, glm::vec3);
template std::vector<Vertex_normal> quad_vertices(float, float, Face, glm::vec3);
template std::vector<Vertex_color> quad_vertices(float, float, glm::vec4, Face, glm::vec3);
template std::vector<Vertex_texcoords> quad_vertices(float, float, Face, glm::vec3);
template std::vector<Vertex_normal_color> quad_vertices(float, float, glm::vec4, Face, glm::vec3);
template std::vector<Vertex_normal_texcoords> quad_vertices(float, float, Face, glm::vec3);

template std::vector<Vertex> cuboid_vertices(glm::vec3, glm::vec3);
template std::vector<Vertex> cuboid_vertices(glm::vec3, glm::vec4, glm::vec3);
template std::vector<Vertex_simple> cuboid_vertices(glm::vec3, glm::vec3);
template std::vector<Vertex_normal> cuboid_vertices(glm::vec3, glm::vec3);
template std::vector<Vertex_color> cuboid_vertices(glm::vec3, glm::vec4, glm::vec3);
template std::vector<Vertex_texcoords> cuboid_vertices(glm::vec3, glm::vec3);
template std::vector<Vertex_normal_color> cuboid_vertices(glm::vec3, glm::vec4, glm::vec3);
template std::vector<Vertex_normal_texcoords> cuboid_vertices(glm::vec3, glm::vec3);
