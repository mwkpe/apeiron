#ifndef APEIRON_PREFAB_AXIS_H
#define APEIRON_PREFAB_AXIS_H


#include <cstdint>
#include "apeiron/engine/entity.h"
#include "apeiron/opengl/cylinder.h"


namespace apeiron::prefab {


class Axis final : public engine::Entity
{
public:
  Axis() = default;
  Axis(std::uint32_t points, float radius, float height) : axis_{points, radius, height} {}
  void init(int points, float radius, float height) { axis_.init(points, radius, height); }
  void render() const override { axis_.render(); }

private:
  opengl::Cylinder axis_;
};


}  // namespace apeiron::prefab


#endif  // APEIRON_PREFAB_AXIS_H
