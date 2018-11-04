#include "quad.h"


#include <vector>
#include <cstddef>
#include "GL/glew.h"
#include "engine/vertex.h"


namespace {


std::vector<apeiron::engine::Vertex_texcoords> build_vertices(float w, float h)
{
  w /= 2.0f;
  h /= 2.0f;

  return {
    {
      {-w, -h, 0.0f, 0.0f, 0.0f},
      { w, -h, 0.0f, 1.0f, 0.0f},
      {-w,  h, 0.0f, 0.0f, 1.0f},
      { w, -h, 0.0f, 1.0f, 0.0f},
      { w,  h, 0.0f, 1.0f, 1.0f},
      {-w,  h, 0.0f, 0.0f, 1.0f}
    }
  };
}


std::vector<apeiron::engine::Vertex_color> build_vertices(float w, float h, glm::vec4 color)
{
  w /= 2.0f;
  h /= 2.0f;

  return {
    {
      {-w, -h, 0.0f, color.r, color.g, color.b, color.a},
      { w, -h, 0.0f, color.r, color.g, color.b, color.a},
      {-w,  h, 0.0f, color.r, color.g, color.b, color.a},
      { w, -h, 0.0f, color.r, color.g, color.b, color.a},
      { w,  h, 0.0f, color.r, color.g, color.b, color.a},
      {-w,  h, 0.0f, color.r, color.g, color.b, color.a}
    }
  };
}


}  // namespace


apeiron::opengl::Quad::Quad(float width, float height)
{
  set(width, height);
}


apeiron::opengl::Quad::Quad(float width, float height, glm::vec4 color)
{
  set(width, height, color);
}


void apeiron::opengl::Quad::set(float width, float height)
{
  delete_buffers();

  glGenVertexArrays(1, &vao_);
  glGenBuffers(1, &vbo_);
  glBindVertexArray(vao_);

  const auto vertices = build_vertices(width, height);
  vertex_count_ = vertices.size();
  const int stride = sizeof(engine::Vertex_texcoords);

  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(engine::Vertex_texcoords),
      vertices.data(), GL_STATIC_DRAW);
  
  // Position
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(0));
  glEnableVertexAttribArray(0);
  // Texture coordinates
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride,
      reinterpret_cast<void*>(offsetof(engine::Vertex_texcoords, texcoords)));
  glEnableVertexAttribArray(2);
}


void apeiron::opengl::Quad::set(float width, float height, glm::vec4 color)
{
  delete_buffers();

  glGenVertexArrays(1, &vao_);
  glGenBuffers(1, &vbo_);
  glBindVertexArray(vao_);

  const auto vertices = build_vertices(width, height, color);
  vertex_count_ = vertices.size();
  const int stride = sizeof(engine::Vertex_color);

  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(engine::Vertex_color),
      vertices.data(), GL_STATIC_DRAW);
  
  // Position
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(0));
  glEnableVertexAttribArray(0);
  // Color
  glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, stride,
      reinterpret_cast<void*>(offsetof(engine::Vertex_color, color)));
  glEnableVertexAttribArray(3);
}


void apeiron::opengl::Quad::render() const
{
  glBindVertexArray(vao_);
  glDrawArrays(GL_TRIANGLES, 0, vertex_count_);
}
