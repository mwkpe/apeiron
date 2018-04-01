#include "cube.h"


#include "GL/glew.h"


namespace {


float cube_vertices[] = {
  -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
   0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
   0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
   0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
  -0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
  -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

  -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
   0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
   0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
   0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
  -0.5f,  0.5f,  0.5f, 0.0f, 1.0f,
  -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,

  -0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
  -0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
  -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
  -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
  -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
  -0.5f,  0.5f,  0.5f, 1.0f, 0.0f,

   0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
   0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
   0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
   0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
   0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
   0.5f,  0.5f,  0.5f, 1.0f, 0.0f,

  -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
   0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
   0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
   0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
  -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
  -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

  -0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
   0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
   0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
   0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
  -0.5f,  0.5f,  0.5f, 0.0f, 0.0f,
  -0.5f,  0.5f, -0.5f, 0.0f, 1.0f
};


}  // namespace


apeiron::opengl::Cube::Cube()
{
  const int elements_per_vertex = 5;
  vertex_count_ = sizeof(cube_vertices) / elements_per_vertex;
  glGenVertexArrays(1, &vao_);
  glGenBuffers(1, &vbo_);
  glBindVertexArray(vao_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);
  const int stride = elements_per_vertex * sizeof(float);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(0));
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(3 * sizeof(float)));
  glEnableVertexAttribArray(2);
}


void apeiron::opengl::Cube::render() const
{
  glBindVertexArray(vao_);
  glDrawArrays(GL_TRIANGLES, 0, vertex_count_);
}
