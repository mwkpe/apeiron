#include "triangles.h"


#include <cstddef>
#include <type_traits>
#include "GL/glew.h"


template<typename T> apeiron::opengl::Triangles::Triangles(const std::vector<T>& vertices)
{
  set(vertices);
}


template<typename T> void apeiron::opengl::Triangles::set(const std::vector<T>& vertices)
{
  using namespace apeiron::engine;

  delete_buffers();
  glGenVertexArrays(1, &vao_);
  glGenBuffers(1, &vbo_);
  glBindVertexArray(vao_);

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


namespace apeiron::opengl {


using namespace apeiron::engine;


template Triangles::Triangles(const std::vector<Vertex>& vertices);
template Triangles::Triangles(const std::vector<Vertex_simple>& vertices);
template Triangles::Triangles(const std::vector<Vertex_normal>& vertices);
template Triangles::Triangles(const std::vector<Vertex_color>& vertices);
template Triangles::Triangles(const std::vector<Vertex_texcoords>& vertices);
template Triangles::Triangles(const std::vector<Vertex_normal_color>& vertices);
template Triangles::Triangles(const std::vector<Vertex_normal_texcoords>& vertices);


template void Triangles::set(const std::vector<Vertex>& vertices);
template void Triangles::set(const std::vector<Vertex_simple>& vertices);
template void Triangles::set(const std::vector<Vertex_normal>& vertices);
template void Triangles::set(const std::vector<Vertex_color>& vertices);
template void Triangles::set(const std::vector<Vertex_texcoords>& vertices);
template void Triangles::set(const std::vector<Vertex_normal_color>& vertices);
template void Triangles::set(const std::vector<Vertex_normal_texcoords>& vertices);


}  // apeiron::opengl
