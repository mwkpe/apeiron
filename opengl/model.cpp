#include "model.h"


#include <vector>
#include "GL/glew.h"
#include "engine/model_loader.h"


void apeiron::opengl::Model::load(std::string_view filename)
{
  auto vertices = engine::load_vertices(filename);
  vertex_count_ = vertices.size() / 3;
  glGenVertexArrays(1, &vao_);
  glGenBuffers(1, &vbo_);
  glBindVertexArray(vao_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, static_cast<void*>(0));
  glEnableVertexAttribArray(0);
}


void apeiron::opengl::Model::render() const
{
  glBindVertexArray(vao_);
  glDrawArrays(GL_TRIANGLES, 0, vertex_count_);
}
