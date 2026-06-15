#include "font.h"


#include <format>
#include <filesystem>
#include <fstream>
#include <tuple>
#include <type_traits>
#include <nlohmann/json.hpp>
#include "apeiron/engine/error.h"
#include "apeiron/engine/model_loader.h"


template<typename T> auto apeiron::engine::load_font(std::string_view filepath) -> Font<T>
{
  std::filesystem::path json_path = filepath;
  std::ifstream ifs{json_path, std::ios::binary};

  if (!ifs) {
    throw engine::Error{std::format("Could not open file: {}", filepath)};
  }

  Font<T> font;

  try {
    auto font_data = nlohmann::json::parse(ifs);
    auto glyph_data = font_data.at("glyphs");

    auto model_path = json_path.parent_path() / font_data.at("model").get<std::string>();
    auto model = engine::load_model<T>(model_path.string());

    font.name = font_data.at("name").get<std::string>();
    font.line_height = font_data.at("line_height").get<float>();
    font.ascender = font_data.at("ascender").get<float>();
    font.descender = font_data.at("descender").get<float>();

    const auto query_metrics = [&glyph_data](std::string_view codepoint)
        -> std::tuple<std::uint32_t, float> {
      const auto& d = glyph_data.at(codepoint);
      return {d.at("codepoint").get<std::uint32_t>(), d.at("advance").get<float>()};
    };

    // Empty glyph for space character
    {
      auto [codepoint, advance] = query_metrics("U+0020");
      font.glyphs.emplace_back(std::vector<T>{}, 0, codepoint, advance);
    }

    for (std::size_t i=0; i<model.meshes.size(); ++i) {
      auto [codepoint, advance] = query_metrics(model.meshes[i].name);
      font.glyphs.emplace_back(model.meshes[i].vertices, i+1, codepoint, advance);
    }
  }
  catch (const nlohmann::json::parse_error& e) {
    throw engine::Error{std::format("Error loading {}: {}", filepath, e.what())};
  }

  return font;
}


namespace apeiron::engine {


template auto load_font(std::string_view filename) -> Font<Vertex>;
template auto load_font(std::string_view filename) -> Font<Vertex_simple>;
template auto load_font(std::string_view filename) -> Font<Vertex_normal>;
template auto load_font(std::string_view filename) -> Font<Vertex_color>;
template auto load_font(std::string_view filename) -> Font<Vertex_normal_color>;


}  // namespace apeiron::engine
