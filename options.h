#ifndef APEIRON_OPTIONS_H
#define APEIRON_OPTIONS_H


#include "color.h"


namespace apeiron {


struct Options
{
  bool quit = false;
  bool show_gui = true;
  bool autorotate = true;
  bool wireframe = true;
  bool strobe = false;
  bool limit_fps = true;
  int cylinder_points = 8;
  int max_fps = 120;
  float velocity = 2.0f;
  float sensitivity = 0.02f;
  Color main_color = Color{0.2f, 0.905f, 0.968f, 1.0f};
};


}  // namespace apeiron


#endif  //APEIRON_OPTIONS_H
