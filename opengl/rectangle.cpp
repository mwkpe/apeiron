#include "rectangle.h"


#include <tuple>
#include <vector>
#include "GL/glew.h"


namespace {


std::tuple<std::vector<float>, int> build_vertices(float x, float y)
{
  x /= 2.0f;
  y /= 2.0f;

  return {
    {
      // x, y, z, nx, ny, nz, s, t
      -x, -y, 0,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
       x, -y, 0,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f,
       x,  y, 0,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
       x,  y, 0,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
      -x,  y, 0,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f,
      -x, -y, 0,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
    },
    8  // Values per vertex
  };
}


std::tuple<std::vector<float>, int> build_wireframe_vertices(float x, float y)
{
  x /= 2.0f;
  y /= 2.0f;

  return {
    {
      -x, -y, 0,
       x, -y, 0,
       x, -y, 0,
       x,  y, 0,
       x,  y, 0,
      -x,  y, 0,
      -x,  y, 0,
      -x, -y, 0,
    },
    3  // Values per vertex
  };
}


}  // namespace


apeiron::opengl::Rectangle::Rectangle(float x, float y, bool wireframe, float line_width)
    : wireframe_{wireframe}, line_width_{line_width}
{
  glGenVertexArrays(1, &vao_);
  glGenBuffers(1, &vbo_);
  glBindVertexArray(vao_);

  if (wireframe) {
    const auto [vertices, values_per_vertex] = build_wireframe_vertices(x, y);
    vertex_count_ = vertices.size() / values_per_vertex;
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);
  }
  else {
    const auto [vertices, values_per_vertex] = build_vertices(x, y);
    vertex_count_ = vertices.size() / values_per_vertex;
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    const int stride = values_per_vertex * sizeof(float);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
  }
}


void apeiron::opengl::Rectangle::render() const
{
  glBindVertexArray(vao_);
  if (wireframe_) {
    float global_width;
    glGetFloatv(GL_LINE_WIDTH, &global_width);
    glLineWidth(line_width_);
    glDrawArrays(GL_LINES, 0, vertex_count_);
    glLineWidth(global_width);
  }
  else {
    glDrawArrays(GL_TRIANGLES, 0, vertex_count_);
  }
}
