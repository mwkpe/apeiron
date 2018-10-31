#include "points.h"


#include <cstddef>
#include "GL/glew.h"


apeiron::opengl::Points::Points(const std::vector<engine::Vertex_simple>& vertices)
{
  set(vertices);
}


apeiron::opengl::Points::Points(const std::vector<engine::Vertex_color>& vertices)
{
  set(vertices);
}


void apeiron::opengl::Points::set(const std::vector<engine::Vertex_simple>& vertices)
{
  vertex_count_ = vertices.size();

  glGenVertexArrays(1, &vao_);
  glGenBuffers(1, &vbo_);
  glBindVertexArray(vao_);

  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(engine::Vertex_simple),
      vertices.data(), GL_STATIC_DRAW);

  // Position
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(0));
  glEnableVertexAttribArray(0);
}


void apeiron::opengl::Points::set(const std::vector<engine::Vertex_color>& vertices)
{
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
