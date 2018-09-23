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
