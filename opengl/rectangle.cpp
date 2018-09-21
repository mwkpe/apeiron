#include "rectangle.h"


#include <vector>
#include <cstddef>
#include "GL/glew.h"
#include "engine/vertex.h"


namespace {


std::vector<apeiron::engine::Vertex_normal_texcoords> build_vertices(float w, float h)
{
  w /= 2.0f;
  h /= 2.0f;

  return {
    {
      { w,  h, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f},
      { w, -h, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f},
      {-w,  h, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f},
      {-w, -h, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f},
      {-w,  h, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f},
      { w, -h, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f}
    }
  };
}


}  // namespace


apeiron::opengl::Rectangle::Rectangle(float width, float height)
{
  glGenVertexArrays(1, &vao_);
  glGenBuffers(1, &vbo_);
  glBindVertexArray(vao_);

  const auto vertices = build_vertices(width, height);
  vertex_count_ = vertices.size();
  const int stride = sizeof(engine::Vertex_normal_texcoords);

  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(engine::Vertex_normal_texcoords),
      vertices.data(), GL_STATIC_DRAW);
  
  // Position
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(0));
  glEnableVertexAttribArray(0);
  // Normal
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride,
      reinterpret_cast<void*>(offsetof(engine::Vertex_normal_texcoords, normal)));
  glEnableVertexAttribArray(1);
  // Texture coordinates
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride,
      reinterpret_cast<void*>(offsetof(engine::Vertex_normal_texcoords, texcoords)));
  glEnableVertexAttribArray(2);
}


void apeiron::opengl::Rectangle::render() const
{
  glBindVertexArray(vao_);
  glDrawArrays(GL_TRIANGLES, 0, vertex_count_);
}
