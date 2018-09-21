#ifndef APEIRON_EXAMPLE_AXES_H
#define APEIRON_EXAMPLE_AXES_H


#include "opengl/renderer.h"
#include "example/axis.h"


namespace apeiron::example {


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


}  // namespace apeiron::example


#endif  // APEIRON_EXAMPLE_AXES_H
