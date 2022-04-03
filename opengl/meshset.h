#ifndef APEIRON_OPENGL_MESHSET_H
#define APEIRON_OPENGL_MESHSET_H


#include <cstdint>
#include <string_view>
#include "opengl/shape.h"


namespace apeiron::opengl {


class Meshset final : public Shape
{
public:
  Meshset() = default;
  void load_from_image(std::string_view filename, std::uint32_t rows,
      std::uint32_t cols, std::uint32_t index_offset = 0);
  void render(std::uint32_t i) const;
  void set_tile_width(float tile_width) { tile_width_ = tile_width; }
  void set_tile_height(float tile_height) { tile_height_ = tile_height; }
  float tile_width() const { return tile_width_; }
  float tile_height() const { return tile_height_; }

private:
  std::vector<std::uint32_t> index_;
  std::vector<std::uint32_t> vertex_count_;
  std::uint32_t tile_count_ = 1;
  std::uint32_t index_offset_ = 0;
  float tile_width_ = 1.0f;
  float tile_height_ = 1.0f;
};


}  // namespace apeiron::opengl


#endif  // APEIRON_OPENGL_MESHSET_H
