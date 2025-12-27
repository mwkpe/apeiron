#include "triangles.h"


#include <glad/glad.h>


template<typename T> apeiron::opengl::Triangles::Triangles(const std::vector<T>& vertices)
{
  set_buffers(vertices);
}


template<typename T> void apeiron::opengl::Triangles::set(const std::vector<T>& vertices)
{
  set_buffers(vertices);
}


void apeiron::opengl::Triangles::render() const
{
  glBindVertexArray(vao_);
  glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vertex_count_));
}


void apeiron::opengl::Triangles::render(std::uint32_t start, std::uint32_t count) const
{
  glBindVertexArray(vao_);
  glDrawArrays(GL_TRIANGLES, static_cast<GLint>(start), static_cast<GLsizei>(count));
}


namespace apeiron::opengl {


template Triangles::Triangles(const std::vector<apeiron::engine::Vertex>&);
template Triangles::Triangles(const std::vector<apeiron::engine::Vertex_simple>&);
template Triangles::Triangles(const std::vector<apeiron::engine::Vertex_normal>&);
template Triangles::Triangles(const std::vector<apeiron::engine::Vertex_color>&);
template Triangles::Triangles(const std::vector<apeiron::engine::Vertex_texcoords>&);
template Triangles::Triangles(const std::vector<apeiron::engine::Vertex_normal_color>&);
template Triangles::Triangles(const std::vector<apeiron::engine::Vertex_normal_texcoords>&);

template void Triangles::set(const std::vector<apeiron::engine::Vertex>&);
template void Triangles::set(const std::vector<apeiron::engine::Vertex_simple>&);
template void Triangles::set(const std::vector<apeiron::engine::Vertex_normal>&);
template void Triangles::set(const std::vector<apeiron::engine::Vertex_color>&);
template void Triangles::set(const std::vector<apeiron::engine::Vertex_texcoords>&);
template void Triangles::set(const std::vector<apeiron::engine::Vertex_normal_color>&);
template void Triangles::set(const std::vector<apeiron::engine::Vertex_normal_texcoords>&);


}  // namespace apeiron::opengl
