#include "triangles.h"


#include <cstddef>
#include <type_traits>
#include "GL/glew.h"


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
  glDrawArrays(GL_TRIANGLES, 0, vertex_count_);
}


void apeiron::opengl::Triangles::render(std::uint32_t start, std::uint32_t count) const
{
  glBindVertexArray(vao_);
  glDrawArrays(GL_TRIANGLES, start, count);
}


using namespace apeiron::engine;
using namespace apeiron::opengl;

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
