#ifndef APEIRON_EXAMPLE_GROUND_H
#define APEIRON_EXAMPLE_GROUND_H


#include <tuple>
#include "engine/entity.h"
#include "opengl/grid.h"


namespace apeiron::example {


class Ground final : public engine::Entity
{
public:
  Ground(std::tuple<float, float, float> size, std::tuple<float, float, float> spacing, float precision)
      : grid_{size, spacing, precision} {}
  void render() const override { grid_.render(); }

private:
  opengl::Grid grid_;
};


}  // namespace apeiron::example


#endif  // APEIRON_EXAMPLE_GROUND_H
