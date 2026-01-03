#ifndef APEIRON_PREFAB_GROUND_H
#define APEIRON_PREFAB_GROUND_H


#include <glm/glm.hpp>
#include "apeiron/engine/entity.h"
#include "apeiron/opengl/grid.h"


namespace apeiron::prefab {


class Grid final : public engine::Entity
{
public:
  Grid() = default;
  Grid(const glm::vec2& size, const glm::uvec2& cells,
      const glm::vec4& color, bool edge = true, float line_width = 1.0f);
  void init(const glm::vec2& size, const glm::uvec2& cells,
      const glm::vec4& color, bool edge = true, float line_width = 1.0f);
  [[nodiscard]] glm::vec2 size() const { return grid_.size(); }
  [[nodiscard]] glm::uvec2 cells() const { return grid_.cells(); }
  void render() const override { grid_.render(); };

private:
  opengl::Grid grid_;
};


}  // namespace apeiron::prefab


#endif  // APEIRON_PREFAB_GROUND_H
