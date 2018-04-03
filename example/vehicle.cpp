#include "vehicle.h"


void apeiron::example::Vehicle::load_model(std::string_view filename, std::uint32_t flags)
{
  model_.load(filename, flags);
}


void apeiron::example::Vehicle::load_texture(std::string_view filename)
{
  texture_.load(filename);
}
