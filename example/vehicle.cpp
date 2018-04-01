#include "vehicle.h"


void apeiron::example::Vehicle::load_model(std::string_view filename, int flags)
{
  model_.load(filename, flags);
}


void apeiron::example::Vehicle::load_texture(std::string_view filename)
{
  texture_.load(filename);
}
