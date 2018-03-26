#ifndef APEIRON_EXAMPLE_OPTIONS_H
#define APEIRON_EXAMPLE_OPTIONS_H


#include "engine/color.h"


namespace apeiron::example {


struct Options
{
  bool quit = false;
  bool show_gui = true;
  bool autorotate = true;
  bool wireframe = true;
  bool limit_fps = true;
  bool pirate_mode = false;
  int cylinder_points = 8;
  float cylinder_revs = 0.2f;
  int max_fps = 120;
  float velocity = 10.0f;
  float sensitivity = 0.02f;
  engine::Color main_color = engine::Color{0.2f, 0.905f, 0.968f, 1.0f};
};


}  // namespace apeiron::example


#endif  // APEIRON_EXAMPLE_OPTIONS_H
