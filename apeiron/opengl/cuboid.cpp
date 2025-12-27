#include "cuboid.h"


#include <tuple>
#include <vector>
#include <cstddef>
#include <glad/glad.h>
#include "apeiron/engine/vertex.h"
#include "apeiron/engine/primitive.h"


apeiron::opengl::Cuboid::Cuboid(const glm::vec3& size, const glm::vec3& position)
{
  set(size, position);
}


apeiron::opengl::Cuboid::Cuboid(const glm::vec3& size, const glm::vec4& color,
    const glm::vec3& position)
{
  set(size, color, position);
}


template<typename T> void apeiron::opengl::Cuboid::set(const glm::vec3& size, const glm::vec3& position)
{
  set_buffers(engine::primitive::cuboid_vertices<T>(size, position));
}


template<typename T> void apeiron::opengl::Cuboid::set(const glm::vec3& size, const glm::vec4& color,
    const glm::vec3& position)
{
  set_buffers(engine::primitive::cuboid_vertices<T>(size, color, position));
}


void apeiron::opengl::Cuboid::render() const
{
  glBindVertexArray(vao_);
  glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vertex_count_));
}


using apeiron::engine::Vertex;
using apeiron::engine::Vertex_simple;
using apeiron::engine::Vertex_normal;
using apeiron::engine::Vertex_color;
using apeiron::engine::Vertex_texcoords;
using apeiron::engine::Vertex_normal_color;
using apeiron::engine::Vertex_normal_texcoords;
using apeiron::engine::Vertex_index;


namespace apeiron::opengl {


template void Cuboid::set<Vertex>(const glm::vec3&, const glm::vec3&);
template void Cuboid::set<Vertex>(const glm::vec3&, const glm::vec4&, const glm::vec3&);
template void Cuboid::set<Vertex_simple>(const glm::vec3&, const glm::vec3&);
template void Cuboid::set<Vertex_normal>(const glm::vec3&, const glm::vec3&);
template void Cuboid::set<Vertex_color>(const glm::vec3&, const glm::vec4&, const glm::vec3&);
template void Cuboid::set<Vertex_texcoords>(const glm::vec3&, const glm::vec3&);
template void Cuboid::set<Vertex_normal_color>(const glm::vec3&, const glm::vec4&, const glm::vec3&);
template void Cuboid::set<Vertex_normal_texcoords>(const glm::vec3&, const glm::vec3&);


}  // namespace apeiron::opengl
