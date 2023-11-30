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


template void apeiron::opengl::Quad::set<apeiron::engine::Vertex>(float, float, apeiron::engine::Face, const glm::vec3&);
template void apeiron::opengl::Quad::set<apeiron::engine::Vertex>(float, float, const glm::vec4&, apeiron::engine::Face, const glm::vec3&);
template void apeiron::opengl::Quad::set<apeiron::engine::Vertex>(float, float, const glm::mat4&, apeiron::engine::Face, const glm::vec3&);
template void apeiron::opengl::Quad::set<apeiron::engine::Vertex_simple>(float, float, apeiron::engine::Face, const glm::vec3&);
template void apeiron::opengl::Quad::set<apeiron::engine::Vertex_normal>(float, float, apeiron::engine::Face, const glm::vec3&);
template void apeiron::opengl::Quad::set<apeiron::engine::Vertex_color>(float, float, const glm::vec4&, apeiron::engine::Face, const glm::vec3&);
template void apeiron::opengl::Quad::set<apeiron::engine::Vertex_color>(float, float, const glm::mat4&, apeiron::engine::Face, const glm::vec3&);
template void apeiron::opengl::Quad::set<apeiron::engine::Vertex_texcoords>(float, float, apeiron::engine::Face, const glm::vec3&);
template void apeiron::opengl::Quad::set<apeiron::engine::Vertex_normal_color>(float, float, const glm::vec4&, apeiron::engine::Face, const glm::vec3&);
template void apeiron::opengl::Quad::set<apeiron::engine::Vertex_normal_texcoords>(float, float, apeiron::engine::Face, const glm::vec3&);
