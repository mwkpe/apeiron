#include "cuboid.h"


#include <tuple>
#include <vector>
#include <cstddef>
#include <glad/glad.h>
#include "engine/vertex.h"
#include "engine/primitive.h"


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
  glDrawArrays(GL_TRIANGLES, 0, vertex_count_);
}


template void apeiron::opengl::Cuboid::set<apeiron::engine::Vertex>(const glm::vec3&, const glm::vec3&);
template void apeiron::opengl::Cuboid::set<apeiron::engine::Vertex>(const glm::vec3&, const glm::vec4&, const glm::vec3&);
template void apeiron::opengl::Cuboid::set<apeiron::engine::Vertex_simple>(const glm::vec3&, const glm::vec3&);
template void apeiron::opengl::Cuboid::set<apeiron::engine::Vertex_normal>(const glm::vec3&, const glm::vec3&);
template void apeiron::opengl::Cuboid::set<apeiron::engine::Vertex_color>(const glm::vec3&, const glm::vec4&, const glm::vec3&);
template void apeiron::opengl::Cuboid::set<apeiron::engine::Vertex_texcoords>(const glm::vec3&, const glm::vec3&);
template void apeiron::opengl::Cuboid::set<apeiron::engine::Vertex_normal_color>(const glm::vec3&, const glm::vec4&, const glm::vec3&);
template void apeiron::opengl::Cuboid::set<apeiron::engine::Vertex_normal_texcoords>(const glm::vec3&, const glm::vec3&);
