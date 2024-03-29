#ifndef APEIRON_PREFAB_AXES_H
#define APEIRON_PREFAB_AXES_H


#include <cstdint>
#include "apeiron/opengl/renderer.h"
#include "apeiron/prefab/axis.h"


namespace apeiron::prefab {


class Axes final
{
public:
  Axes() = default;
  Axes(std::uint32_t points, float radius, float height);
  void init(int points, float radius, float height);
  void render(opengl::Renderer& renderer) const;

private:
  Axis x_axis_;
  Axis y_axis_;
  Axis z_axis_;
};


}  // namespace apeiron::prefab


#endif  // APEIRON_PREFAB_AXES_H
