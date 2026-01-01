#include "vertex_array.h"


#include <cassert>
#include <type_traits>
#include <glad/glad.h>


namespace {


template<typename T> concept has_normal = requires(T v) {
  { v.normal } -> std::same_as<glm::vec3&>;
};

template<typename T> concept has_texcoords = requires(T v) {
  { v.texcoords } -> std::same_as<glm::vec2&>;
};

template<typename T> concept has_color = requires(T v) {
  { v.color } -> std::same_as<glm::vec4&>;
};

template<typename T> concept index_vertex = requires(T v) {
  { v.position } -> std::same_as<std::uint16_t&>;
  { v.color } -> std::same_as<std::uint8_t&>;
  { v.material } -> std::same_as<std::uint8_t&>;
};


GLenum as_gl(apeiron::opengl::Usage_hint hint)
{
  switch (hint) {
    case apeiron::opengl::Usage_hint::Static: return GL_STATIC_DRAW;
    case apeiron::opengl::Usage_hint::Dynamic: return GL_DYNAMIC_DRAW;
    case apeiron::opengl::Usage_hint::Stream: return GL_STREAM_DRAW;
  }

  return GL_STATIC_DRAW;
}


}  // namespace


apeiron::opengl::Vertex_array::Vertex_array()
{
  usage_hint_ = GL_STATIC_DRAW;
}


apeiron::opengl::Vertex_array::Vertex_array(Vertex_array&& other) noexcept
{
  vbo_ = other.vbo_;
  vao_ = other.vao_;
  vertex_size_ = other.vertex_size_;
  vertex_count_ = other.vertex_count_;
  usage_hint_ = other.usage_hint_;

  other.vbo_ = 0;
  other.vao_ = 0;
  other.vertex_size_ = 0;
  other.vertex_count_ = 0;
  other.usage_hint_ = GL_STATIC_DRAW;
}


auto apeiron::opengl::Vertex_array::operator=(Vertex_array&& other) noexcept -> Vertex_array&
{
  if (&other == this) {
    return *this;
  }

  delete_buffers();

  vbo_ = other.vbo_;
  vao_ = other.vao_;
  vertex_size_ = other.vertex_size_;
  vertex_count_ = other.vertex_count_;
  usage_hint_ = other.usage_hint_;

  other.vbo_ = 0;
  other.vao_ = 0;
  other.vertex_size_ = 0;
  other.vertex_count_ = 0;
  other.usage_hint_ = GL_STATIC_DRAW;

  return *this;
}


apeiron::opengl::Vertex_array::~Vertex_array()
{
  delete_buffers();
}


void apeiron::opengl::Vertex_array::delete_buffers()
{
  if (vbo_) {
    glDeleteBuffers(1, &vbo_);
  }
  
  if (vao_) {
    glDeleteVertexArrays(1, &vao_);
  }

  vao_ = 0;
  vbo_ = 0;
  vertex_size_ = 0;
  vertex_count_ = 0;
  usage_hint_ = GL_STATIC_DRAW;
}


template<typename T> void apeiron::opengl::Vertex_array::set_buffers(const std::vector<T>& vertices,
    Usage_hint hint)
{
  delete_buffers();
  glGenVertexArrays(1, &vao_);
  glGenBuffers(1, &vbo_);
  glBindVertexArray(vao_);

  vertex_size_ = sizeof(T);
  vertex_count_ = vertices.size();
  usage_hint_ = as_gl(hint);
  const auto stride = static_cast<int>(vertex_size_);

  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, vertex_count_ * vertex_size_, vertices.data(), usage_hint_);

  if constexpr (!index_vertex<T>) {
    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);

    // Normal
    if constexpr (has_normal<T>) {
      glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride,
          reinterpret_cast<void*>(offsetof(T, normal)));
      glEnableVertexAttribArray(1);
    }

    // Texture coordinates
    if constexpr (has_texcoords<T>) {
      glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride,
          reinterpret_cast<void*>(offsetof(T, texcoords)));
      glEnableVertexAttribArray(2);
    }

    // Color
    if constexpr (has_color<T>) {
      glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, stride,
          reinterpret_cast<void*>(offsetof(T, color)));
      glEnableVertexAttribArray(3);
    }
  }
  else {
    // Position index
    glVertexAttribIPointer(0, 1, GL_UNSIGNED_SHORT, stride, reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);

    // Color index
    glVertexAttribIPointer(1, 1, GL_UNSIGNED_BYTE, stride,
        reinterpret_cast<void*>(offsetof(T, color)));
    glEnableVertexAttribArray(1);

    // Material index
    glVertexAttribIPointer(2, 1, GL_UNSIGNED_BYTE, stride,
        reinterpret_cast<void*>(offsetof(T, material)));
    glEnableVertexAttribArray(2);
  }
}


template<typename T> void apeiron::opengl::Vertex_array::update_buffers(const std::vector<T>& vertices)
{
  assert(vertex_size_ == sizeof(T));
  assert(vao_ != 0);
  assert(vbo_ != 0);

  vertex_count_ = vertices.size();

  glBindVertexArray(vao_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);

  // Use sizeof(T) since vertex_size_ records how the VAO was setup by set_buffers
  glBufferData(GL_ARRAY_BUFFER, vertex_count_ * sizeof(T), vertices.data(), usage_hint_);
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


template void Vertex_array::set_buffers(const std::vector<Vertex>&, Usage_hint);
template void Vertex_array::set_buffers(const std::vector<Vertex_simple>&, Usage_hint);
template void Vertex_array::set_buffers(const std::vector<Vertex_normal>&, Usage_hint);
template void Vertex_array::set_buffers(const std::vector<Vertex_color>&, Usage_hint);
template void Vertex_array::set_buffers(const std::vector<Vertex_texcoords>&, Usage_hint);
template void Vertex_array::set_buffers(const std::vector<Vertex_normal_color>&, Usage_hint);
template void Vertex_array::set_buffers(const std::vector<Vertex_normal_texcoords>&, Usage_hint);
template void Vertex_array::set_buffers(const std::vector<Vertex_index>&, Usage_hint);


template void Vertex_array::update_buffers(const std::vector<Vertex>&);
template void Vertex_array::update_buffers(const std::vector<Vertex_simple>&);
template void Vertex_array::update_buffers(const std::vector<Vertex_normal>&);
template void Vertex_array::update_buffers(const std::vector<Vertex_color>&);
template void Vertex_array::update_buffers(const std::vector<Vertex_texcoords>&);
template void Vertex_array::update_buffers(const std::vector<Vertex_normal_color>&);
template void Vertex_array::update_buffers(const std::vector<Vertex_normal_texcoords>&);
template void Vertex_array::update_buffers(const std::vector<Vertex_index>&);


}  // namespace apeiron::opengl
