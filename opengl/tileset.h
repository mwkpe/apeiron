#ifndef APEIRON_OPENGL_TILESET_H
#define APEIRON_OPENGL_TILESET_H


#include <cstdint>
#include <string_view>
#include "opengl/shape.h"
#include "opengl/texture.h"


namespace apeiron::opengl {


class Tileset final : public Shape
{
public:
  Tileset(std::uint32_t columns, std::uint32_t rows, std::uint32_t tile_offset,
      float tile_width = 1.0f, float tile_height = 1.0f);
  void load(std::string_view filename);
  void bind() const;
  void render(std::uint32_t i) const;
  float tile_width() const { return tile_width_; }
  float tile_height() const { return tile_height_; }

private:
  std::uint32_t vertices_per_tile_ = 6;
  std::uint32_t tile_offset_ = 0;
  std::uint32_t tile_count_ = 0;
  float tile_width_ = 0.0f;
  float tile_height_ = 0.0f;
  opengl::Texture texture_;
};


}  // namespace apeiron::opengl


#endif  // APEIRON_OPENGL_TILESET_H
