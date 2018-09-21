#include "charset.h"


#include <cstdint>
#include <tuple>
#include <vector>
#include "GL/glew.h"
#include <glm/glm.hpp>
#include "engine/vertex.h"


namespace {


auto build_vertices(std::uint32_t columns, std::uint32_t rows, std::uint32_t character_count,
    float character_height, float character_width)
{
  std::vector<apeiron::engine::Vertex_texcoords> vertices;
  const float w = 1.0f / columns;
  const float h = 1.0f / rows;
  const float x = character_width / 2.0f;
  const float y = character_height / 2.0f;

  for (std::size_t i=0; i<character_count; ++i) {
    const float s = (i % columns) * w;
    const float t = 1.0f - h - (i / columns) * h;
    vertices.push_back({-x, -y, 0.0f, s,   t});
    vertices.push_back({ x, -y, 0.0f, s+w, t});
    vertices.push_back({ x,  y, 0.0f, s+w, t+h});
    vertices.push_back({ x,  y, 0.0f, s+w, t+h});
    vertices.push_back({-x,  y, 0.0f, s,   t+h});
    vertices.push_back({-x, -y, 0.0f, s,   t});
  }

  return vertices;
}


}  // namespace


apeiron::opengl::Charset::Charset(std::uint32_t columns, std::uint32_t rows,
    std::uint8_t character_offset, float character_width, float character_height)
    : character_offset_{character_offset}, character_count_{columns * rows},
      character_width_{character_width}, character_height_{character_height}
{
  glGenVertexArrays(1, &vao_);
  glGenBuffers(1, &vbo_);
  glBindVertexArray(vao_);

  const auto vertices = build_vertices(columns, rows, character_count_,
      character_height_, character_width_);
  vertex_count_ = vertices.size();
  const int stride = sizeof(engine::Vertex_texcoords);

  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(engine::Vertex_texcoords),
      vertices.data(), GL_STATIC_DRAW);

  // Position
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(0));
  glEnableVertexAttribArray(0);
  // Texture coordinates
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride,
      reinterpret_cast<void*>(offsetof(engine::Vertex_texcoords, texcoords)));
  glEnableVertexAttribArray(2);
}


void apeiron::opengl::Charset::load(std::string_view filename)
{
  texture_.load(filename);
}


void apeiron::opengl::Charset::bind() const
{
  texture_.bind();
}


void apeiron::opengl::Charset::render(char c) const
{
  const auto index = std::min(c - character_offset_, character_count_ - 1);
  glBindVertexArray(vao_);
  glDrawArrays(GL_TRIANGLES, index * vertices_per_character_, vertices_per_character_);
}


void apeiron::opengl::Charset::render(int i) const
{
  const auto index = std::min(i - character_offset_, character_count_ - 1);
  glBindVertexArray(vao_);
  glDrawArrays(GL_TRIANGLES, index * vertices_per_character_, vertices_per_character_);
}
