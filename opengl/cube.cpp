#include "cube.h"


#include "GL/glew.h"


namespace {


float cube_vertices[] = {
  -0.5f, -0.5f, -0.5f,
   0.5f, -0.5f, -0.5f,
   0.5f,  0.5f, -0.5f,
   0.5f,  0.5f, -0.5f,
  -0.5f,  0.5f, -0.5f,
  -0.5f, -0.5f, -0.5f,

  -0.5f, -0.5f,  0.5f,
   0.5f, -0.5f,  0.5f,
   0.5f,  0.5f,  0.5f,
   0.5f,  0.5f,  0.5f,
  -0.5f,  0.5f,  0.5f,
  -0.5f, -0.5f,  0.5f,

  -0.5f,  0.5f,  0.5f,
  -0.5f,  0.5f, -0.5f,
  -0.5f, -0.5f, -0.5f,
  -0.5f, -0.5f, -0.5f,
  -0.5f, -0.5f,  0.5f,
  -0.5f,  0.5f,  0.5f,

   0.5f,  0.5f,  0.5f,
   0.5f,  0.5f, -0.5f,
   0.5f, -0.5f, -0.5f,
   0.5f, -0.5f, -0.5f,
   0.5f, -0.5f,  0.5f,
   0.5f,  0.5f,  0.5f,

  -0.5f, -0.5f, -0.5f,
   0.5f, -0.5f, -0.5f,
   0.5f, -0.5f,  0.5f,
   0.5f, -0.5f,  0.5f,
  -0.5f, -0.5f,  0.5f,
  -0.5f, -0.5f, -0.5f,

  -0.5f,  0.5f, -0.5f,
   0.5f,  0.5f, -0.5f,
   0.5f,  0.5f,  0.5f,
   0.5f,  0.5f,  0.5f,
  -0.5f,  0.5f,  0.5f,
  -0.5f,  0.5f, -0.5f
};


}  // namespace


apeiron::opengl::Cube::Cube()
{
  vertex_count_ = sizeof(cube_vertices) / 3;
  glGenVertexArrays(1, &vao_);
  glGenBuffers(1, &vbo_);
  glBindVertexArray(vao_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, static_cast<void*>(0));
  glEnableVertexAttribArray(0);
}


apeiron::opengl::Cube::~Cube()
{
  glDeleteBuffers(1, &vbo_);
  glDeleteVertexArrays(1, &vao_);
}


void apeiron::opengl::Cube::render() const
{
  glBindVertexArray(vao_);
  glDrawArrays(GL_TRIANGLES, 0, vertex_count_);
}
