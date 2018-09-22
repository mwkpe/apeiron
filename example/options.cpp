#include "options.h"


#include <string>
#include <sstream>
#include <fstream>
#include "nlohmann/json.hpp"
#include "engine/error.h"


using json = nlohmann::json;
using namespace std::string_literals;


auto apeiron::example::load_configuration(std::string_view filename) -> Options
{
  std::ifstream fs{std::string{filename}};
  if (!fs.is_open())
    throw engine::Warning{std::string{"Could not open config file: "} + std::string{filename}};

  std::stringstream ss;
  ss << fs.rdbuf();
  fs.close();
  json j;

  try {
    j = json::parse(ss.str());
    if (j.is_null())
      throw engine::Warning{std::string{"Config file empty"}};

    Options options;  // Contains default values
    options.window_width = j.value("window_width", options.window_width);
    options.window_height = j.value("window_height", options.window_height);
    options.msaa_samples = j.value("msaa_samples", options.msaa_samples);
    options.max_fps = j.value("max_fps", options.max_fps);
    options.vsync = j.value("vsync", options.vsync);
    return options;
  }
  catch (const json::exception& e) {
    throw engine::Warning{std::string{"Config file parse error: "} + e.what()};
  }
}


void apeiron::example::save_configuration(const Options& options, std::string_view filename)
{
  json j;
  j["window_width"] = options.window_width;
  j["window_height"] = options.window_height;
  j["msaa_samples"] = options.msaa_samples;
  j["max_fps"] = options.max_fps;
  j["vsync"] = options.vsync;

  if (std::ofstream fs{std::string{filename}, std::ios::binary}; fs.is_open()) {
    fs << j.dump(2);
  }
}
