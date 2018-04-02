#ifndef APEIRON_EXAMPLE_OPTIONS_H
#define APEIRON_EXAMPLE_OPTIONS_H


#include <string_view>
#include "engine/color.h"


namespace apeiron::example {


struct Options
{
  bool quit = false;
  bool show_gui = true;
  bool autorotate = true;
  bool wireframe = false;
  bool lighting = false;
  bool limit_fps = true;
  bool pirate_mode = false;
  int window_width = 1280;
  int window_height = 720;
  int msaa_samples = 4;
  int cylinder_points = 8;
  int max_fps = 90;
  float light_distance = 2.5f;
  float cylinder_distance = 25.0f;
  float cylinder_revs = 0.2f;
  float velocity = 10.0f;
  float sensitivity = 0.02f;
  engine::Color main_color = engine::Color{0.9f, 0.9f, 0.9f, 1.0f};
};


Options load_configuration(std::string_view filename);
void save_configuration(const Options& options, std::string_view filename);


}  // namespace apeiron::example


#endif  // APEIRON_EXAMPLE_OPTIONS_H
