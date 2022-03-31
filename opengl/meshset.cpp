#include "meshset.h"


#include <algorithm>
#include <cstdint>
#include <tuple>
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "engine/error.h"
#include "engine/image_loader.h"
#include "engine/vertex.h"


namespace {


}  // namespace


void apeiron::opengl::Meshset::load_from_image(std::string_view filename, std::uint32_t rows,
    std::uint32_t cols, std::uint32_t tile_offset)
{
  tile_count_ = cols * rows;
  tile_offset_ = tile_offset;

  auto&& [pixel, image_w, image_h, channel_count] = engine::load_image(filename, false);

  if (channel_count != 4)
    throw engine::Error{"Image must be RGBA: ", filename};

  const std::uint32_t tile_w = image_w / cols;
  const std::uint32_t tile_h = image_h / rows;
  const float ps = tile_width_ / tile_w;  // Pixel size normalized

  std::vector<apeiron::engine::Vertex_color> vertices;

  auto read_tile = [&,this](std::uint32_t pos, std::uint32_t skip) -> std::uint32_t {
    float x = -0.5f;
    float y = 0.5f;
    const float z = 0.0f;
    std::size_t vertex_count = 0;

    for (std::uint32_t i=0; i<tile_h; i++) {
      for (std::uint32_t j=0; j<tile_w; j++) {
        // Read pixel
        const float r = pixel[pos] / 255.0f;
        const float g = pixel[pos + 1] / 255.0f;
        const float b = pixel[pos + 2] / 255.0f;
        const std::uint8_t alpha = pixel[pos + 3];
        const float a = alpha / 255.0f;
        pos += channel_count;

        // Pixel to quad
        if (alpha > 0) {
          // First triangle
          vertices.push_back({{x,    y,    z}, {r, g, b, a}});
          vertices.push_back({{x,    y-ps, z}, {r, g, b, a}});
          vertices.push_back({{x+ps, y-ps, z}, {r, g, b, a}});
          // Second triangle
          vertices.push_back({{x+ps, y-ps, z}, {r, g, b, a}});
          vertices.push_back({{x+ps, y,    z}, {r, g, b, a}});
          vertices.push_back({{x,    y,    z}, {r, g, b, a}});

          vertex_count += 6;
        }

        x += ps;
      }

      x = -0.5f;
      y -= ps;
      pos += skip - tile_w * channel_count;
    }

    return vertex_count;
  };

  for (std::uint32_t i=0; i<rows * cols; i++) {
    auto count = read_tile(((i % cols) * tile_w * channel_count) +
        ((i / cols) * tile_h * image_w * channel_count), image_w * channel_count);
    
    if (i == 0)
      index_.push_back(0);
    else
      index_.push_back(index_.back() + vertex_count_.back());

    vertex_count_.push_back(count);
  }

  set_buffers(vertices);
}


void apeiron::opengl::Meshset::render(std::uint32_t i) const
{
  const auto index = std::min(i - tile_offset_, tile_count_ - 1);
  glBindVertexArray(vao_);
  glDrawArrays(GL_TRIANGLES, index_[index], vertex_count_[index]);
}
