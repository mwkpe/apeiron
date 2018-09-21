#ifndef APEIRON_OPENGL_CHARSET_H
#define APEIRON_OPENGL_CHARSET_H


#include <cstdint>
#include <string_view>
#include "opengl/shape.h"
#include "opengl/texture.h"


namespace apeiron::opengl {


class Charset final : public Shape
{
public:
  Charset(std::uint32_t columns, std::uint32_t rows, std::uint8_t character_offset,
      float character_width = 0.5f, float character_height = 1.0f);
  void load(std::string_view filename);
  void bind() const;
  void render(char c) const;
  void render(int i) const;
  float character_height() const { return character_height_; }
  float character_width() const { return character_width_; }

private:
  std::uint32_t vertices_per_character_ = 6;
  std::uint32_t character_offset_ = 0;
  std::uint32_t character_count_ = 0;
  float character_width_ = 0;
  float character_height_ = 0;
  opengl::Texture texture_;
};


}  // namespace apeiron::opengl


#endif  // APEIRON_OPENGL_CHARSET_H
