#include "vehicle.h"


void apeiron::example::Vehicle::load_model(std::string_view filename)
{
  model_.load(filename);
}


void apeiron::example::Vehicle::load_texture(std::string_view filename)
{
  texture_.load(filename);
}
