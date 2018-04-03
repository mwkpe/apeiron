#ifndef APEIRON_EXAMPLE_GROUND_H
#define APEIRON_EXAMPLE_GROUND_H


#include <glm/glm.hpp>
#include "engine/entity.h"
#include "opengl/grid.h"


namespace apeiron::example {


class Ground final : public engine::Entity
{
public:
  Ground(const glm::vec3& size, const glm::vec3& spacing, float precision, const glm::vec3& color,
      float line_width) : Entity{size}, grid_{size, spacing, precision, color, line_width} {}
  void render() const override { grid_.render(); }

private:
  opengl::Grid grid_;
};


}  // namespace apeiron::example


#endif  // APEIRON_EXAMPLE_GROUND_H
