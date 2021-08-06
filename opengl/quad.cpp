#include "quad.h"


#include <vector>
#include <cstddef>
#include <glad/glad.h>


apeiron::opengl::Quad::Quad(float width, float height, engine::Face face,
    glm::vec3 position)
{
  set(width, height, face, position);
}


apeiron::opengl::Quad::Quad(float width, float height, glm::vec4 color,
    engine::Face face, glm::vec3 position)
{
  set(width, height, color, face, position);
}


template<typename T> void apeiron::opengl::Quad::set(float width, float height,
    engine::Face face, glm::vec3 position)
{
  set_buffers(engine::primitive::quad_vertices<T>(width, height, face, position));
}


template<typename T> void apeiron::opengl::Quad::set(float width, float height,
    glm::vec4 color, engine::Face face, glm::vec3 position)
{
  set_buffers(engine::primitive::quad_vertices<T>(width, height, color, face, position));
}


void apeiron::opengl::Quad::render() const
{
  glBindVertexArray(vao_);
  glDrawArrays(GL_TRIANGLES, 0, vertex_count_);
}


using namespace apeiron::engine;
using namespace apeiron::engine::primitive;
using namespace apeiron::opengl;

template void Quad::set<Vertex>(float, float, Face, glm::vec3);
template void Quad::set<Vertex>(float, float, glm::vec4, Face, glm::vec3);
template void Quad::set<Vertex_simple>(float, float, Face, glm::vec3);
template void Quad::set<Vertex_normal>(float, float, Face, glm::vec3);
template void Quad::set<Vertex_color>(float, float, glm::vec4, Face, glm::vec3);
template void Quad::set<Vertex_texcoords>(float, float, Face, glm::vec3);
template void Quad::set<Vertex_normal_color>(float, float, glm::vec4, Face, glm::vec3);
template void Quad::set<Vertex_normal_texcoords>(float, float, Face, glm::vec3);
