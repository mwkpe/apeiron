#include "mesh.h"


#include <glad/glad.h>
#include "apeiron/engine/vertex.h"


template<typename T> void apeiron::opengl::Mesh::init(const std::vector<T>& vertices,
    Usage_hint hint)
{
  set_buffers(vertices, hint);
}


template<typename T> void apeiron::opengl::Mesh::update(const std::vector<T>& vertices)
{
  update_buffers(vertices);
}


void apeiron::opengl::Mesh::render() const
{
  glBindVertexArray(vao_);
  glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vertex_count_));
}


void apeiron::opengl::Mesh::render_batched(std::uint32_t count) const
{
  glBindVertexArray(vao_);
  glMultiDrawArraysIndirect(GL_TRIANGLES, nullptr, static_cast<GLint>(count), 0);
}


void apeiron::opengl::Mesh::render_points_batched(std::uint32_t count) const
{
  glBindVertexArray(vao_);
  glMultiDrawArraysIndirect(GL_POINTS, 0, static_cast<GLint>(count), 0);
}


using apeiron::engine::Vertex;
using apeiron::engine::Vertex_simple;
using apeiron::engine::Vertex_normal;
using apeiron::engine::Vertex_color;
using apeiron::engine::Vertex_texcoords;
using apeiron::engine::Vertex_normal_color;
using apeiron::engine::Vertex_normal_texcoords;
using apeiron::engine::Vertex_index;
using apeiron::opengl::Usage_hint;


namespace apeiron::opengl {


template void Mesh::init(const std::vector<Vertex>&, Usage_hint);
template void Mesh::init(const std::vector<Vertex_simple>&, Usage_hint);
template void Mesh::init(const std::vector<Vertex_color>&, Usage_hint);
template void Mesh::init(const std::vector<Vertex_normal>&, Usage_hint);
template void Mesh::init(const std::vector<Vertex_texcoords>&, Usage_hint);
template void Mesh::init(const std::vector<Vertex_normal_color>&, Usage_hint);
template void Mesh::init(const std::vector<Vertex_normal_texcoords>&, Usage_hint);
template void Mesh::init(const std::vector<Vertex_index>&, Usage_hint);

template void Mesh::update(const std::vector<Vertex>&);
template void Mesh::update(const std::vector<Vertex_simple>&);
template void Mesh::update(const std::vector<Vertex_normal>&);
template void Mesh::update(const std::vector<Vertex_color>&);
template void Mesh::update(const std::vector<Vertex_texcoords>&);
template void Mesh::update(const std::vector<Vertex_normal_color>&);
template void Mesh::update(const std::vector<Vertex_normal_texcoords>&);
template void Mesh::update(const std::vector<Vertex_index>&);


}  // namespace apeiron::opengl
