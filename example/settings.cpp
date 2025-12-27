#include "settings.h"


#include <string>
#include <fstream>
#include "toml.hpp"
#include "apeiron/engine/error.h"

using namespace std::string_literals;


auto apeiron::example::load_settings(std::string_view filename) -> Settings
{
  std::ifstream fs{std::string{filename}};
  if (!fs.is_open()) {
    throw engine::Warning{std::string{"Could not open settings file: "} + std::string{filename}};
  }

  toml::table t;
  try {
    t = toml::parse_file(filename);
  }
  catch (const toml::parse_error& e)
  {
    throw engine::Warning{std::string{"Settings file parse error: "} + e.what()};
  }

  Settings settings;  // Contains default values
  settings.window_width = t["window_width"].value_or(settings.window_width);
  settings.window_height = t["window_height"].value_or(settings.window_height);
  settings.msaa_samples = t["msaa_samples"].value_or(settings.msaa_samples);
  settings.max_fps = t["max_fps"].value_or(settings.max_fps);
  settings.vsync = t["vsync"].value_or(settings.vsync);

  return settings;
}


void apeiron::example::save_settings(const Settings& settings, std::string_view filename)
{
  toml::table t;
  t.insert("window_width", settings.window_width);
  t.insert("window_height", settings.window_height);
  t.insert("msaa_samples", settings.msaa_samples);
  t.insert("max_fps", settings.max_fps);
  t.insert("vsync", settings.vsync);

  if (std::ofstream fs{std::string{filename}, std::ios::binary}; fs.is_open()) {
    fs << t;
  }
}
