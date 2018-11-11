#include "cuboid.h"


#include <tuple>
#include <vector>
#include <cstddef>
#include "GL/glew.h"
#include "engine/vertex.h"
#include "engine/primitive.h"


apeiron::opengl::Cuboid::Cuboid(glm::vec3 size, glm::vec3 position)
{
  set(size, position);
}


apeiron::opengl::Cuboid::Cuboid(glm::vec3 size, glm::vec4 color, glm::vec3 position)
{
  set(size, color, position);
}


void apeiron::opengl::Cuboid::set(glm::vec3 size, glm::vec3 position)
{
  using namespace apeiron::engine;

  delete_buffers();
  glGenVertexArrays(1, &vao_);
  glGenBuffers(1, &vbo_);
  glBindVertexArray(vao_);

  const auto vertices = primitive::cube_vertices<Vertex_normal_texcoords>(size, position);
  vertex_count_ = vertices.size();
  const int stride = sizeof(Vertex_normal_texcoords);

  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex_normal_texcoords),
      vertices.data(), GL_STATIC_DRAW);

  // Position
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(0));
  glEnableVertexAttribArray(0);
  // Normal
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride,
      reinterpret_cast<void*>(offsetof(Vertex_normal_texcoords, normal)));
  glEnableVertexAttribArray(1);
  // Texture coordinates
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride,
      reinterpret_cast<void*>(offsetof(Vertex_normal_texcoords, texcoords)));
  glEnableVertexAttribArray(2);
}


void apeiron::opengl::Cuboid::set(glm::vec3 size, glm::vec4 color, glm::vec3 position)
{
  using namespace apeiron::engine;

  delete_buffers();
  glGenVertexArrays(1, &vao_);
  glGenBuffers(1, &vbo_);
  glBindVertexArray(vao_);

  const auto vertices = primitive::cube_vertices<Vertex>(size, color, position);
  vertex_count_ = vertices.size();
  const int stride = sizeof(Vertex);

  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex),
      vertices.data(), GL_STATIC_DRAW);

  // Position
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(0));
  glEnableVertexAttribArray(0);
  // Normal
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride,
      reinterpret_cast<void*>(offsetof(Vertex, normal)));
  glEnableVertexAttribArray(1);
  // Texture coordinates
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride,
      reinterpret_cast<void*>(offsetof(Vertex, texcoords)));
  glEnableVertexAttribArray(2);
  // Color
  glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, stride,
      reinterpret_cast<void*>(offsetof(Vertex, color)));
  glEnableVertexAttribArray(3);
}


void apeiron::opengl::Cuboid::render() const
{
  glBindVertexArray(vao_);
  glDrawArrays(GL_TRIANGLES, 0, vertex_count_);
}
