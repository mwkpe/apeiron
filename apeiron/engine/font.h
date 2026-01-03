#ifndef APEIRON_ENGINE_FONT_H
#define APEIRON_ENGINE_FONT_H


#include <cstdint>
#include <string_view>
#include <glm/glm.hpp>
#include "apeiron/engine/vertex.h"


namespace apeiron::engine {


template<typename T = Vertex> struct Glyph
{
  std::vector<T> vertices;
  std::uint32_t index = 0;
  glm::vec3 size;
};


template<typename T = Vertex> struct Font
{
  std::vector<Glyph<T>> glyphs;
};


template<typename T = Vertex> Font<T> load_font(std::string_view filename,
    const glm::vec3& glyph_size);


}  // namespace apeiron::engine


#endif  // APEIRON_ENGINE_FONT_H
