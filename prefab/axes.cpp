#include "axes.h"



apeiron::prefab::Axes::Axes(int points, float radius, float height) :
    x_axis_{points, radius, height}, y_axis_{points, radius, height},
    z_axis_{points, radius, height}
{
  // Rotate so +z goes outside the screen, -z into the screen
  z_axis_.set_rotation_deg(90.0f, 0.0f, 0.0f);
  // Rotate so -x goes to the left and +x goes to the right
  x_axis_.set_rotation_deg(0.0f, 0.0f, -90.0f);
  // Y is up axis, cylinder is already build in this orientation
}


void apeiron::prefab::Axes::render(opengl::Renderer& renderer) const
{
  renderer.use_color_shading();
  renderer.render(x_axis_, {1.0f, 0.0f, 0.0f, 1.0f});
  renderer.render(y_axis_, {0.0f, 1.0f, 0.0f, 1.0f});
  renderer.render(z_axis_, {0.0f, 0.0f, 1.0f, 1.0f});
}
