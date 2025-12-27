#include "text.h"


#include <ranges>


namespace {


constexpr auto is_printable_ascii = std::views::filter([](const auto& c) { return c > 21 && c < 127; });


void add_glyph(auto& vertices, auto& entries, const auto& glyph, const glm::vec3& pos)
{
  apeiron::opengl::Meshset_entry entry;

  entry.first_vertex = entries.empty() ? 0 :
      entries.back().first_vertex + entries.back().vertex_count;
  entry.vertex_count = glyph.index > 0 ? glyph.vertices.size() : 0;
  entry.size = glyph.size;

  entries.push_back(entry);

  // Ignore space character
  if (glyph.index > 0) {
    for (auto v : glyph.vertices) {
      float offset = static_cast<float>(glyph.index) * glyph.size.x;
      v.position.x += pos.x - offset;
      vertices.push_back(v);
    }
  }
}


void create_text(auto& vertices, auto& entries, auto& font, std::string_view text)
{
  static const std::uint32_t ascii_offset = 32;
  glm::vec3 pos{0.0f};

  for (char c : text | is_printable_ascii) {
    std::uint32_t index = static_cast<std::uint32_t>(c) - ascii_offset;

    if (index < font.glyphs.size()) {
      add_glyph(vertices, entries, font.glyphs[index], pos);
      pos.x += entries.back().size.x;
    }
  }
}


}  // namespace


template<typename T> void apeiron::prefab::Text::init(std::string_view text,
    const engine::Font<T>& font, opengl::Usage_hint hint)
{
  text_ = text;

  std::vector<T> vertices;
  std::vector<apeiron::opengl::Meshset_entry> entries;
  create_text(vertices, entries, font, text);

  meshset_.set_data(vertices, std::move(entries), hint);
}


template<typename T> void apeiron::prefab::Text::update(std::string_view text,
    const engine::Font<T>& font)
{
  text_ = text;

  std::vector<T> vertices;
  std::vector<apeiron::opengl::Meshset_entry> entries;
  create_text(vertices, entries, font, text);

  meshset_.update_data(vertices, std::move(entries));
}


using apeiron::engine::Vertex;
using apeiron::engine::Vertex_simple;
using apeiron::engine::Vertex_normal;
using apeiron::engine::Vertex_color;
using apeiron::engine::Vertex_texcoords;
using apeiron::engine::Vertex_normal_color;
using apeiron::engine::Vertex_normal_texcoords;
using apeiron::opengl::Usage_hint;


namespace apeiron::prefab {


template void Text::init(std::string_view, const engine::Font<Vertex>&, Usage_hint);
template void Text::init(std::string_view, const engine::Font<Vertex_simple>&, Usage_hint);
template void Text::init(std::string_view, const engine::Font<Vertex_normal>&, Usage_hint);
template void Text::init(std::string_view, const engine::Font<Vertex_color>&, Usage_hint);
template void Text::init(std::string_view, const engine::Font<Vertex_texcoords>&, Usage_hint);
template void Text::init(std::string_view, const engine::Font<Vertex_normal_color>&, Usage_hint);
template void Text::init(std::string_view, const engine::Font<Vertex_normal_texcoords>&, Usage_hint);


template void Text::update(std::string_view, const engine::Font<Vertex>&);
template void Text::update(std::string_view, const engine::Font<Vertex_simple>&);
template void Text::update(std::string_view, const engine::Font<Vertex_normal>&);
template void Text::update(std::string_view, const engine::Font<Vertex_color>&);
template void Text::update(std::string_view, const engine::Font<Vertex_texcoords>&);
template void Text::update(std::string_view, const engine::Font<Vertex_normal_color>&);
template void Text::update(std::string_view, const engine::Font<Vertex_normal_texcoords>&);


}  // namespace apeiron::prefab
