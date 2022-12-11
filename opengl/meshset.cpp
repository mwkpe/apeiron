#include "meshset.h"


#include <algorithm>
#include <cstdint>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "engine/error.h"
#include "engine/image_loader.h"
#include "engine/vertex.h"


namespace {


struct Pixel
{
  auto operator<=>(const Pixel&) const = default;
  std::uint8_t r;
  std::uint8_t g;
  std::uint8_t b;
  std::uint8_t a;
};


void add_quad(auto& vertices, Pixel pixel, float x, float y, float w, float h)
{
  const auto r = static_cast<float>(pixel.r) / 255.0f;
  const auto g = static_cast<float>(pixel.g) / 255.0f;
  const auto b = static_cast<float>(pixel.b) / 255.0f;
  const auto a = static_cast<float>(pixel.a) / 255.0f;

  const float z = 0.0f;

  // First triangle
  vertices.push_back({{x,   y,   z}, {r, g, b, a}});
  vertices.push_back({{x,   y-h, z}, {r, g, b, a}});
  vertices.push_back({{x+w, y-h, z}, {r, g, b, a}});
  // Second triangle
  vertices.push_back({{x+w, y-h, z}, {r, g, b, a}});
  vertices.push_back({{x+w, y,   z}, {r, g, b, a}});
  vertices.push_back({{x,   y,   z}, {r, g, b, a}});
}


}  // namespace


void apeiron::opengl::Meshset::load_from_image(std::string_view filename, std::uint32_t rows,
    std::uint32_t cols, std::uint32_t index_offset, float tile_width, float tile_height,
    bool optimize)
{
  tile_count_ = cols * rows;
  index_offset_ = index_offset;
  tile_width_ = tile_width;
  tile_height_ = tile_height;

  auto&& [bytes, image_w, image_h, channel_count] = engine::load_image(filename, false);

  if (channel_count != 4)
    throw engine::Error{"Image must be RGBA: ", filename};

  const std::uint32_t tile_w = image_w / cols;
  const std::uint32_t tile_h = image_h / rows;
  const float ps = tile_width_ / tile_w;  // Pixel size normalized

  std::vector<apeiron::engine::Vertex_color> vertices;

  auto read_tile = [&,this](std::uint32_t pos, std::uint32_t skip) -> std::uint32_t {
    float x = -0.5f * tile_width_;
    float y = 0.5f * tile_height_;
    std::size_t vertex_count = 0;

    for (std::uint32_t i=0; i<tile_h; i++) {
      // Read first pixel
      Pixel last_pixel{bytes[pos], bytes[pos + 1], bytes[pos + 2], bytes[pos + 3]};
      pos += channel_count;
      std::uint32_t run_length = 1;

      for (std::uint32_t j=1; j<tile_w; j++) {
        // Read pixel
        Pixel current_pixel{bytes[pos], bytes[pos + 1], bytes[pos + 2], bytes[pos + 3]};
        pos += channel_count;

        // Combine pixels with identical color
        if (optimize && current_pixel == last_pixel) {
          run_length++;
        }
        else {
          if (last_pixel.a > 0) {
            add_quad(vertices, last_pixel, x, y, run_length * ps, ps);
            vertex_count += 6;
          }

          x += run_length * ps;
          last_pixel = current_pixel;
          run_length = 1;
        }
      }

      if (last_pixel.a > 0) {
        add_quad(vertices, last_pixel, x, y, run_length * ps, ps);
        vertex_count += 6;
      }

      x = -0.5f * tile_width_;
      y -= ps;
      pos += skip - tile_w * channel_count;
    }

    return vertex_count;
  };

  for (std::uint32_t i=0; i<rows * cols; i++) {
    auto count = read_tile(((i % cols) * tile_w * channel_count) +
        ((i / cols) * tile_h * image_w * channel_count), image_w * channel_count);
    
    if (i == 0)
      tile_indices_.push_back(0);
    else
      tile_indices_.push_back(tile_indices_.back() + vertex_counts_.back());

    vertex_counts_.push_back(count);
  }

  set_buffers(vertices);
}


template<typename T> void apeiron::opengl::Meshset::set_data(const std::vector<T>& vertices,
    std::vector<std::uint32_t>&& tile_indices, std::vector<std::uint32_t>&& vertex_counts)
{
  set_buffers(vertices);
  tile_indices_ = std::move(tile_indices);
  vertex_counts_ = std::move(vertex_counts);
  tile_count_ = tile_indices_.size();
}


template<typename T> void apeiron::opengl::Meshset::set_data(const std::vector<T>& vertices,
    const std::vector<std::uint32_t>& tile_indices, const std::vector<std::uint32_t>& vertex_counts)
{
  set_buffers(vertices);
  tile_indices_ = tile_indices;
  vertex_counts_ = vertex_counts;
  tile_count_ = tile_indices_.size();
}


void apeiron::opengl::Meshset::set_tile_spacing(const Spacing_vector& tile_spacing)
{
  tile_spacing_ = tile_spacing;
}


void apeiron::opengl::Meshset::set_tile_spacing(Spacing_vector&& tile_spacing)
{
  tile_spacing_ = std::move(tile_spacing);
}


std::tuple<float, float> apeiron::opengl::Meshset::tile_spacing(std::uint32_t i) const
{
  if (const std::uint32_t index = i - index_offset_; index < tile_spacing_.size())
    return tile_spacing_[index];

  return {tile_width_, tile_height_};
}


void apeiron::opengl::Meshset::render(std::uint32_t i) const
{
  const auto tile_index = std::min(i - index_offset_, tile_count_ - 1);
  glBindVertexArray(vao_);
  glDrawArrays(GL_TRIANGLES, tile_indices_[tile_index], vertex_counts_[tile_index]);
}


template void apeiron::opengl::Meshset::set_data(const std::vector<apeiron::engine::Vertex>&, 
    std::vector<std::uint32_t>&&,
    std::vector<std::uint32_t>&&);
template void apeiron::opengl::Meshset::set_data(const std::vector<apeiron::engine::Vertex>&, 
    const std::vector<std::uint32_t>&,
    const std::vector<std::uint32_t>&);

template void apeiron::opengl::Meshset::set_data(const std::vector<apeiron::engine::Vertex_color>&, 
    std::vector<std::uint32_t>&&,
    std::vector<std::uint32_t>&&);
template void apeiron::opengl::Meshset::set_data(const std::vector<apeiron::engine::Vertex_color>&, 
    const std::vector<std::uint32_t>&,
    const std::vector<std::uint32_t>&);
