#include "grid.h"


#include <vector>
#include <cmath>
#include "GL/glew.h"


namespace {


std::vector<float> build_grid(std::tuple<float, float, float> size,
    std::tuple<float, float, float> spacing, float precision)
{
  std::vector<float> vertex_data;
  auto [x, y, z] = size;
  auto [x_gap, y_gap, z_gap] = spacing;

  float x_first = -x / 2.0f;
  float x_last = x / 2.0f;
  float z_first = -z / 2.0f;
  float z_last = z / 2.0f;

  for (float pos = x_first; std::abs(pos - x_gap - x_last) > precision; pos += x_gap) {
    vertex_data.push_back(pos);
    vertex_data.push_back(y);
    vertex_data.push_back(z_first);
    if (std::abs(pos) < precision) {
      vertex_data.push_back(0.956f);
      vertex_data.push_back(0.262f);
      vertex_data.push_back(0.211f);
    }
    else {
      vertex_data.push_back(0.25f);
      vertex_data.push_back(0.25f);
      vertex_data.push_back(0.25f);
    }
    vertex_data.push_back(pos);
    vertex_data.push_back(y);
    vertex_data.push_back(z_last);
    if (std::abs(pos) < precision) {
      vertex_data.push_back(0.956f);
      vertex_data.push_back(0.262f);
      vertex_data.push_back(0.211f);
    }
    else {
      vertex_data.push_back(0.25f);
      vertex_data.push_back(0.25f);
      vertex_data.push_back(0.25f);
    }
  }

  for (float pos = z_first; std::abs(pos - z_gap - z_last) > precision; pos += z_gap) {
    vertex_data.push_back(x_first);
    vertex_data.push_back(y);
    vertex_data.push_back(pos);
    if (std::abs(pos) < precision) {
      vertex_data.push_back(0.129f);
      vertex_data.push_back(0.588f);
      vertex_data.push_back(0.952f);
    }
    else {
      vertex_data.push_back(0.25f);
      vertex_data.push_back(0.25f);
      vertex_data.push_back(0.25f);
    }
    vertex_data.push_back(x_last);
    vertex_data.push_back(y);
    vertex_data.push_back(pos);
    if (std::abs(pos) < precision) {
      vertex_data.push_back(0.129f);
      vertex_data.push_back(0.588f);
      vertex_data.push_back(0.952f);
    }
    else {
      vertex_data.push_back(0.25f);
      vertex_data.push_back(0.25f);
      vertex_data.push_back(0.25f);
    }
  }

  return vertex_data;
}


}  // namespace


apeiron::opengl::Grid::Grid(std::tuple<float, float, float> size,
    std::tuple<float, float, float> spacing, float precision)
{
  const auto vertex_data = build_grid(size, spacing, precision);
  const int elements_per_vertex = 6;
  vertex_count_ = vertex_data.size() / elements_per_vertex;
  glGenVertexArrays(1, &vao_);
  glGenBuffers(1, &vbo_);
  glBindVertexArray(vao_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, vertex_data.size() * sizeof(float), vertex_data.data(), GL_STATIC_DRAW);
  const int stride = elements_per_vertex * sizeof(float);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(0));
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(3 * sizeof(float)));
  glEnableVertexAttribArray(3);
}


void apeiron::opengl::Grid::render() const
{
  glBindVertexArray(vao_);
  glDrawArrays(GL_LINES, 0, vertex_count_);
}
