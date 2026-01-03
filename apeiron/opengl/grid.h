#ifndef APEIRON_OPENGL_GRID_H
#define APEIRON_OPENGL_GRID_H


#include <glm/glm.hpp>
#include "apeiron/opengl/vertex_array.h"


namespace apeiron::opengl {


class Grid final : public Vertex_array
{
public:
  Grid() = default;
  Grid(const glm::vec2& size, const glm::uvec2& cells,
      const glm::vec4& color, bool edge = true, float line_width = 1.0f);
  void init(const glm::vec2& size, const glm::uvec2& cells,
      const glm::vec4& color, bool edge = true, float line_width = 1.0f);
  [[nodiscard]] glm::vec2 size() const { return size_; }
  [[nodiscard]] glm::uvec2 cells() const { return cells_; }
  void render() const override;

private:
  glm::vec2 size_ = glm::vec2{1.0f};
  glm::vec2 cells_ = glm::uvec2{1};
  float line_width_ = 1.0f;
};


}  // namespace apeiron::opengl


#endif  // APEIRON_OPENGL_GRID_H
