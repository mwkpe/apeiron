#ifndef APEIRON_EXAMPLE_VEHICLE_H
#define APEIRON_EXAMPLE_VEHICLE_H


#include "engine/entity.h"
#include "opengl/model.h"


namespace apeiron::example {


class Vehicle final : public engine::Entity
{
public:
  void load_model(std::string_view filename);

private:
  opengl::Model model_;
};


}  // namespace apeiron::example


#endif  // APEIRON_EXAMPLE_VEHICLE_H
