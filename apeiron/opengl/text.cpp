#include "text.h"


#include <ranges>


namespace {


// Excluding DEL (127)
constexpr auto is_printable_ascii = std::views::filter(
    [](const auto& c) { return c > 31 && c < 127; });


void add_glyph(auto& vertices, auto& entries, const auto& glyph, const glm::vec3& pos)
{
  apeiron::opengl::Meshset_entry entry;

  entry.first_vertex = entries.empty() ? 0 :
      entries.back().first_vertex + entries.back().vertex_count;
  entry.vertex_count = glyph.vertices.size();

  entries.push_back(entry);

  for (auto v : glyph.vertices) {
    v.position += pos;
    vertices.push_back(v);
  }
}


void create_text(auto& vertices, auto& entries, auto& font, std::string_view text,
    const glm::vec3& offset = glm::vec3{0.0f}, const glm::vec3& scale = glm::vec3{1.0f})
{
  auto pos = glm::vec3{0.0f} + offset / scale;

  for (char c : text | is_printable_ascii) {
    constexpr std::uint32_t ascii_offset = 32;
    std::uint32_t index = static_cast<std::uint32_t>(c) - ascii_offset;

    if (index < font.glyphs.size()) {
      add_glyph(vertices, entries, font.glyphs[index], pos);
      pos.x += font.glyphs[index].advance;
    }
  }
}


}  // namespace


template<typename T> void apeiron::opengl::Text::init(std::string_view text,
    const engine::Font<T>& font, opengl::Usage_hint hint)
{
  text_ = text;

  std::vector<T> vertices;
  std::vector<Meshset_entry> entries;
  create_text(vertices, entries, font, text);

  meshset_.init(vertices, std::move(entries), hint);
}


template<typename T> void apeiron::opengl::Text::update(std::string_view text,
    const engine::Font<T>& font)
{
  text_ = text;

  std::vector<T> vertices;
  std::vector<Meshset_entry> entries;
  create_text(vertices, entries, font, text);

  meshset_.update(vertices, std::move(entries));
}


template<typename T> void apeiron::opengl::Multi_text::init(std::span<Text_part> text_parts,
    const engine::Font<T>& font, opengl::Usage_hint hint)
{
  std::vector<T> vertices;
  std::vector<Meshset_entry> entries;

  for (const auto& part : text_parts) {
    create_text(vertices, entries, font, part.text, part.offset, transform().scale());
  }

  meshset_.init(vertices, std::move(entries), hint);
}


template<typename T> void apeiron::opengl::Multi_text::update(std::span<Text_part> text_parts,
    const engine::Font<T>& font)
{
  std::vector<T> vertices;
  std::vector<Meshset_entry> entries;

  for (const auto& part : text_parts) {
    create_text(vertices, entries, font, part.text, part.offset, transform().scale());
  }

  meshset_.update(vertices, std::move(entries));
}


using apeiron::engine::Vertex;
using apeiron::engine::Vertex_simple;
using apeiron::engine::Vertex_normal;
using apeiron::engine::Vertex_color;
using apeiron::engine::Vertex_normal_color;
using apeiron::opengl::Usage_hint;


namespace apeiron::opengl {


template void Text::init(std::string_view, const engine::Font<Vertex>&, Usage_hint);
template void Text::init(std::string_view, const engine::Font<Vertex_simple>&, Usage_hint);
template void Text::init(std::string_view, const engine::Font<Vertex_normal>&, Usage_hint);
template void Text::init(std::string_view, const engine::Font<Vertex_color>&, Usage_hint);
template void Text::init(std::string_view, const engine::Font<Vertex_normal_color>&, Usage_hint);

template void Multi_text::init(std::span<Text_part>, const engine::Font<Vertex>&, Usage_hint);
template void Multi_text::init(std::span<Text_part>, const engine::Font<Vertex_simple>&, Usage_hint);
template void Multi_text::init(std::span<Text_part>, const engine::Font<Vertex_normal>&, Usage_hint);
template void Multi_text::init(std::span<Text_part>, const engine::Font<Vertex_color>&, Usage_hint);
template void Multi_text::init(std::span<Text_part>, const engine::Font<Vertex_normal_color>&, Usage_hint);

template void Text::update(std::string_view, const engine::Font<Vertex>&);
template void Text::update(std::string_view, const engine::Font<Vertex_simple>&);
template void Text::update(std::string_view, const engine::Font<Vertex_normal>&);
template void Text::update(std::string_view, const engine::Font<Vertex_color>&);
template void Text::update(std::string_view, const engine::Font<Vertex_normal_color>&);

template void Multi_text::update(std::span<Text_part>, const engine::Font<Vertex>&);
template void Multi_text::update(std::span<Text_part>, const engine::Font<Vertex_simple>&);
template void Multi_text::update(std::span<Text_part>, const engine::Font<Vertex_normal>&);
template void Multi_text::update(std::span<Text_part>, const engine::Font<Vertex_color>&);
template void Multi_text::update(std::span<Text_part>, const engine::Font<Vertex_normal_color>&);


}  // namespace apeiron::opengl
