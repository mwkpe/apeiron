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
  bool vsync = false;
  bool limit_fps = true;
  bool lighting = true;
  bool invert_color = false;
  bool desaturate = false;
  bool show_light = true;
  bool show_ground_highlight = false;
  bool show_cubes = false;
  bool rotate_cubes = true;
  int window_width = 1280;
  int window_height = 720;
  int msaa_samples = 4;
  int af_samples = 1;
  int max_fps = 120;
  float camera_speed = 10.0f;
  float camera_sensitivity = 0.02f;
  float light_position_z = -4.0f;
  float desaturation_strength = 0.5f;
  glm::vec4 main_color = {1.0f, 1.0f, 1.0f, 1.0f};
  std::string world_text = "Hello world!";
  std::string screen_text = "Hello screen!";
};


Settings load_settings(std::string_view filename);
void save_settings(const Settings& settings, std::string_view filename);


}  // namespace apeiron::example


#endif  // APEIRON_EXAMPLE_SETTINGS_H
