#include "wire_cuboid.h"


#include <tuple>
#include <vector>
#include <cstddef>
#include "GL/glew.h"
#include "engine/vertex.h"


namespace {


auto build_wireframe_vertices(glm::vec3 size, glm::vec3 position)
    -> std::tuple<std::vector<apeiron::engine::Vertex_simple>, std::vector<std::uint16_t>>
{
  const float x = position.x;
  const float y = position.y;
  const float z = position.z;

  const float w = size.x * 0.5f;
  const float h = size.y * 0.5f;
  const float l = size.z * 0.5f;

  return {
    // Vertices
    {
      // Front
      {-w + x, -h + y, l + z},
      { w + x, -h + y, l + z},
      { w + x,  h + y, l + z},
      {-w + x,  h + y, l + z},
      // Back
      {-w + x, -h + y, -l + z},
      { w + x, -h + y, -l + z},
      { w + x,  h + y, -l + z},
      {-w + x,  h + y, -l + z}
    },
    // Elements
    {
      // Front
      0, 1, 1, 2, 2, 3, 3, 0,
      // Back
      4, 5, 5, 6, 6, 7, 7, 4,
      // Connections
      0, 4, 1, 5, 2, 6, 3, 7
    }
  };
}


auto build_wireframe_vertices(glm::vec3 size, glm::vec4 color, glm::vec3 position)
    -> std::tuple<std::vector<apeiron::engine::Vertex_color>, std::vector<std::uint16_t>>
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

  return {
    // Vertices
    {
      // Front
      {-w + x, -h + y, l + z, r, g, b, a},
      { w + x, -h + y, l + z, r, g, b, a},
      { w + x,  h + y, l + z, r, g, b, a},
      {-w + x,  h + y, l + z, r, g, b, a},
      // Back
      {-w + x, -h + y, -l + z, r, g, b, a},
      { w + x, -h + y, -l + z, r, g, b, a},
      { w + x,  h + y, -l + z, r, g, b, a},
      {-w + x,  h + y, -l + z, r, g, b, a}
    },
    // Elements
    {
      // Front
      0, 1, 1, 2, 2, 3, 3, 0,
      // Back
      4, 5, 5, 6, 6, 7, 7, 4,
      // Connections
      0, 4, 1, 5, 2, 6, 3, 7
    }
  };
}


} // namespace


apeiron::opengl::Wire_cuboid::Wire_cuboid(glm::vec3 size, glm::vec3 position)
{
  glGenVertexArrays(1, &vao_);
  glGenBuffers(1, &vbo_);
  glGenBuffers(1, &ebo_);
  glBindVertexArray(vao_);

  const auto [vertices, elements] = build_wireframe_vertices(size, position);
  element_count_ = elements.size();

  // Vertices
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(engine::Vertex_simple),
      vertices.data(), GL_STATIC_DRAW);

  // Elements
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size() * sizeof(std::uint16_t),
      elements.data(), GL_STATIC_DRAW);

  // Position
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(0));
  glEnableVertexAttribArray(0);
}


apeiron::opengl::Wire_cuboid::Wire_cuboid(glm::vec3 size, glm::vec4 color, glm::vec3 position)
{
  glGenVertexArrays(1, &vao_);
  glGenBuffers(1, &vbo_);
  glGenBuffers(1, &ebo_);
  glBindVertexArray(vao_);

  const auto [vertices, elements] = build_wireframe_vertices(size, color, position);
  element_count_ = elements.size();
  const int stride = sizeof(engine::Vertex_color);

  // Vertices
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(engine::Vertex_color),
      vertices.data(), GL_STATIC_DRAW);

  // Elements
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size() * sizeof(std::uint16_t),
      elements.data(), GL_STATIC_DRAW);

  // Position
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(0));
  glEnableVertexAttribArray(0);
  // Color
  glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, stride,
      reinterpret_cast<void*>(offsetof(engine::Vertex_color, color)));
  glEnableVertexAttribArray(3);
}


void apeiron::opengl::Wire_cuboid::render() const
{
  float global_width;
  glGetFloatv(GL_LINE_WIDTH, &global_width);
  glLineWidth(line_width_);

  glBindVertexArray(vao_); 
  glDrawElements(GL_LINES, element_count_, GL_UNSIGNED_SHORT, nullptr);

  glLineWidth(global_width);
}
