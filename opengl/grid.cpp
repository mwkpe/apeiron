#include "grid.h"


#include <tuple>
#include <vector>
#include <cmath>
#include "GL/glew.h"


namespace {


std::tuple<std::vector<float>, int> build_vertices(const glm::vec3& size, const glm::vec3& spacing,
    float precision, glm::vec3 color)
{
  std::vector<float> vertices;

  float x_first = -size.x / 2.0f;
  float x_last = size.x / 2.0f;
  float z_first = -size.z / 2.0f;
  float z_last = size.z / 2.0f;

  for (float pos = x_first; std::abs(pos - spacing.x - x_last) > precision; pos += spacing.x) {
    vertices.push_back(pos);
    vertices.push_back(0);
    vertices.push_back(z_first);
    vertices.push_back(color.r);
    vertices.push_back(color.g);
    vertices.push_back(color.b);
    vertices.push_back(pos);
    vertices.push_back(0);
    vertices.push_back(z_last);
    vertices.push_back(color.r);
    vertices.push_back(color.g);
    vertices.push_back(color.b);
  }

  for (float pos = z_first; std::abs(pos - spacing.z - z_last) > precision; pos += spacing.z) {
    vertices.push_back(x_first);
    vertices.push_back(0);
    vertices.push_back(pos);
    vertices.push_back(color.r);
    vertices.push_back(color.g);
    vertices.push_back(color.b);
    vertices.push_back(x_last);
    vertices.push_back(0);
    vertices.push_back(pos);
    vertices.push_back(color.r);
    vertices.push_back(color.g);
    vertices.push_back(color.b);
  }

  return {std::move(vertices), 6};  // Values per vertex
}


}  // namespace


apeiron::opengl::Grid::Grid(const glm::vec3& size, const glm::vec3& spacing, float precision,
      const glm::vec3& color, float line_width)
    : size_{size}, spacing_{spacing}, line_width_{line_width}
{
  const auto [vertices, values_per_vertex] = build_vertices(size, spacing, precision, color);
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
