#include "cylinder.h"


#include <vector>
#include <cmath>
#include "GL/glew.h"


namespace {


constexpr float pi = 3.14159f;
constexpr float tau = 2.0f * pi;


std::vector<float> build_cylinder_vertices(int points, float radius = 0.5f, float height = 1.0f)
{
  int wall_vertices = (points + 1) * 2 * 3;
  int circle_vertices = wall_vertices / 2;
  std::vector<float> cylinder(wall_vertices + circle_vertices * 2);
  int wall_index = 0;
  int bottom_circle_index = wall_vertices;
  int top_circle_index = wall_vertices + circle_vertices;

  for (int i=0; i<=points; ++i) {
    float angle = static_cast<float>(i) / points * tau;
    float x = radius * std::cos(-angle);
    float y = radius * std::sin(-angle);
    cylinder[wall_index++] = x;
    cylinder[wall_index++] = y;
    cylinder[wall_index++] = -height / 2.0f;
    cylinder[wall_index++] = x;
    cylinder[wall_index++] = y;
    cylinder[wall_index++] = height / 2.0f;
    cylinder[bottom_circle_index++] = x;
    cylinder[bottom_circle_index++] = y;
    cylinder[bottom_circle_index++] = -height / 2.0f;
    cylinder[top_circle_index++] = x;
    cylinder[top_circle_index++] = y;
    cylinder[top_circle_index++] = height / 2.0f;
  }

  return cylinder;
}


}  // namespace


apeiron::opengl::Cylinder::Cylinder(int points) : points_{points}
{
  glGenVertexArrays(1, &vao_);
  glGenBuffers(1, &vbo_);
  construct(points_);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, static_cast<void*>(0));
  glEnableVertexAttribArray(0);
}


apeiron::opengl::Cylinder::~Cylinder()
{
  glDeleteBuffers(1, &vbo_);
  glDeleteVertexArrays(1, &vao_);
}


void apeiron::opengl::Cylinder::construct(int points)
{
  points_ = points;
  auto vertices = build_cylinder_vertices(points_);
  vertex_count_ = vertices.size() / 3;
  glBindVertexArray(vao_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
}


void apeiron::opengl::Cylinder::render() const
{
  glBindVertexArray(vao_);
  auto wall_vertices = vertex_count_ / 2;
  auto circle_vertices = wall_vertices / 2;
  glDrawArrays(GL_TRIANGLE_STRIP, 0, wall_vertices);  // Walls
  glDrawArrays(GL_TRIANGLE_FAN, wall_vertices, circle_vertices);  // Bottom circle
  glDrawArrays(GL_TRIANGLE_FAN, wall_vertices + circle_vertices, circle_vertices);  // Top circle
}
