#include "grid.h"


#include <tuple>
#include <vector>
#include <cmath>
#include "GL/glew.h"
#include "engine/vertex.h"
#include "utility/linear_range.h"


namespace {


auto build_vertices(const glm::vec2& size, std::size_t x_steps, std::size_t y_steps,
    glm::vec4 color)
{
  using namespace apeiron::engine;
  using namespace apeiron::utility;
  std::vector<Vertex_color> vertices;

  // Builds a grid on the OpenGL xz-plane (with y as height vector),
  // therefore puts the y coordinate into the z coordinate
  const float x_first = -size.x / 2.0f;
  const float x_last = size.x / 2.0f;
  const float y_first = -size.y / 2.0f;
  const float y_last = size.y / 2.0f;
  const float height = 0.0f;

  for (float x : Linear_range{x_first, x_last, x_steps}) {
    vertices.push_back(Vertex_color{x, height, y_first, color.r, color.g, color.b, color.a});
    vertices.push_back(Vertex_color{x, height, y_last, color.r, color.g, color.b, color.a});
  }

  for (float y : Linear_range{y_first, y_last, y_steps}) {
    vertices.push_back(Vertex_color{x_first, height, y, color.r, color.g, color.b, color.a});
    vertices.push_back(Vertex_color{x_last, height, y, color.r, color.g, color.b, color.a});
  }

  return vertices;
}


}  // namespace


apeiron::opengl::Grid::Grid(const glm::vec2& size, std::size_t x_steps, std::size_t y_steps,
    const glm::vec4& color, float line_width) : size_{size}, line_width_{line_width}
{
  const auto vertices = build_vertices(size, x_steps, y_steps, color);
  vertex_count_ = vertices.size();

  glGenVertexArrays(1, &vao_);
  glGenBuffers(1, &vbo_);
  glBindVertexArray(vao_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(engine::Vertex_color),
      vertices.data(), GL_STATIC_DRAW);
  
  // Position
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(engine::Vertex_color),
      reinterpret_cast<void*>(0));
  glEnableVertexAttribArray(0);
  // Color
  glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(engine::Vertex_color),
      reinterpret_cast<void*>(offsetof(engine::Vertex_color, color)));
  glEnableVertexAttribArray(3);
}


void apeiron::opengl::Grid::render() const
{
  glBindVertexArray(vao_);
  float global_width;
  glGetFloatv(GL_LINE_WIDTH, &global_width);
  glLineWidth(line_width_);
  glDrawArrays(GL_LINES, 0, vertex_count_);
  glLineWidth(global_width);
}
