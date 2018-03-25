#include "vehicle.h"


void apeiron::example::Vehicle::load_model(std::string_view filename)
{
  model_.load(filename);
  shape_ = static_cast<const opengl::Shape*>(&model_);
}
