#ifndef APEIRON_EXAMPLE_GROUND_H
#define APEIRON_EXAMPLE_GROUND_H


#include <glm/glm.hpp>
#include "engine/entity.h"
#include "opengl/grid.h"


namespace apeiron::example {


class Ground final : public engine::Entity
{
public:
  Ground(glm::vec2 size, std::size_t x_steps, std::size_t y_steps, glm::vec4 color,
      float line_width = 1.0f) : grid_{size, x_steps, y_steps, color, line_width} {}
  void render() const override { grid_.render(); }

private:
  opengl::Grid grid_;
};


}  // namespace apeiron::example


#endif  // APEIRON_EXAMPLE_GROUND_H
