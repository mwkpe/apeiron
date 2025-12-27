#include "font.h"


#include <type_traits>
#include "apeiron/engine/model_loader.h"


template<typename T> auto apeiron::engine::load_font(std::string_view filename,
    const glm::vec3& glyph_size) -> Font<T>
{
  Font<T> font;
  auto model = engine::load_model<T>(filename);
  std::uint32_t index = 0;

  for (const auto& mesh : model.meshes) {
    font.glyphs.emplace_back(mesh.vertices, index++, glyph_size);
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
