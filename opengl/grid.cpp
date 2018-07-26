#include "grid.h"


#include <tuple>
#include <vector>
#include <cmath>
#include "GL/glew.h"
#include "utility/linear_range.h"


namespace {


std::tuple<std::vector<float>, int> build_vertices(const glm::vec2& size, std::size_t x_steps,
    std::size_t y_steps, glm::vec3 color)
{
  using namespace apeiron::utility;
  std::vector<float> vertices;

  // Builds a grid on the y-plane, therefore puts the y coordinate into the z coordinate
  const float x_first = -size.x / 2.0f;
  const float x_last = size.x / 2.0f;
  const float y_first = -size.y / 2.0f;
  const float y_last = size.y / 2.0f;
  const float z = 0;

  for (float x : Linear_range{x_first, x_last, x_steps}) {
    vertices.push_back(x);
    vertices.push_back(z);
    vertices.push_back(y_first);
    vertices.push_back(color.r);
    vertices.push_back(color.g);
    vertices.push_back(color.b);
    vertices.push_back(x);
    vertices.push_back(z);
    vertices.push_back(y_last);
    vertices.push_back(color.r);
    vertices.push_back(color.g);
    vertices.push_back(color.b);
  }

  for (float y : Linear_range{y_first, y_last, y_steps}) {
    vertices.push_back(x_first);
    vertices.push_back(z);
    vertices.push_back(y);
    vertices.push_back(color.r);
    vertices.push_back(color.g);
    vertices.push_back(color.b);
    vertices.push_back(x_last);
    vertices.push_back(z);
    vertices.push_back(y);
    vertices.push_back(color.r);
    vertices.push_back(color.g);
    vertices.push_back(color.b);
  }

  return {std::move(vertices), 6};  // Values per vertex
}


}  // namespace


apeiron::opengl::Grid::Grid(const glm::vec2& size, std::size_t x_steps, std::size_t y_steps,
    const glm::vec3& color, float line_width) : size_{size}, line_width_{line_width}
{
  const auto [vertices, values_per_vertex] = build_vertices(size, x_steps, y_steps, color);
  vertex_count_ = vertices.size() / values_per_vertex;
  glGenVertexArrays(1, &vao_);
  glGenBuffers(1, &vbo_);
  glBindVertexArray(vao_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
  const int stride = values_per_vertex * sizeof(float);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(0));
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(3 * sizeof(float)));
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
