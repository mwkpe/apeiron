#include "cuboid.h"


#include <tuple>
#include <vector>
#include <cstddef>
#include <glad/glad.h>
#include "engine/vertex.h"
#include "engine/primitive.h"


apeiron::opengl::Cuboid::Cuboid(glm::vec3 size, glm::vec3 position)
{
  set(size, position);
}


apeiron::opengl::Cuboid::Cuboid(glm::vec3 size, glm::vec4 color,
    glm::vec3 position)
{
  set(size, color, position);
}


template<typename T> void apeiron::opengl::Cuboid::set(glm::vec3 size, glm::vec3 position)
{
  set_buffers(engine::primitive::cuboid_vertices<T>(size, position));
}


template<typename T> void apeiron::opengl::Cuboid::set(glm::vec3 size, glm::vec4 color,
    glm::vec3 position)
{
  set_buffers(engine::primitive::cuboid_vertices<T>(size, color, position));
}


void apeiron::opengl::Cuboid::render() const
{
  glBindVertexArray(vao_);
  glDrawArrays(GL_TRIANGLES, 0, vertex_count_);
}


using namespace apeiron::engine;
using namespace apeiron::opengl;

template void Cuboid::set<Vertex>(glm::vec3, glm::vec3);
template void Cuboid::set<Vertex>(glm::vec3, glm::vec4, glm::vec3);
template void Cuboid::set<Vertex_simple>(glm::vec3, glm::vec3);
template void Cuboid::set<Vertex_normal>(glm::vec3, glm::vec3);
template void Cuboid::set<Vertex_color>(glm::vec3, glm::vec4, glm::vec3);
template void Cuboid::set<Vertex_texcoords>(glm::vec3, glm::vec3);
template void Cuboid::set<Vertex_normal_color>(glm::vec3, glm::vec4, glm::vec3);
template void Cuboid::set<Vertex_normal_texcoords>(glm::vec3, glm::vec3);
