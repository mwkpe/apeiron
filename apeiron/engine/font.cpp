#include "font.h"


#include <type_traits>
#include "apeiron/engine/model_loader.h"


template<typename T> auto apeiron::engine::load_font(std::string_view filename,
    const glm::vec3& glyph_size) -> Font<T>
{
  Font<T> font;
  auto model = engine::load_model<T>(filename);

  // Empty glyph for space character (model contains placeholder)
  font.glyphs.emplace_back(std::vector<T>{}, 0, glyph_size);

  // Skip over placeholder for space character
  for (std::size_t i=1; i<model.meshes.size(); ++i) {
    font.glyphs.emplace_back(model.meshes[i].vertices, i, glyph_size);
  }

  return font;
}


namespace apeiron::engine {


template auto load_font(std::string_view filename, const glm::vec3& glyph_size) -> Font<Vertex>;
template auto load_font(std::string_view filename, const glm::vec3& glyph_size) -> Font<Vertex_simple>;
template auto load_font(std::string_view filename, const glm::vec3& glyph_size) -> Font<Vertex_normal>;
template auto load_font(std::string_view filename, const glm::vec3& glyph_size) -> Font<Vertex_color>;
template auto load_font(std::string_view filename, const glm::vec3& glyph_size) -> Font<Vertex_texcoords>;
template auto load_font(std::string_view filename, const glm::vec3& glyph_size) -> Font<Vertex_normal_color>;
template auto load_font(std::string_view filename, const glm::vec3& glyph_size) -> Font<Vertex_normal_texcoords>;


}  // namespace apeiron::engine
