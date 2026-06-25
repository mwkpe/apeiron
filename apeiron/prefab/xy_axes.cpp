#include "xy_axes.h"


#include <string>
#include <tuple>
#include <vector>

#include "apeiron/engine/primitive.h"
#include "apeiron/engine/vertex.h"


namespace {


auto build_axes(const glm::uvec2& size, float width)
{
  using namespace apeiron::engine;

  constexpr std::uint32_t vertices_per_quad = 6;
  std::vector<Vertex_simple> vertices;

  // Axes
  std::uint32_t total_vertices = vertices_per_quad * 2;

  // Tick marks
  total_vertices += ((size.x + 1) * vertices_per_quad) + ((size.y + 1) * vertices_per_quad);

  vertices.reserve(total_vertices);
  vertices.append_range(primitive::quad_vertices<Vertex_simple>(static_cast<float>(size.x) + width,
      width, Face::Front));
  vertices.append_range(primitive::quad_vertices<Vertex_simple>(width,
     static_cast<float>(size.y) + width, Face::Front));

  // Tick labels
  std::vector<apeiron::opengl::Text_part> text_parts;

  // Ticks x
  {
    int first = -static_cast<int>(size.x) / 2;
    int last = static_cast<int>(size.x) / 2;

    for (int i=first; i<=last; ++i) {
      if (i != 0) {
        vertices.append_range(primitive::quad_vertices<Vertex_simple>(width, width * 2.0f,
            Face::Front, {static_cast<float>(i), width * 1.5f, 0.0f}));
        text_parts.emplace_back(std::to_string(i),
          glm::vec3{static_cast<float>(i) + 0.05f, 0.1f, 0.0f});
      }
    }
  }

  // Ticks y
  {
    int first = -static_cast<int>(size.x) / 2;
    int last = static_cast<int>(size.x) / 2;

    for (int i=first; i<=last; ++i) {
      if (i != 0) {
        vertices.append_range(primitive::quad_vertices<Vertex_simple>(width * 2.0f, width,
            Face::Front, {width * 1.5f, static_cast<float>(i), 0.0f}));
        text_parts.emplace_back(std::to_string(i),
            glm::vec3{0.1f, static_cast<float>(i) + 0.05f, 0.0f});
      }
    }
  }

  return std::tuple{vertices, text_parts};
}


}  // namespace


template<typename T> void apeiron::prefab::Xy_axes::init(const glm::uvec2& size, float width,
    const engine::Font<T>& font, float font_scale)
{
  if (size.x < 2 || size.y < 2) {
    return;
  }

  auto [vertices, text_parts] = build_axes(size, width);
  axes_.init(vertices);

  tick_labels_.transform().set_scale(glm::vec3{font_scale});
  tick_labels_.init(text_parts, font);
}


namespace apeiron::prefab {


template void Xy_axes::init(const glm::uvec2& size, float, const engine::Font<engine::Vertex>&, float);
template void Xy_axes::init(const glm::uvec2& size, float, const engine::Font<engine::Vertex_simple>&, float);
template void Xy_axes::init(const glm::uvec2& size, float, const engine::Font<engine::Vertex_normal>&, float);
template void Xy_axes::init(const glm::uvec2& size, float, const engine::Font<engine::Vertex_color>&, float);
template void Xy_axes::init(const glm::uvec2& size, float, const engine::Font<engine::Vertex_normal_color>&, float);


}  // namespace apeiron::prefab
