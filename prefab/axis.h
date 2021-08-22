#ifndef APEIRON_PREFAB_AXIS_H
#define APEIRON_PREFAB_AXIS_H


#include "engine/entity.h"
#include "opengl/cylinder.h"


namespace apeiron::prefab {


class Axis final : public engine::Entity
{
public:
  Axis() = default;
  Axis(int points, float radius, float height) : axis_{points, radius, height} {}
  void init(int points, float radius, float height) { axis_.init(points, radius, height); }
  void render() const override { axis_.render(); }

private:
  opengl::Cylinder axis_;
};


}  // namespace apeiron::prefab


#endif  // APEIRON_PREFAB_AXIS_H
