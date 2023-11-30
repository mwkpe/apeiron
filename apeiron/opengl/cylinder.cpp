#include "cylinder.h"


#include <vector>
#include <cmath>
#include <glad/glad.h>


namespace {


constexpr float pi = 3.14159f;
constexpr float tau = 2.0f * pi;


std::vector<float> build_vertices(std::uint32_t points, float radius, float height)
{
  const std::uint32_t wall_vertices = (points + 1) * 2 * 3;
  const std::uint32_t circle_vertices = wall_vertices / 2;
  std::vector<float> cylinder(wall_vertices + circle_vertices * 2);
  std::uint32_t wall_index = 0;
  std::uint32_t bottom_circle_index = wall_vertices;
  std::uint32_t top_circle_index = wall_vertices + circle_vertices;

  for (std::uint32_t i=0; i<=points; ++i) {
    const float angle = static_cast<float>(i) / static_cast<float>(points) * tau;
    const float x = radius * std::cos(angle);
    const float z = radius * std::sin(angle);
    cylinder[wall_index++] = x;
    cylinder[wall_index++] = -height / 2.0f;
    cylinder[wall_index++] = z;
    cylinder[wall_index++] = x;
    cylinder[wall_index++] = height / 2.0f;
    cylinder[wall_index++] = z;
    cylinder[bottom_circle_index++] = x;
    cylinder[bottom_circle_index++] = -height / 2.0f;
    cylinder[bottom_circle_index++] = z;
    cylinder[top_circle_index++] = radius * std::cos(tau - angle);
    cylinder[top_circle_index++] = height / 2.0f;
    cylinder[top_circle_index++] = radius * std::sin(tau - angle);
  }

  return cylinder;
}


}  // namespace


apeiron::opengl::Cylinder::Cylinder(std::uint32_t points, float radius, float height)
{
  init(points, radius, height);
}


void apeiron::opengl::Cylinder::init(std::uint32_t points, float radius, float height)
{
  points_ = points;
  glGenVertexArrays(1, &vao_);
  glGenBuffers(1, &vbo_);
  construct(points_, radius, height);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(0));
  glEnableVertexAttribArray(0);
}


void apeiron::opengl::Cylinder::construct(std::uint32_t points, float radius, float height)
{
  points_ = points;
  const auto vertices = build_vertices(points_, radius, height);
  vertex_count_ = static_cast<std::uint32_t>(vertices.size()) / 3;
  glBindVertexArray(vao_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(vertices.size() * sizeof(float)),
      vertices.data(), GL_STATIC_DRAW);
}


void apeiron::opengl::Cylinder::render() const
{
  glBindVertexArray(vao_);
  const GLsizei wall_vertices = static_cast<GLsizei>(vertex_count_) / 2;
  const GLsizei circle_vertices = wall_vertices / 2;
  glDrawArrays(GL_TRIANGLE_STRIP, 0, wall_vertices);  // Walls
  glDrawArrays(GL_TRIANGLE_FAN, wall_vertices, circle_vertices);  // Bottom circle
  glDrawArrays(GL_TRIANGLE_FAN, wall_vertices + circle_vertices, circle_vertices);  // Top circle
}
