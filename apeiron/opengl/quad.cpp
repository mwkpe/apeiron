#include "quad.h"


#include <glad/glad.h>


apeiron::opengl::Quad::Quad(float width, float height, engine::Face face,
    const glm::vec3& position)
{
  init(width, height, face, position);
}


apeiron::opengl::Quad::Quad(float width, float height, const glm::vec4& color,
    engine::Face face, const glm::vec3& position)
{
  init(width, height, color, face, position);
}


apeiron::opengl::Quad::Quad(float width, float height, const glm::mat4& color,
    engine::Face face, const glm::vec3& position)
{
  init(width, height, color, face, position);
}


apeiron::opengl::Quad::Quad(const glm::vec2& size, engine::Face face, const glm::vec3& position)
{
  init(size, face, position);
}


apeiron::opengl::Quad::Quad(const glm::vec2& size, const glm::vec4& color, engine::Face face,
    const glm::vec3& position)
{
  init(size, color, face, position);
}


apeiron::opengl::Quad::Quad(const glm::vec2& size, const glm::mat4& color, engine::Face face,
    const glm::vec3& position)
{
  init(size, color, face, position);
}


template<typename T> void apeiron::opengl::Quad::init(float width, float height,
    engine::Face face, const glm::vec3& position)
{
  set_buffers(engine::primitive::quad_vertices<T>(width, height, face, position));
}


template<typename T> void apeiron::opengl::Quad::init(float width, float height,
    const glm::vec4& color, engine::Face face, const glm::vec3& position)
{
  set_buffers(engine::primitive::quad_vertices<T>(width, height, color, face, position));
}


template<typename T> void apeiron::opengl::Quad::init(float width, float height,
    const glm::mat4& color, engine::Face face, const glm::vec3& position)
{
  set_buffers(engine::primitive::quad_vertices<T>(width, height, color, face, position));
}


template<typename T> void apeiron::opengl::Quad::init(const glm::vec2& size,
    engine::Face face, const glm::vec3& position)
{
  set_buffers(engine::primitive::quad_vertices<T>(size, face, position));
}


template<typename T> void apeiron::opengl::Quad::init(const glm::vec2& size,
    const glm::vec4& color, engine::Face face, const glm::vec3& position)
{
  set_buffers(engine::primitive::quad_vertices<T>(size, color, face, position));
}


template<typename T> void apeiron::opengl::Quad::init(const glm::vec2& size,
    const glm::mat4& color, engine::Face face, const glm::vec3& position)
{
  set_buffers(engine::primitive::quad_vertices<T>(size, color, face, position));
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


template void Quad::init<Vertex>(float, float, Face, const glm::vec3&);
template void Quad::init<Vertex>(float, float, const glm::vec4&, Face, const glm::vec3&);
template void Quad::init<Vertex>(float, float, const glm::mat4&, Face, const glm::vec3&);
template void Quad::init<Vertex_simple>(float, float, Face, const glm::vec3&);
template void Quad::init<Vertex_normal>(float, float, Face, const glm::vec3&);
template void Quad::init<Vertex_color>(float, float, const glm::vec4&, Face, const glm::vec3&);
template void Quad::init<Vertex_color>(float, float, const glm::mat4&, Face, const glm::vec3&);
template void Quad::init<Vertex_texcoords>(float, float, Face, const glm::vec3&);
template void Quad::init<Vertex_normal_color>(float, float, const glm::vec4&, Face, const glm::vec3&);
template void Quad::init<Vertex_normal_texcoords>(float, float, Face, const glm::vec3&);

template void Quad::init<Vertex>(const glm::vec2&,Face, const glm::vec3&);
template void Quad::init<Vertex>(const glm::vec2&,const glm::vec4&, Face, const glm::vec3&);
template void Quad::init<Vertex>(const glm::vec2&,const glm::mat4&, Face, const glm::vec3&);
template void Quad::init<Vertex_simple>(const glm::vec2&,Face, const glm::vec3&);
template void Quad::init<Vertex_normal>(const glm::vec2&,Face, const glm::vec3&);
template void Quad::init<Vertex_color>(const glm::vec2&,const glm::vec4&, Face, const glm::vec3&);
template void Quad::init<Vertex_color>(const glm::vec2&,const glm::mat4&, Face, const glm::vec3&);
template void Quad::init<Vertex_texcoords>(const glm::vec2&,Face, const glm::vec3&);
template void Quad::init<Vertex_normal_color>(const glm::vec2&,const glm::vec4&, Face, const glm::vec3&);
template void Quad::init<Vertex_normal_texcoords>(const glm::vec2&,Face, const glm::vec3&);


}  // namespace apeiron::opengl
