#include "cuboid.h"


#include <tuple>
#include <vector>
#include "GL/glew.h"


namespace {


std::tuple<std::vector<float>, int> build_vertices(const glm::vec3& size)
{
  float x = size.x / 2.0f;
  float y = size.y / 2.0f;
  float z = size.z / 2.0f;

  return {
    {
      // x, y, z, nx, ny, nz, s, t
      -x, -y, -z,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
       x, -y, -z,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f,
       x,  y, -z,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
       x,  y, -z,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
      -x,  y, -z,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f,
      -x, -y, -z,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
      -x, -y,  z,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f,
       x, -y,  z,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f,
       x,  y,  z,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f,
       x,  y,  z,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f,
      -x,  y,  z,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f,
      -x, -y,  z,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f,
      -x,  y,  z, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
      -x,  y, -z, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
      -x, -y, -z, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
      -x, -y, -z, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
      -x, -y,  z, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
      -x,  y,  z, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
       x,  y,  z,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
       x,  y, -z,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
       x, -y, -z,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
       x, -y, -z,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
       x, -y,  z,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
       x,  y,  z,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
      -x, -y, -z,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,
       x, -y, -z,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,
       x, -y,  z,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
       x, -y,  z,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
      -x, -y,  z,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
      -x, -y, -z,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,
      -x,  y, -z,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,
       x,  y, -z,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f,
       x,  y,  z,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
       x,  y,  z,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
      -x,  y,  z,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
      -x,  y, -z,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f
    },
    8  // Values per vertex
  };
}


std::tuple<std::vector<float>, std::vector<std::uint16_t>> build_wireframe_vertices(const glm::vec3& size)
{
  float x = size.x / 2.0f;
  float y = size.y / 2.0f;
  float z = size.z / 2.0f;

  return {
    // Vertices
    {
      // Front
      -x, -y, z,
       x, -y, z,
       x,  y, z,
      -x,  y, z,
      // Back
      -x, -y, -z,
       x, -y, -z,
       x,  y, -z,
      -x,  y, -z
    },
    // Elements
    {
      // Front
      0, 1, 1, 2, 2, 3, 3, 0,
      // Back
      4, 5, 5, 6, 6, 7, 7, 4,
      // Connections
      0, 4, 1, 5, 2, 6, 3, 7
    }
  };
}


}  // namespace


apeiron::opengl::Cuboid::Cuboid(const glm::vec3& size, bool wireframe, float line_width)
    : wireframe_{wireframe}, line_width_{line_width}
{
  glGenVertexArrays(1, &vao_);
  glGenBuffers(1, &vbo_);
  glBindVertexArray(vao_);

  if (wireframe) {
    glGenBuffers(1, &ebo_);
    const auto [vertices, elements] = build_wireframe_vertices(size);
    element_count_ = elements.size();
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size() * sizeof(std::uint16_t), elements.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);
  }
  else {
    const auto [vertices, values_per_vertex] = build_vertices(size);
    vertex_count_ = vertices.size() / values_per_vertex;
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    const int stride = values_per_vertex * sizeof(float);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
  }
}


void apeiron::opengl::Cuboid::render() const
{
  glBindVertexArray(vao_);
  if (wireframe_) {
    float global_width;
    glGetFloatv(GL_LINE_WIDTH, &global_width);
    glLineWidth(line_width_);
    glDrawElements(GL_LINES, element_count_, GL_UNSIGNED_SHORT, nullptr);
    glLineWidth(global_width);
  }
  else {
    glDrawArrays(GL_TRIANGLES, 0, vertex_count_);
  }
}
