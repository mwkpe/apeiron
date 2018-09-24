#ifndef APEIRON_PREFAB_AXES_H
#define APEIRON_PREFAB_AXES_H


#include "opengl/renderer.h"
#include "prefab/axis.h"


namespace apeiron::prefab {


class Axes final
{
public:
  Axes(int points, float radius, float height);
  void render(opengl::Renderer& renderer) const;

private:
  Axis x_axis_;
  Axis y_axis_;
  Axis z_axis_;
};


}  // namespace apeiron::prefab


#endif  // APEIRON_PREFAB_AXES_H
