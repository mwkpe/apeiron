#include "engine/primitive.h"


#include <type_traits>


template<typename T> std::vector<T> apeiron::engine::primitive::cube_vertices(glm::vec3 size,
    glm::vec3 position)
{
  const float x = position.x;
  const float y = position.y;
  const float z = position.z;

  const float w = size.x * 0.5f;
  const float h = size.y * 0.5f;
  const float l = size.z * 0.5f;

  if constexpr (std::is_same<T, Vertex_simple>::value) {
    return {
      {
        // x, y, z
        // Front (xy-plane)
        {-w + x, -h + y, l + z},
        { w + x, -h + y, l + z},
        { w + x,  h + y, l + z},
        { w + x,  h + y, l + z},
        {-w + x,  h + y, l + z},
        {-w + x, -h + y, l + z},
        // Back (xy-plane)
        { w + x, -h + y, -l + z},
        {-w + x, -h + y, -l + z},
        {-w + x,  h + y, -l + z},
        {-w + x,  h + y, -l + z},
        { w + x,  h + y, -l + z},
        { w + x, -h + y, -l + z},
        // Left (yz-plane)
        {-w + x, -h + y, -l + z},
        {-w + x, -h + y,  l + z},
        {-w + x,  h + y,  l + z},
        {-w + x,  h + y,  l + z},
        {-w + x,  h + y, -l + z},
        {-w + x, -h + y, -l + z},
        // Right (yz-plane)
        {w + x, -h + y,  l + z},
        {w + x, -h + y, -l + z},
        {w + x,  h + y, -l + z},
        {w + x,  h + y, -l + z},
        {w + x,  h + y,  l + z},
        {w + x, -h + y,  l + z},
        // Top (xz-plane)
        {-w + x, h + y,  l + z},
        { w + x, h + y,  l + z},
        { w + x, h + y, -l + z},
        { w + x, h + y, -l + z},
        {-w + x, h + y, -l + z},
        {-w + x, h + y,  l + z},
        // Bottom (xz-plane)
        {-w + x, -h + y, -l + z},
        { w + x, -h + y, -l + z},
        { w + x, -h + y,  l + z},
        { w + x, -h + y,  l + z},
        {-w + x, -h + y,  l + z},
        {-w + x, -h + y, -l + z}
      }
    };
  }
  else if constexpr (std::is_same<T, Vertex_normal>::value) {
    return {
      {
        // x, y, z, nx, ny, nz
        // Front (xy-plane)
        {-w + x, -h + y, l + z, 0.0f, 0.0f, 1.0f},
        { w + x, -h + y, l + z, 0.0f, 0.0f, 1.0f},
        { w + x,  h + y, l + z, 0.0f, 0.0f, 1.0f},
        { w + x,  h + y, l + z, 0.0f, 0.0f, 1.0f},
        {-w + x,  h + y, l + z, 0.0f, 0.0f, 1.0f},
        {-w + x, -h + y, l + z, 0.0f, 0.0f, 1.0f},
        // Back (xy-plane)
        { w + x, -h + y, -l + z, 0.0f, 0.0f, -1.0f},
        {-w + x, -h + y, -l + z, 0.0f, 0.0f, -1.0f},
        {-w + x,  h + y, -l + z, 0.0f, 0.0f, -1.0f},
        {-w + x,  h + y, -l + z, 0.0f, 0.0f, -1.0f},
        { w + x,  h + y, -l + z, 0.0f, 0.0f, -1.0f},
        { w + x, -h + y, -l + z, 0.0f, 0.0f, -1.0f},
        // Left (yz-plane)
        {-w + x, -h + y, -l + z, -1.0f, 0.0f, 0.0f},
        {-w + x, -h + y,  l + z, -1.0f, 0.0f, 0.0f},
        {-w + x,  h + y,  l + z, -1.0f, 0.0f, 0.0f},
        {-w + x,  h + y,  l + z, -1.0f, 0.0f, 0.0f},
        {-w + x,  h + y, -l + z, -1.0f, 0.0f, 0.0f},
        {-w + x, -h + y, -l + z, -1.0f, 0.0f, 0.0f},
        // Right (yz-plane)
        {w + x, -h + y,  l + z, 1.0f, 0.0f, 0.0f},
        {w + x, -h + y, -l + z, 1.0f, 0.0f, 0.0f},
        {w + x,  h + y, -l + z, 1.0f, 0.0f, 0.0f},
        {w + x,  h + y, -l + z, 1.0f, 0.0f, 0.0f},
        {w + x,  h + y,  l + z, 1.0f, 0.0f, 0.0f},
        {w + x, -h + y,  l + z, 1.0f, 0.0f, 0.0f},
        // Top (xz-plane)
        {-w + x, h + y,  l + z, 0.0f, 1.0f, 0.0f},
        { w + x, h + y,  l + z, 0.0f, 1.0f, 0.0f},
        { w + x, h + y, -l + z, 0.0f, 1.0f, 0.0f},
        { w + x, h + y, -l + z, 0.0f, 1.0f, 0.0f},
        {-w + x, h + y, -l + z, 0.0f, 1.0f, 0.0f},
        {-w + x, h + y,  l + z, 0.0f, 1.0f, 0.0f},
        // Bottom (xz-plane)
        {-w + x, -h + y, -l + z, 0.0f, -1.0f, 0.0f},
        { w + x, -h + y, -l + z, 0.0f, -1.0f, 0.0f},
        { w + x, -h + y,  l + z, 0.0f, -1.0f, 0.0f},
        { w + x, -h + y,  l + z, 0.0f, -1.0f, 0.0f},
        {-w + x, -h + y,  l + z, 0.0f, -1.0f, 0.0f},
        {-w + x, -h + y, -l + z, 0.0f, -1.0f, 0.0f}
      }
    };
  }
  else if constexpr (std::is_same<T, Vertex_texcoords>::value) {
    return {
      {
        // x, y, z, nx, ny, nz, s, t, r, g, b, a
        // Front (xy-plane)
        {-w + x, -h + y, l + z, 0.0f, 0.0f},
        { w + x, -h + y, l + z, 1.0f, 0.0f},
        { w + x,  h + y, l + z, 1.0f, 1.0f},
        { w + x,  h + y, l + z, 1.0f, 1.0f},
        {-w + x,  h + y, l + z, 0.0f, 1.0f},
        {-w + x, -h + y, l + z, 0.0f, 0.0f},
        // Back (xy-plane)
        { w + x, -h + y, -l + z, 0.0f, 0.0f},
        {-w + x, -h + y, -l + z, 1.0f, 0.0f},
        {-w + x,  h + y, -l + z, 1.0f, 1.0f},
        {-w + x,  h + y, -l + z, 1.0f, 1.0f},
        { w + x,  h + y, -l + z, 0.0f, 1.0f},
        { w + x, -h + y, -l + z, 0.0f, 0.0f},
        // Left (yz-plane)
        {-w + x, -h + y, -l + z, 0.0f, 0.0f},
        {-w + x, -h + y,  l + z, 1.0f, 0.0f},
        {-w + x,  h + y,  l + z, 1.0f, 1.0f},
        {-w + x,  h + y,  l + z, 1.0f, 1.0f},
        {-w + x,  h + y, -l + z, 0.0f, 1.0f},
        {-w + x, -h + y, -l + z, 0.0f, 0.0f},
        // Right (yz-plane)
        {w + x, -h + y,  l + z, 0.0f, 0.0f},
        {w + x, -h + y, -l + z, 1.0f, 0.0f},
        {w + x,  h + y, -l + z, 1.0f, 1.0f},
        {w + x,  h + y, -l + z, 1.0f, 1.0f},
        {w + x,  h + y,  l + z, 0.0f, 1.0f},
        {w + x, -h + y,  l + z, 0.0f, 0.0f},
        // Top (xz-plane)
        {-w + x, h + y,  l + z, 0.0f, 0.0f},
        { w + x, h + y,  l + z, 1.0f, 0.0f},
        { w + x, h + y, -l + z, 1.0f, 1.0f},
        { w + x, h + y, -l + z, 1.0f, 1.0f},
        {-w + x, h + y, -l + z, 0.0f, 1.0f},
        {-w + x, h + y,  l + z, 0.0f, 0.0f},
        // Bottom (xz-plane)
        {-w + x, -h + y, -l + z, 0.0f, 0.0f},
        { w + x, -h + y, -l + z, 1.0f, 0.0f},
        { w + x, -h + y,  l + z, 1.0f, 1.0f},
        { w + x, -h + y,  l + z, 1.0f, 1.0f},
        {-w + x, -h + y,  l + z, 0.0f, 1.0f},
        {-w + x, -h + y, -l + z, 0.0f, 0.0f}
      }
    };
  }
  else if constexpr (std::is_same<T, Vertex_normal_texcoords>::value) {
    return {
      {
        // x, y, z, nx, ny, nz, s, t
        // Front (xy-plane)
        {-w + x, -h + y, l + z, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
        { w + x, -h + y, l + z, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f},
        { w + x,  h + y, l + z, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f},
        { w + x,  h + y, l + z, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f},
        {-w + x,  h + y, l + z, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f},
        {-w + x, -h + y, l + z, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
        // Back (xy-plane)
        { w + x, -h + y, -l + z, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f},
        {-w + x, -h + y, -l + z, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f},
        {-w + x,  h + y, -l + z, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f},
        {-w + x,  h + y, -l + z, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f},
        { w + x,  h + y, -l + z, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f},
        { w + x, -h + y, -l + z, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f},
        // Left (yz-plane)
        {-w + x, -h + y, -l + z, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f},
        {-w + x, -h + y,  l + z, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f},
        {-w + x,  h + y,  l + z, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f},
        {-w + x,  h + y,  l + z, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f},
        {-w + x,  h + y, -l + z, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f},
        {-w + x, -h + y, -l + z, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f},
        // Right (yz-plane)
        {w + x, -h + y,  l + z, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f},
        {w + x, -h + y, -l + z, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f},
        {w + x,  h + y, -l + z, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f},
        {w + x,  h + y, -l + z, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f},
        {w + x,  h + y,  l + z, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f},
        {w + x, -h + y,  l + z, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f},
        // Top (xz-plane)
        {-w + x, h + y,  l + z, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f},
        { w + x, h + y,  l + z, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f},
        { w + x, h + y, -l + z, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f},
        { w + x, h + y, -l + z, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f},
        {-w + x, h + y, -l + z, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f},
        {-w + x, h + y,  l + z, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f},
        // Bottom (xz-plane)
        {-w + x, -h + y, -l + z, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f},
        { w + x, -h + y, -l + z, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f},
        { w + x, -h + y,  l + z, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f},
        { w + x, -h + y,  l + z, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f},
        {-w + x, -h + y,  l + z, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f},
        {-w + x, -h + y, -l + z, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f}
      }
    };
  }
}


template<typename T> std::vector<T> apeiron::engine::primitive::cube_vertices(glm::vec3 size,
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
        {-w + x, -h + y, l + z, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, r, g, b, a},
        { w + x, -h + y, l + z, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, r, g, b, a},
        { w + x,  h + y, l + z, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, r, g, b, a},
        { w + x,  h + y, l + z, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, r, g, b, a},
        {-w + x,  h + y, l + z, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, r, g, b, a},
        {-w + x, -h + y, l + z, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, r, g, b, a},
        // Back (xy-plane)
        { w + x, -h + y, -l + z, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, r, g, b, a},
        {-w + x, -h + y, -l + z, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, r, g, b, a},
        {-w + x,  h + y, -l + z, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f, r, g, b, a},
        {-w + x,  h + y, -l + z, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f, r, g, b, a},
        { w + x,  h + y, -l + z, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, r, g, b, a},
        { w + x, -h + y, -l + z, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, r, g, b, a},
        // Left (yz-plane)
        {-w + x, -h + y, -l + z, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, r, g, b, a},
        {-w + x, -h + y,  l + z, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, r, g, b, a},
        {-w + x,  h + y,  l + z, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, r, g, b, a},
        {-w + x,  h + y,  l + z, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, r, g, b, a},
        {-w + x,  h + y, -l + z, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, r, g, b, a},
        {-w + x, -h + y, -l + z, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, r, g, b, a},
        // Right (yz-plane)
        {w + x, -h + y,  l + z, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, r, g, b, a},
        {w + x, -h + y, -l + z, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, r, g, b, a},
        {w + x,  h + y, -l + z, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, r, g, b, a},
        {w + x,  h + y, -l + z, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, r, g, b, a},
        {w + x,  h + y,  l + z, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, r, g, b, a},
        {w + x, -h + y,  l + z, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, r, g, b, a},
        // Top (xz-plane)
        {-w + x, h + y,  l + z, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, r, g, b, a},
        { w + x, h + y,  l + z, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, r, g, b, a},
        { w + x, h + y, -l + z, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, r, g, b, a},
        { w + x, h + y, -l + z, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, r, g, b, a},
        {-w + x, h + y, -l + z, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, r, g, b, a},
        {-w + x, h + y,  l + z, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, r, g, b, a},
        // Bottom (xz-plane)
        {-w + x, -h + y, -l + z, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, r, g, b, a},
        { w + x, -h + y, -l + z, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, r, g, b, a},
        { w + x, -h + y,  l + z, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f, r, g, b, a},
        { w + x, -h + y,  l + z, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f, r, g, b, a},
        {-w + x, -h + y,  l + z, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, r, g, b, a},
        {-w + x, -h + y, -l + z, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, r, g, b, a}
      }
    };
  }
  else if constexpr (std::is_same<T, Vertex_color>::value) {
    return {
      {
        // x, y, z, r, g, b, a
        // Front (xy-plane)
        {-w + x, -h + y, l + z, r, g, b, a},
        { w + x, -h + y, l + z, r, g, b, a},
        { w + x,  h + y, l + z, r, g, b, a},
        { w + x,  h + y, l + z, r, g, b, a},
        {-w + x,  h + y, l + z, r, g, b, a},
        {-w + x, -h + y, l + z, r, g, b, a},
        // Back (xy-plane)
        { w + x, -h + y, -l + z, r, g, b, a},
        {-w + x, -h + y, -l + z, r, g, b, a},
        {-w + x,  h + y, -l + z, r, g, b, a},
        {-w + x,  h + y, -l + z, r, g, b, a},
        { w + x,  h + y, -l + z, r, g, b, a},
        { w + x, -h + y, -l + z, r, g, b, a},
        // Left (yz-plane)
        {-w + x, -h + y, -l + z, r, g, b, a},
        {-w + x, -h + y,  l + z, r, g, b, a},
        {-w + x,  h + y,  l + z, r, g, b, a},
        {-w + x,  h + y,  l + z, r, g, b, a},
        {-w + x,  h + y, -l + z, r, g, b, a},
        {-w + x, -h + y, -l + z, r, g, b, a},
        // Right (yz-plane)
        {w + x, -h + y,  l + z, r, g, b, a},
        {w + x, -h + y, -l + z, r, g, b, a},
        {w + x,  h + y, -l + z, r, g, b, a},
        {w + x,  h + y, -l + z, r, g, b, a},
        {w + x,  h + y,  l + z, r, g, b, a},
        {w + x, -h + y,  l + z, r, g, b, a},
        // Top (xz-plane)
        {-w + x, h + y,  l + z, r, g, b, a},
        { w + x, h + y,  l + z, r, g, b, a},
        { w + x, h + y, -l + z, r, g, b, a},
        { w + x, h + y, -l + z, r, g, b, a},
        {-w + x, h + y, -l + z, r, g, b, a},
        {-w + x, h + y,  l + z, r, g, b, a},
        // Bottom (xz-plane)
        {-w + x, -h + y, -l + z, r, g, b, a},
        { w + x, -h + y, -l + z, r, g, b, a},
        { w + x, -h + y,  l + z, r, g, b, a},
        { w + x, -h + y,  l + z, r, g, b, a},
        {-w + x, -h + y,  l + z, r, g, b, a},
        {-w + x, -h + y, -l + z, r, g, b, a}
      }
    };
  }
  else if constexpr (std::is_same<T, Vertex_normal_color>::value) {
    return {
      {
        // x, y, z, nx, ny, nz, r, g, b, a
        // Front (xy-plane)
        {-w + x, -h + y, l + z, 0.0f, 0.0f, 1.0f, r, g, b, a},
        { w + x, -h + y, l + z, 0.0f, 0.0f, 1.0f, r, g, b, a},
        { w + x,  h + y, l + z, 0.0f, 0.0f, 1.0f, r, g, b, a},
        { w + x,  h + y, l + z, 0.0f, 0.0f, 1.0f, r, g, b, a},
        {-w + x,  h + y, l + z, 0.0f, 0.0f, 1.0f, r, g, b, a},
        {-w + x, -h + y, l + z, 0.0f, 0.0f, 1.0f, r, g, b, a},
        // Back (xy-plane)
        { w + x, -h + y, -l + z, 0.0f, 0.0f, -1.0f, r, g, b, a},
        {-w + x, -h + y, -l + z, 0.0f, 0.0f, -1.0f, r, g, b, a},
        {-w + x,  h + y, -l + z, 0.0f, 0.0f, -1.0f, r, g, b, a},
        {-w + x,  h + y, -l + z, 0.0f, 0.0f, -1.0f, r, g, b, a},
        { w + x,  h + y, -l + z, 0.0f, 0.0f, -1.0f, r, g, b, a},
        { w + x, -h + y, -l + z, 0.0f, 0.0f, -1.0f, r, g, b, a},
        // Left (yz-plane)
        {-w + x, -h + y, -l + z, -1.0f, 0.0f, 0.0f, r, g, b, a},
        {-w + x, -h + y,  l + z, -1.0f, 0.0f, 0.0f, r, g, b, a},
        {-w + x,  h + y,  l + z, -1.0f, 0.0f, 0.0f, r, g, b, a},
        {-w + x,  h + y,  l + z, -1.0f, 0.0f, 0.0f, r, g, b, a},
        {-w + x,  h + y, -l + z, -1.0f, 0.0f, 0.0f, r, g, b, a},
        {-w + x, -h + y, -l + z, -1.0f, 0.0f, 0.0f, r, g, b, a},
        // Right (yz-plane)
        {w + x, -h + y,  l + z, 1.0f, 0.0f, 0.0f, r, g, b, a},
        {w + x, -h + y, -l + z, 1.0f, 0.0f, 0.0f, r, g, b, a},
        {w + x,  h + y, -l + z, 1.0f, 0.0f, 0.0f, r, g, b, a},
        {w + x,  h + y, -l + z, 1.0f, 0.0f, 0.0f, r, g, b, a},
        {w + x,  h + y,  l + z, 1.0f, 0.0f, 0.0f, r, g, b, a},
        {w + x, -h + y,  l + z, 1.0f, 0.0f, 0.0f, r, g, b, a},
        // Top (xz-plane)
        {-w + x, h + y,  l + z, 0.0f, 1.0f, 0.0f, r, g, b, a},
        { w + x, h + y,  l + z, 0.0f, 1.0f, 0.0f, r, g, b, a},
        { w + x, h + y, -l + z, 0.0f, 1.0f, 0.0f, r, g, b, a},
        { w + x, h + y, -l + z, 0.0f, 1.0f, 0.0f, r, g, b, a},
        {-w + x, h + y, -l + z, 0.0f, 1.0f, 0.0f, r, g, b, a},
        {-w + x, h + y,  l + z, 0.0f, 1.0f, 0.0f, r, g, b, a},
        // Bottom (xz-plane)
        {-w + x, -h + y, -l + z, 0.0f, -1.0f, 0.0f, r, g, b, a},
        { w + x, -h + y, -l + z, 0.0f, -1.0f, 0.0f, r, g, b, a},
        { w + x, -h + y,  l + z, 0.0f, -1.0f, 0.0f, r, g, b, a},
        { w + x, -h + y,  l + z, 0.0f, -1.0f, 0.0f, r, g, b, a},
        {-w + x, -h + y,  l + z, 0.0f, -1.0f, 0.0f, r, g, b, a},
        {-w + x, -h + y, -l + z, 0.0f, -1.0f, 0.0f, r, g, b, a}
      }
    };
  }
}


namespace apeiron::engine::primitive {


template auto cube_vertices<Vertex_simple>(glm::vec3 size, glm::vec3 position)
    -> std::vector<Vertex_simple>;
template auto cube_vertices<Vertex_normal>(glm::vec3 size, glm::vec3 position)
    -> std::vector<Vertex_normal>;
template auto cube_vertices<Vertex_texcoords>(glm::vec3 size, glm::vec3 position)
    -> std::vector<Vertex_texcoords>;
template auto cube_vertices<Vertex_normal_texcoords>(glm::vec3 size, glm::vec3 position)
    -> std::vector<Vertex_normal_texcoords>;


template auto cube_vertices<Vertex>(glm::vec3 size, glm::vec4 color, glm::vec3 position)
    -> std::vector<Vertex>;
template auto cube_vertices<Vertex_color>(glm::vec3 size, glm::vec4 color, glm::vec3 position)
    -> std::vector<Vertex_color>;
template auto cube_vertices<Vertex_normal_color>(glm::vec3 size, glm::vec4 color,
    glm::vec3 position) -> std::vector<Vertex_normal_color>;


}  // apeiron::engine::primitive
