#ifndef APEIRON_OPENGL_TILESET_H
#define APEIRON_OPENGL_TILESET_H


#include <cstdint>
#include <string_view>
#include "apeiron/opengl/shape.h"
#include "apeiron/opengl/texture.h"


namespace apeiron::opengl {


class Tileset final : public Shape
{
public:
  Tileset(std::uint32_t cols, std::uint32_t rows, std::uint32_t index_offset = 0,
      float tile_width = 1.0f, float tile_height = 1.0f, bool flip_y = false);
  void load_texture(std::string_view filename, Pixel_format pixel_format);
  void bind() const;
  void render(std::uint32_t i) const override;
  [[nodiscard]] float tile_width() const { return tile_width_; }
  [[nodiscard]] float tile_height() const { return tile_height_; }
  Texture& texture() { return texture_; }

private:
  std::uint32_t vertices_per_tile_ = 6;
  std::uint32_t index_offset_ = 0;
  std::uint32_t tile_count_ = 0;
  float tile_width_ = 0.0f;
  float tile_height_ = 0.0f;
  opengl::Texture texture_;
};


}  // namespace apeiron::opengl


#endif  // APEIRON_OPENGL_TILESET_H
