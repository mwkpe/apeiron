#include "model.h"


#include <vector>
#include "GL/glew.h"
#include "engine/model_loader.h"


template<typename T> void apeiron::opengl::Model::load(std::string_view filename)
{
  using namespace apeiron::engine;

  delete_buffers();
  glGenVertexArrays(1, &vao_);
  glGenBuffers(1, &vbo_);
  glBindVertexArray(vao_);

  auto vertices = load_model<T>(filename);
  vertex_count_ = vertices.size();
  const int stride = sizeof(T);

  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(T),
      vertices.data(), GL_STATIC_DRAW);

  // Position
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(0));
  glEnableVertexAttribArray(0);

  // Normal
  if constexpr (std::is_same<T, Vertex>::value ||
      std::is_same<T, Vertex_normal>::value ||
      std::is_same<T, Vertex_normal_color>::value ||
      std::is_same<T, Vertex_normal_texcoords>::value) {
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride,
        reinterpret_cast<void*>(offsetof(T, normal)));
    glEnableVertexAttribArray(1);
  }

  // Texture coordinates
  if constexpr (std::is_same<T, Vertex>::value ||
      std::is_same<T, Vertex_texcoords>::value ||
      std::is_same<T, Vertex_normal_texcoords>::value) {
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride,
        reinterpret_cast<void*>(offsetof(T, texcoords)));
    glEnableVertexAttribArray(2);
  }

  // Color
  if constexpr (std::is_same<T, Vertex>::value ||
      std::is_same<T, Vertex_color>::value ||
      std::is_same<T, Vertex_normal_color>::value) {
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, stride,
        reinterpret_cast<void*>(offsetof(T, color)));
    glEnableVertexAttribArray(3);
  }
}


void apeiron::opengl::Model::render() const
{
  glBindVertexArray(vao_);
  glDrawArrays(GL_TRIANGLES, 0, vertex_count_);
}


using namespace apeiron::engine;
using namespace apeiron::opengl;


template void Model::load<Vertex>(std::string_view filename);
template void Model::load<Vertex_simple>(std::string_view filename);
template void Model::load<Vertex_normal>(std::string_view filename);
template void Model::load<Vertex_color>(std::string_view filename);
template void Model::load<Vertex_texcoords>(std::string_view filename);
template void Model::load<Vertex_normal_color>(std::string_view filename);
template void Model::load<Vertex_normal_texcoords>(std::string_view filename);
