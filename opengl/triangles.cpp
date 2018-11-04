#include "triangles.h"


#include <cstddef>
#include "GL/glew.h"


apeiron::opengl::Triangles::Triangles(const std::vector<engine::Vertex>& vertices)
{
  set(vertices);
}


apeiron::opengl::Triangles::Triangles(const std::vector<engine::Vertex_simple>& vertices)
{
  set(vertices);
}


apeiron::opengl::Triangles::Triangles(const std::vector<engine::Vertex_normal>& vertices)
{
  set(vertices);
}


apeiron::opengl::Triangles::Triangles(const std::vector<engine::Vertex_color>& vertices)
{
  set(vertices);
}


apeiron::opengl::Triangles::Triangles(const std::vector<engine::Vertex_texcoords>& vertices)
{
  set(vertices);
}


apeiron::opengl::Triangles::Triangles(const std::vector<engine::Vertex_normal_color>& vertices)
{
  set(vertices);
}


apeiron::opengl::Triangles::Triangles(const std::vector<engine::Vertex_normal_texcoords>& vertices)
{
  set(vertices);
}


void apeiron::opengl::Triangles::set(const std::vector<engine::Vertex>& vertices)
{
  delete_buffers();

  vertex_count_ = vertices.size();

  glGenVertexArrays(1, &vao_);
  glGenBuffers(1, &vbo_);
  glBindVertexArray(vao_);

  const int stride = sizeof(engine::Vertex);

  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(engine::Vertex),
      vertices.data(), GL_STATIC_DRAW);

  // Position
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(0));
  glEnableVertexAttribArray(0);
  // Normal
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride,
      reinterpret_cast<void*>(offsetof(engine::Vertex, normal)));
  glEnableVertexAttribArray(1);
  // Texture coordinates
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride,
      reinterpret_cast<void*>(offsetof(engine::Vertex, texcoords)));
  glEnableVertexAttribArray(2);
  // Color
  glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, stride,
      reinterpret_cast<void*>(offsetof(engine::Vertex, color)));
  glEnableVertexAttribArray(3);
}


void apeiron::opengl::Triangles::set(const std::vector<engine::Vertex_simple>& vertices)
{
  delete_buffers();

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


void apeiron::opengl::Triangles::set(const std::vector<engine::Vertex_normal>& vertices)
{
  delete_buffers();

  vertex_count_ = vertices.size();

  glGenVertexArrays(1, &vao_);
  glGenBuffers(1, &vbo_);
  glBindVertexArray(vao_);

  const int stride = sizeof(engine::Vertex_normal);

  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(engine::Vertex_normal),
      vertices.data(), GL_STATIC_DRAW);

  // Position
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(0));
  glEnableVertexAttribArray(0);
  // Normal
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride,
      reinterpret_cast<void*>(offsetof(engine::Vertex_normal, normal)));
  glEnableVertexAttribArray(1);
}


void apeiron::opengl::Triangles::set(const std::vector<engine::Vertex_color>& vertices)
{
  delete_buffers();

  vertex_count_ = vertices.size();

  glGenVertexArrays(1, &vao_);
  glGenBuffers(1, &vbo_);
  glBindVertexArray(vao_);

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


void apeiron::opengl::Triangles::set(const std::vector<engine::Vertex_texcoords>& vertices)
{
  delete_buffers();

  vertex_count_ = vertices.size();

  glGenVertexArrays(1, &vao_);
  glGenBuffers(1, &vbo_);
  glBindVertexArray(vao_);

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


void apeiron::opengl::Triangles::set(const std::vector<engine::Vertex_normal_color>& vertices)
{
  delete_buffers();

  vertex_count_ = vertices.size();

  glGenVertexArrays(1, &vao_);
  glGenBuffers(1, &vbo_);
  glBindVertexArray(vao_);

  const int stride = sizeof(engine::Vertex_normal_color);

  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(engine::Vertex_normal_color),
      vertices.data(), GL_STATIC_DRAW);

  // Position
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(0));
  glEnableVertexAttribArray(0);
  // Normal
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride,
      reinterpret_cast<void*>(offsetof(engine::Vertex_normal_color, normal)));
  glEnableVertexAttribArray(1);
  // Color
  glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, stride,
      reinterpret_cast<void*>(offsetof(engine::Vertex_normal_color, color)));
  glEnableVertexAttribArray(3);
}


void apeiron::opengl::Triangles::set(const std::vector<engine::Vertex_normal_texcoords>& vertices)
{
  delete_buffers();

  vertex_count_ = vertices.size();

  glGenVertexArrays(1, &vao_);
  glGenBuffers(1, &vbo_);
  glBindVertexArray(vao_);

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


void apeiron::opengl::Triangles::render() const
{
  glBindVertexArray(vao_);
  glDrawArrays(GL_TRIANGLES, 0, vertex_count_);
}


void apeiron::opengl::Triangles::render(std::uint32_t start, std::uint32_t count) const
{
  glBindVertexArray(vao_);
  glDrawArrays(GL_TRIANGLES, start, count);
}
