#include "polygon.h"


#include "GL/glew.h"


apeiron::opengl::Polygon::Polygon(std::vector<float>&& vertices)
{
  glGenVertexArrays(1, &vao_);
  glGenBuffers(1, &vbo_);
  glBindVertexArray(vao_);
  const std::size_t values_per_vertex = 3;
  vertex_count_ = static_cast<std::uint32_t>(vertices.size() / values_per_vertex);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(0));
  glEnableVertexAttribArray(0);
}


void apeiron::opengl::Polygon::render() const
{
  glBindVertexArray(vao_);
  glDrawArrays(GL_TRIANGLES, 0, vertex_count_);
}
