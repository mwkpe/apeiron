#ifndef APEIRON_EXAMPLE_VEHICLE_H
#define APEIRON_EXAMPLE_VEHICLE_H


#include <cstdint>
#include "engine/entity.h"
#include "opengl/model.h"
#include "opengl/cuboid.h"
#include "opengl/texture.h"


namespace apeiron::example {


class Vehicle final : public engine::Entity
{
public:
  explicit Vehicle(const glm::vec3& size) : Entity{size}, bounding_box_{size, true, 2.0f} {}
  void load_model(std::string_view filename, std::uint32_t flags);
  void load_texture(std::string_view filename);
  void render() const override { texture_.bind(); model_.render();  }
  void render_bounds() const override { bounding_box_.render(); };

private:
  opengl::Model model_;
  opengl::Texture texture_;
  opengl::Cuboid bounding_box_;
};


}  // namespace apeiron::example


#endif  // APEIRON_EXAMPLE_VEHICLE_H
