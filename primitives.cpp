#include "primitives.h"


#include <vector>
#include <cmath>
#include "GL/glew.h"


namespace {


constexpr float pi = 3.14159f;
constexpr float tau = 2 * pi;


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


std::vector<float> build_cylinder_vertices(int points, float radius = 0.5f, float height = 1.0f)
{
  std::vector<float> cylinder((points + 1) * 2 * 3);
  int offset = 0;

  for (int i=0; i<=points; ++i) {
    float angle = static_cast<float>(i) / points * tau;
    float x = radius * std::cos(-angle);
    float y = radius * std::sin(-angle);
    cylinder[offset++] = x;
    cylinder[offset++] = y;
    cylinder[offset++] = -height/2.0f;
    cylinder[offset++] = x;
    cylinder[offset++] = y;
    cylinder[offset++] = height/2.0f;
  }

  return cylinder;
}


}  // namespace


apeiron::primitives::Cube::Cube() : vertex_count_{sizeof(cube_vertices) / 3}
{
  glGenVertexArrays(1, &vao_);
  glGenBuffers(1, &vbo_);
  glBindVertexArray(vao_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, static_cast<void*>(0));
  glEnableVertexAttribArray(0);
}


void apeiron::primitives::Cube::render() const
{
  glBindVertexArray(vao_);
  glDrawArrays(GL_TRIANGLES, 0, vertex_count_);
}


apeiron::primitives::Cylinder::Cylinder(int points) : vertex_count_{(points + 1) * 2}
{
  auto vertices = build_cylinder_vertices(points);
  glGenVertexArrays(1, &vao_);
  glGenBuffers(1, &vbo_);
  glBindVertexArray(vao_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, static_cast<void*>(0));
  glEnableVertexAttribArray(0);
}


void apeiron::primitives::Cylinder::render() const
{
  glBindVertexArray(vao_);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, vertex_count_);
}
