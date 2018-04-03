#include "shape.h"


#include "GL/glew.h"


apeiron::opengl::Shape::~Shape()
{
  glDeleteBuffers(1, &vbo_);
  glDeleteBuffers(1, &ebo_);
  glDeleteVertexArrays(1, &vao_);
}
