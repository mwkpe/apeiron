#include "charset.h"

#include <iostream>
#include <cstdint>
#include <tuple>
#include <vector>
#include "GL/glew.h"
#include <glm/glm.hpp>


namespace {


struct Vertex
{
  float x;
  float y;
  float z;
  float s;
  float t;
};


std::vector<Vertex> build_vertices(std::uint32_t columns, std::uint32_t rows,
    std::uint32_t character_count, float character_height_, float character_width_)
{
  std::vector<Vertex> vertices;
  const float w = 1.0f / columns;
  const float h = 1.0f / rows;
  const float x = character_width_ / 2.0f;
  const float y = character_height_ / 2.0f;

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


apeiron::opengl::Charset::Charset(std::uint32_t columns, std::uint32_t rows, std::uint8_t offset)
    : character_offset_{offset}, character_count_{columns * rows}
{
  character_width_ = 0.5f;
  character_height_ = 1.0f;
  glGenVertexArrays(1, &vao_);
  glGenBuffers(1, &vbo_);
  glBindVertexArray(vao_);
  const auto vertices = build_vertices(columns, rows, character_count_, character_height_, character_width_);
  vertex_count_ = static_cast<std::uint32_t>(vertices.size());
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
  const int stride = sizeof(Vertex);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(0));
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(offsetof(Vertex, s)));
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
