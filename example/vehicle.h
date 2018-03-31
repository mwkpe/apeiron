#ifndef APEIRON_EXAMPLE_VEHICLE_H
#define APEIRON_EXAMPLE_VEHICLE_H


#include "engine/entity.h"
#include "opengl/model.h"
#include "opengl/texture.h"


namespace apeiron::example {


class Vehicle final : public engine::Entity
{
public:
  void load_model(std::string_view filename);
  void load_texture(std::string_view filename);
  void render() const override { texture_.bind(); model_.render(); }

private:
  opengl::Model model_;
  opengl::Texture texture_;
};


}  // namespace apeiron::example


#endif  // APEIRON_EXAMPLE_VEHICLE_H
