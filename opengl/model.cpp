#include "model.h"


#include <vector>
#include "GL/glew.h"
#include "engine/model_flags.h"
#include "engine/model_loader.h"


void apeiron::opengl::Model::load(std::string_view filename, std::uint32_t flags)
{
  delete_buffers();

  auto&& [vertices, values_per_vertex] = engine::load_model(filename, flags);
  vertex_count_ = vertices.size() / values_per_vertex;
  glGenVertexArrays(1, &vao_);
  glGenBuffers(1, &vbo_);
  glBindVertexArray(vao_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
  const int stride = values_per_vertex * sizeof(float);
  int offset = 0;
  namespace mf = engine::model_flags;
  if (flags & mf::vertices) {
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(offset));
    glEnableVertexAttribArray(0);
    offset += 3 * sizeof(float);
  }
  if (flags & mf::normals) {
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(offset));
    glEnableVertexAttribArray(1);
    offset += 3 * sizeof(float);
  }
  if (flags & mf::texcoords) {
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(offset));
    glEnableVertexAttribArray(2);
    offset += 2 * sizeof(float);
  }
  if (flags & mf::colors) {
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(offset));
    glEnableVertexAttribArray(3);
  }
}


void apeiron::opengl::Model::render() const
{
  glBindVertexArray(vao_);
  glDrawArrays(GL_TRIANGLES, 0, vertex_count_);
}
