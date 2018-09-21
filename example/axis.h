#ifndef APEIRON_EXAMPLE_AXIS_H
#define APEIRON_EXAMPLE_AXIS_H


#include "engine/entity.h"
#include "opengl/cylinder.h"


namespace apeiron::example {


class Axis final : public engine::Entity
{
public:
  Axis(int points, float radius, float height) : axis_{points, radius, height} {}
  void render() const override { axis_.render(); }

private:
  opengl::Cylinder axis_;
};


}  // namespace apeiron::example


#endif  // APEIRON_EXAMPLE_AXIS_H
