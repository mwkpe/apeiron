#ifndef APEIRON_PREFAB_GROUND_H
#define APEIRON_PREFAB_GROUND_H


#include <glm/glm.hpp>
#include "engine/entity.h"
#include "opengl/grid.h"


namespace apeiron::prefab {


class Ground final : public engine::Entity
{
public:
  Ground() = default;
  Ground(const glm::vec2& size, std::size_t x_steps, std::size_t y_steps,
      const glm::vec4& color, float line_width = 1.0f);
  void init(const glm::vec2& size, std::size_t x_steps, std::size_t y_steps,
      const glm::vec4& color, float line_width = 1.0f);
  void render() const override { grid_.render(); }

private:
  opengl::Grid grid_;
};


}  // namespace apeiron::prefab


#endif  // APEIRON_PREFAB_GROUND_H
