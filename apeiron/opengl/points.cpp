#include "points.h"


#include <glad/glad.h>


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
  set_buffers(vertices);
}


void apeiron::opengl::Points::set(const std::vector<engine::Vertex_color>& vertices)
{
  set_buffers(vertices);
}


void apeiron::opengl::Points::render() const
{
  float current_size;
  glGetFloatv(GL_POINT_SIZE, &current_size);
  glPointSize(point_size_);
  glBindVertexArray(vao_);
  glDrawArrays(GL_POINTS, 0, static_cast<GLsizei>(vertex_count_));
  glPointSize(current_size);
}


void apeiron::opengl::Points::render(std::uint32_t start, std::uint32_t count) const
{
  float current_size;
  glGetFloatv(GL_POINT_SIZE, &current_size);
  glPointSize(point_size_);
  glBindVertexArray(vao_);
  glDrawArrays(GL_POINTS, static_cast<GLint>(start), static_cast<GLsizei>(count));
  glPointSize(current_size);
}
