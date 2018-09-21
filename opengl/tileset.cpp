#include "tileset.h"


#include <cstdint>
#include <tuple>
#include <vector>
#include "GL/glew.h"
#include <glm/glm.hpp>
#include "engine/vertex.h"


namespace {


auto build_vertices(std::uint32_t columns, std::uint32_t rows, std::uint32_t tile_count,
    float tile_height, float tile_width)
{
  std::vector<apeiron::engine::Vertex_texcoords> vertices;
  const float w = 1.0f / columns;
  const float h = 1.0f / rows;
  const float x = tile_width / 2.0f;
  const float y = tile_height / 2.0f;

  for (std::size_t i=0; i<tile_count; ++i) {
    const float s = (i % columns) * w;
    const float t = 1.0f - h - (i / columns) * h;
    // Texture coordinates are horizontally flipped
    // to revert the flip done when loading the image
    vertices.push_back({ x,  y, 0.0f, s+w, t});
    vertices.push_back({ x, -y, 0.0f, s+w, t+h});
    vertices.push_back({-x,  y, 0.0f, s,   t});
    vertices.push_back({-x, -y, 0.0f, s,   t+h});
    vertices.push_back({-x,  y, 0.0f, s,   t});
    vertices.push_back({ x, -y, 0.0f, s+w, t+h});
  }

  return vertices;
}


}  // namespace


apeiron::opengl::Tileset::Tileset(std::uint32_t columns, std::uint32_t rows,
    std::uint32_t tile_offset, float tile_width, float tile_height)
    : tile_offset_{tile_offset}, tile_count_{columns * rows},
      tile_width_{tile_width}, tile_height_{tile_height}
{
  glGenVertexArrays(1, &vao_);
  glGenBuffers(1, &vbo_);
  glBindVertexArray(vao_);

  const auto vertices = build_vertices(columns, rows, tile_count_,
      tile_height_, tile_width_);
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


void apeiron::opengl::Tileset::load(std::string_view filename)
{
  texture_.load(filename);
}


void apeiron::opengl::Tileset::bind() const
{
  texture_.bind();
}


void apeiron::opengl::Tileset::render(std::uint32_t i) const
{
  const auto index = std::min(i - tile_offset_, tile_count_ - 1);
  glBindVertexArray(vao_);
  glDrawArrays(GL_TRIANGLES, index * vertices_per_tile_, vertices_per_tile_);
}
