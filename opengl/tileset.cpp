#include "tileset.h"


#include <cstdint>
#include <tuple>
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "engine/vertex.h"


namespace {


auto build_vertices(std::uint32_t columns, std::uint32_t rows, std::uint32_t tile_count,
    float tile_height, float tile_width, bool flip_y)
{
  std::vector<apeiron::engine::Vertex_texcoords> vertices;
  const float w = 1.0f / columns;
  const float h = 1.0f / rows;
  const float x = tile_width / 2.0f;
  const float y = tile_height / 2.0f;

  for (std::size_t i=0; i<tile_count; ++i) {
    const float s = (i % columns) * w;
    const float t = 1.0f - h - (i / columns) * h;
    if (flip_y) {  // E.g. when using top left origin
      vertices.push_back({{ x,  y, 0.0f}, {s+w, t}});
      vertices.push_back({{ x, -y, 0.0f}, {s+w, t+h}});
      vertices.push_back({{-x,  y, 0.0f}, {s,   t}});
      vertices.push_back({{-x, -y, 0.0f}, {s,   t+h}});
      vertices.push_back({{-x,  y, 0.0f}, {s,   t}});
      vertices.push_back({{ x, -y, 0.0f}, {s+w, t+h}});
    }
    else {
      vertices.push_back({{-x, -y, 0.0f}, {s,   t}});
      vertices.push_back({{ x, -y, 0.0f}, {s+w, t}});
      vertices.push_back({{-x,  y, 0.0f}, {s,   t+h}});
      vertices.push_back({{ x, -y, 0.0f}, {s+w, t}});
      vertices.push_back({{ x,  y, 0.0f}, {s+w, t+h}});
      vertices.push_back({{-x,  y, 0.0f}, {s,   t+h}});
    }
  }

  return vertices;
}


}  // namespace


apeiron::opengl::Tileset::Tileset(std::uint32_t columns, std::uint32_t rows,
    std::uint32_t tile_offset, float tile_width, float tile_height, bool flip_y)
    : tile_offset_{tile_offset}, tile_count_{columns * rows},
      tile_width_{tile_width}, tile_height_{tile_height}
{
  set_buffers(build_vertices(columns, rows, tile_count_, tile_height_, tile_width_, flip_y));
}


void apeiron::opengl::Tileset::load_texture(std::string_view filename, Pixel_format pixel_format)
{
  texture_.load(filename, pixel_format);
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
