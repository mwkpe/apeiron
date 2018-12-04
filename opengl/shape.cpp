#include "shape.h"


#include "GL/glew.h"


apeiron::opengl::Shape::Shape(Shape&& other) noexcept
{
  vbo_ = other.vbo_;
  ebo_ = other.ebo_;
  vao_ = other.vao_;
  vertex_count_ = other.vertex_count_;
  element_count_ = other.element_count_;

  other.vbo_ = 0;
  other.ebo_ = 0;
  other.vao_ = 0;
  other.vertex_count_ = 0;
  other.element_count_ = 0;
}


auto apeiron::opengl::Shape::operator=(Shape&& other) noexcept -> Shape&
{
  if (&other == this)
    return *this;

  delete_buffers();

  vbo_ = other.vbo_;
  ebo_ = other.ebo_;
  vao_ = other.vao_;
  vertex_count_ = other.vertex_count_;
  element_count_ = other.element_count_;

  other.vbo_ = 0;
  other.ebo_ = 0;
  other.vao_ = 0;
  other.vertex_count_ = 0;
  other.element_count_ = 0;

  return *this;
}


apeiron::opengl::Shape::~Shape()
{
  delete_buffers();
}


void apeiron::opengl::Shape::delete_buffers()
{
  if (vbo_)
    glDeleteBuffers(1, &vbo_);
  if (ebo_)
    glDeleteBuffers(1, &ebo_);
  if (vao_)
    glDeleteVertexArrays(1, &vao_);

  vertex_count_ = 0;
  element_count_ = 0;
}


template<typename T> void apeiron::opengl::Shape::set_buffers(const std::vector<T>& vertices)
{
  using namespace apeiron::engine;

  delete_buffers();
  glGenVertexArrays(1, &vao_);
  glGenBuffers(1, &vbo_);
  glBindVertexArray(vao_);

  vertex_count_ = vertices.size();
  const int stride = sizeof(T);

  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(T), vertices.data(), GL_STATIC_DRAW);

  // Position
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(0));
  glEnableVertexAttribArray(0);

  // Normal
  if constexpr (std::is_same<T, Vertex>::value ||
      std::is_same<T, Vertex_normal>::value ||
      std::is_same<T, Vertex_normal_color>::value ||
      std::is_same<T, Vertex_normal_texcoords>::value) {
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride,
        reinterpret_cast<void*>(offsetof(T, normal)));
    glEnableVertexAttribArray(1);
  }

  // Texture coordinates
  if constexpr (std::is_same<T, Vertex>::value ||
      std::is_same<T, Vertex_texcoords>::value ||
      std::is_same<T, Vertex_normal_texcoords>::value) {
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride,
        reinterpret_cast<void*>(offsetof(T, texcoords)));
    glEnableVertexAttribArray(2);
  }

  // Color
  if constexpr (std::is_same<T, Vertex>::value ||
      std::is_same<T, Vertex_color>::value ||
      std::is_same<T, Vertex_normal_color>::value) {
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, stride,
        reinterpret_cast<void*>(offsetof(T, color)));
    glEnableVertexAttribArray(3);
  }
}


using namespace apeiron::engine;
using namespace apeiron::opengl;

template void Shape::set_buffers(const std::vector<Vertex>&);
template void Shape::set_buffers(const std::vector<Vertex_simple>&);
template void Shape::set_buffers(const std::vector<Vertex_normal>&);
template void Shape::set_buffers(const std::vector<Vertex_color>&);
template void Shape::set_buffers(const std::vector<Vertex_texcoords>&);
template void Shape::set_buffers(const std::vector<Vertex_normal_color>&);
template void Shape::set_buffers(const std::vector<Vertex_normal_texcoords>&);
