#include "grid.h"


#include <cstdint>
#include <ranges>
#include <vector>
#include <glad/glad.h>
#include "apeiron/engine/vertex.h"


namespace {


auto linspace(float first, float last, std::uint32_t cells)
{
  using namespace std::views;

  return iota(0u, cells + 1) | transform([=](std::uint32_t i) {
    auto t = static_cast<float>(i) / static_cast<float>(cells);
    return first + (last - first) * t;
  });
}


auto build_vertices(const glm::vec2& size, const glm::uvec2& cells,
    const glm::vec4& color, bool edge)
{
  using namespace std::views;

  std::vector<apeiron::engine::Vertex_color> vertices;

  const float first_x = -size.x * 0.5f;
  const float last_x = size.x * 0.5f;
  const float first_y = -size.y * 0.5f;
  const float last_y = size.y * 0.5f;
  const float z = 0.0f;

  if (edge) {
    for (float x : linspace(first_x, last_x, cells.x)) {
      vertices.push_back({{x, first_y, z}, color});
      vertices.push_back({{x, last_y, z}, color});
    }

    for (float y : linspace(first_y, last_y, cells.y)) {
      vertices.push_back({{first_x, y, z}, color});
      vertices.push_back({{last_x, y, z}, color});
    }
  }
  else {
    for (float x : linspace(first_x, last_x, cells.x) | drop(1) | take(cells.x - 1)) {
      vertices.push_back({{x, first_y, z}, color});
      vertices.push_back({{x, last_y, z}, color});
    }

    for (float y : linspace(first_y, last_y, cells.y) | drop(1) | take(cells.y - 1)) {
      vertices.push_back({{first_x, y, z}, color});
      vertices.push_back({{last_x, y, z}, color});
    }
  }

  return vertices;
}


}  // namespace


apeiron::opengl::Grid::Grid(const glm::vec2& size, const glm::uvec2& cells,
    const glm::vec4& color, bool edge, float line_width)
{
  init(size, cells, color, edge, line_width);
}


void apeiron::opengl::Grid::init(const glm::vec2& size, const glm::uvec2& cells,
    const glm::vec4& color, bool edge, float line_width)
{
  size_ = size;
  line_width_ = line_width;

  const auto vertices = build_vertices(size, cells, color, edge);
  vertex_count_ = vertices.size();
  const auto vertex_size = sizeof(engine::Vertex_color);

  glGenVertexArrays(1, &vao_);
  glGenBuffers(1, &vbo_);
  glBindVertexArray(vao_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(vertices.size() * vertex_size),
      vertices.data(), GL_STATIC_DRAW);
  
  // Position
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertex_size, reinterpret_cast<void*>(0));
  glEnableVertexAttribArray(0);
  // Color
  glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, vertex_size,
      reinterpret_cast<void*>(offsetof(engine::Vertex_color, color)));
  glEnableVertexAttribArray(3);
}


void apeiron::opengl::Grid::render() const
{
  glBindVertexArray(vao_);
  float global_width;
  glGetFloatv(GL_LINE_WIDTH, &global_width);
  glLineWidth(line_width_);
  glDrawArrays(GL_LINES, 0, static_cast<GLsizei>(vertex_count_));
  glLineWidth(global_width);
}
