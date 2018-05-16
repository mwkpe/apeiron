#include "points.h"


#include "GL/glew.h"


void apeiron::opengl::Points::init(std::vector<float>&& vertices, Format format)
{
  glGenVertexArrays(1, &vao_);
  glGenBuffers(1, &vbo_);
  glBindVertexArray(vao_);
  std::size_t values_per_vertex = 3;
  switch (format) {
    case Format::Xyz:
      values_per_vertex = 3;
      break;
    case Format::Xyzrgb:
      values_per_vertex = 6;
      break;
  }
  const int stride = values_per_vertex * sizeof(float);
  int offset = 0;
  vertex_count_ = static_cast<std::uint32_t>(vertices.size() / values_per_vertex);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(0));
  glEnableVertexAttribArray(0);
  if (format == Format::Xyzrgb) {
    offset += 3 * sizeof(float);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(offset));
    glEnableVertexAttribArray(3);
  }
}


void apeiron::opengl::Points::render() const
{
  float current_size;
  glGetFloatv(GL_POINT_SIZE, &current_size);
  glPointSize(point_size_);
  glBindVertexArray(vao_);
  glDrawArrays(GL_POINTS, 0, vertex_count_);
  glPointSize(current_size);
}


void apeiron::opengl::Points::render(std::uint32_t start, std::uint32_t count) const
{
  float current_size;
  glGetFloatv(GL_POINT_SIZE, &current_size);
  glPointSize(point_size_);
  glBindVertexArray(vao_);
  glDrawArrays(GL_POINTS, start, count);
  glPointSize(current_size);
}
