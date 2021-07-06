#ifndef APEIRON_EXAMPLE_SETTINGS_H
#define APEIRON_EXAMPLE_SETTINGS_H


#include <string>
#include <string_view>
#include <glm/glm.hpp>


namespace apeiron::example {


struct Settings
{
  bool quit = false;
  bool show_menu = true;
  bool wireframe = false;
  bool lighting = true;
  bool show_light = true;
  bool vsync = false;
  bool limit_fps = true;
  bool show_cubes = false;
  bool rotate_cubes = true;
  int window_width = 1280;
  int window_height = 720;
  int msaa_samples = 4;
  int af_samples = 1;
  int cylinder_points = 8;
  int max_fps = 144;
  float light_distance = -5.0f;
  float cylinder_revs = 0.2f;
  float camera_speed = 10.0f;
  float camera_sensitivity = 0.02f;
  glm::vec4 main_color = {1.0f, 1.0f, 1.0f, 1.0f};
  std::string text = "Hello world!";
};


Settings load_settings(std::string_view filename);
void save_settings(const Settings& settings, std::string_view filename);


}  // namespace apeiron::example


#endif  // APEIRON_EXAMPLE_SETTINGS_H
