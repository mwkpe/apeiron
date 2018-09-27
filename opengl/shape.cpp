#include "shape.h"


#include "GL/glew.h"


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
}


auto apeiron::opengl::Shape::operator=(Shape&& other) -> Shape&
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

  return *this;
}


apeiron::opengl::Shape::Shape(Shape&& other)
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
