#include "cylinder.h"


#include <vector>
#include <cmath>
#include <glad/glad.h>


namespace {


std::vector<apeiron::engine::Vertex_simple> build_vertices(std::uint32_t points, float radius,
    float height, apeiron::engine::Axis axis)
{
  constexpr float pi = 3.14159f;
  constexpr float tau = 2.0f * pi;

  std::vector<apeiron::engine::Vertex_simple> vertices;
  vertices.reserve((points + 1) * 4);

  const float r = radius;
  const float h = height / 2.0f;

  for (std::uint32_t i=0; i<=points; ++i) {
    const float a = static_cast<float>(i) / static_cast<float>(points) * tau;
    const float ca = r * std::cos(a);
    const float sa = r * std::sin(a);

    switch (axis) {
      case apeiron::engine::Axis::X:
        vertices.emplace_back(h, ca, sa);
        vertices.emplace_back(-h, ca, sa);
      break;
      case apeiron::engine::Axis::Y:
        vertices.emplace_back(ca, -h, sa);
        vertices.emplace_back(ca, h, sa);
      break;
      case apeiron::engine::Axis::Z:
        vertices.emplace_back(ca, sa, h);
        vertices.emplace_back(ca, sa, -h);
      break;
    }
  }

  for (std::uint32_t i=0; i<=points; ++i) {
    const float a = static_cast<float>(i) / static_cast<float>(points) * tau;
    const float ca = r * std::cos(a);
    const float sa = r * std::sin(a);

    switch (axis) {
      case apeiron::engine::Axis::X:
        vertices.emplace_back(h, ca, sa);
      break;
      case apeiron::engine::Axis::Y:
        vertices.emplace_back(ca, -h, sa);
      break;
      case apeiron::engine::Axis::Z:
        vertices.emplace_back(ca, sa, h);
      break;
    }
  }

  for (std::uint32_t i=0; i<=points; ++i) {
    const float a = tau - static_cast<float>(i) / static_cast<float>(points) * tau;
    const float ca = r * std::cos(a);
    const float sa = r * std::sin(a);

    switch (axis) {
      case apeiron::engine::Axis::X:
        vertices.emplace_back(-h, ca, sa);
      break;
      case apeiron::engine::Axis::Y:
        vertices.emplace_back(ca, h, sa);
      break;
      case apeiron::engine::Axis::Z:
        vertices.emplace_back(ca, sa, -h);
      break;
    }
  }

  return vertices;
}


std::vector<apeiron::engine::Vertex_color> build_vertices(std::uint32_t points, float radius,
    float height, apeiron::engine::Axis axis, const glm::vec4& color)
{
  constexpr float pi = 3.14159f;
  constexpr float tau = 2.0f * pi;

  std::vector<apeiron::engine::Vertex_color> vertices;
  vertices.reserve((points + 1) * 4);

  const float r = radius;
  const float h = height / 2.0f;

  for (std::uint32_t i=0; i<=points; ++i) {
    const float a = static_cast<float>(i) / static_cast<float>(points) * tau;
    const float ca = r * std::cos(a);
    const float sa = r * std::sin(a);

    switch (axis) {
    case apeiron::engine::Axis::X:
        vertices.emplace_back(glm::vec3{h, ca, sa}, color);
        vertices.emplace_back(glm::vec3{-h, ca, sa}, color);
      break;
      case apeiron::engine::Axis::Y:
        vertices.emplace_back(glm::vec3{ca, -h, sa}, color);
        vertices.emplace_back(glm::vec3{ca, h, sa}, color);
      break;
      case apeiron::engine::Axis::Z:
        vertices.emplace_back(glm::vec3{ca, sa, h}, color);
        vertices.emplace_back(glm::vec3{ca, sa, -h}, color);
      break;
    }
  }

  for (std::uint32_t i=0; i<=points; ++i) {
    const float a = static_cast<float>(i) / static_cast<float>(points) * tau;
    const float ca = r * std::cos(a);
    const float sa = r * std::sin(a);

    switch (axis) {
      case apeiron::engine::Axis::X:
        vertices.emplace_back(glm::vec3{h, ca, sa}, color);
      break;
      case apeiron::engine::Axis::Y:
        vertices.emplace_back(glm::vec3{ca, -h, sa}, color);
      break;
      case apeiron::engine::Axis::Z:
        vertices.emplace_back(glm::vec3{ca, sa, h}, color);
      break;
    }
  }

  for (std::uint32_t i=0; i<=points; ++i) {
    const float a = tau - static_cast<float>(i) / static_cast<float>(points) * tau;
    const float ca = r * std::cos(a);
    const float sa = r * std::sin(a);

    switch (axis) {
      case apeiron::engine::Axis::X:
        vertices.emplace_back(glm::vec3{-h, ca, sa}, color);
      break;
      case apeiron::engine::Axis::Y:
        vertices.emplace_back(glm::vec3{ca, h, sa}, color);
      break;
      case apeiron::engine::Axis::Z:
        vertices.emplace_back(glm::vec3{ca, sa, -h}, color);
      break;
    }
  }

  return vertices;
}


}  // namespace


void apeiron::opengl::Cylinder::init(std::uint32_t points, float radius,
    float height, engine::Axis axis)
{
  const auto vertices = build_vertices(points, radius, height, axis);
  set_buffers(vertices);
}


void apeiron::opengl::Cylinder::init(std::uint32_t points, float radius, float height,
    engine::Axis axis, const glm::vec4& color)
{
  const auto vertices = build_vertices(points, radius, height, axis, color);
  set_buffers(vertices);
}


void apeiron::opengl::Cylinder::render() const
{
  glBindVertexArray(vao_);
  const GLsizei wall_vertices = static_cast<GLsizei>(vertex_count_) / 2;
  const GLsizei disk_vertices = wall_vertices / 2;
  glDrawArrays(GL_TRIANGLE_STRIP, 0, wall_vertices);
  glDrawArrays(GL_TRIANGLE_FAN, wall_vertices, disk_vertices);
  glDrawArrays(GL_TRIANGLE_FAN, wall_vertices + disk_vertices, disk_vertices);
}
