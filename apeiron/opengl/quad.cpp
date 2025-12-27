#include "quad.h"


#include <glad/glad.h>


apeiron::opengl::Quad::Quad(float width, float height, engine::Face face,
    const glm::vec3& position)
{
  set(width, height, face, position);
}


apeiron::opengl::Quad::Quad(float width, float height, const glm::vec4& color,
    engine::Face face, const glm::vec3& position)
{
  set(width, height, color, face, position);
}


template<typename T> void apeiron::opengl::Quad::set(float width, float height,
    engine::Face face, const glm::vec3& position)
{
  set_buffers(engine::primitive::quad_vertices<T>(width, height, face, position));
}


template<typename T> void apeiron::opengl::Quad::set(float width, float height,
    const glm::vec4& color, engine::Face face, const glm::vec3& position)
{
  set_buffers(engine::primitive::quad_vertices<T>(width, height, color, face, position));
}


template<typename T> void apeiron::opengl::Quad::set(float width, float height,
    const glm::mat4& color, engine::Face face, const glm::vec3& position)
{
  set_buffers(engine::primitive::quad_vertices<T>(width, height, color, face, position));
}


void apeiron::opengl::Quad::render() const
{
  glBindVertexArray(vao_);
  glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vertex_count_));
}


using apeiron::engine::Face;
using apeiron::engine::Vertex;
using apeiron::engine::Vertex_simple;
using apeiron::engine::Vertex_normal;
using apeiron::engine::Vertex_color;
using apeiron::engine::Vertex_texcoords;
using apeiron::engine::Vertex_normal_color;
using apeiron::engine::Vertex_normal_texcoords;
using apeiron::engine::Vertex_index;


namespace apeiron::opengl {


template void Quad::set<Vertex>(float, float, Face, const glm::vec3&);
template void Quad::set<Vertex>(float, float, const glm::vec4&, Face, const glm::vec3&);
template void Quad::set<Vertex>(float, float, const glm::mat4&, Face, const glm::vec3&);
template void Quad::set<Vertex_simple>(float, float, Face, const glm::vec3&);
template void Quad::set<Vertex_normal>(float, float, Face, const glm::vec3&);
template void Quad::set<Vertex_color>(float, float, const glm::vec4&, Face, const glm::vec3&);
template void Quad::set<Vertex_color>(float, float, const glm::mat4&, Face, const glm::vec3&);
template void Quad::set<Vertex_texcoords>(float, float, Face, const glm::vec3&);
template void Quad::set<Vertex_normal_color>(float, float, const glm::vec4&, Face, const glm::vec3&);
template void Quad::set<Vertex_normal_texcoords>(float, float, Face, const glm::vec3&);


}  // namespace apeiron::opengl
