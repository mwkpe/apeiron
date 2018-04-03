#include "line_array.h"


#include "GL/glew.h"


apeiron::opengl::Line_array::Line_array(std::vector<float>&& vertices, bool vertex_color, float line_width)
    : line_width_{line_width}
{
  glGenVertexArrays(1, &vao_);
  glGenBuffers(1, &vbo_);
  glBindVertexArray(vao_);
  const int values_per_vertex = vertex_color ? 6 : 3;
  vertex_count_ = vertices.size() / values_per_vertex;
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
  const int stride = values_per_vertex * sizeof(float);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(0));
  glEnableVertexAttribArray(0);
  if (vertex_color) {
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(3 * sizeof(float)));
    glEnableVertexAttribArray(3);
  }
}


void apeiron::opengl::Line_array::render() const
{
  glBindVertexArray(vao_);
  float global_width;
  glGetFloatv(GL_LINE_WIDTH, &global_width);
  glLineWidth(line_width_);
  glDrawArrays(GL_LINES, 0, vertex_count_);
  glLineWidth(global_width);
}
