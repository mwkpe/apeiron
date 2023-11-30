#ifndef APEIRON_EXAMPLE_CUBE_H
#define APEIRON_EXAMPLE_CUBE_H


#include <glm/glm.hpp>
#include "apeiron/engine/entity.h"
#include "apeiron/opengl/cuboid.h"


namespace apeiron::example {


class Cube final : public engine::Entity
{
public:
  Cube(const opengl::Cuboid* cuboid, float xrot, float yrot, float zrot)
      : cuboid_{cuboid}, rotation_magnitudes_{xrot, yrot, zrot} {}
  [[nodiscard]] glm::vec3 rotation_magnitudes() const { return rotation_magnitudes_; }
  void render() const override { cuboid_->render(); }

private:
  const opengl::Cuboid* cuboid_;
  glm::vec3 rotation_magnitudes_;
};


}  // namespace apeiron::example


#endif  // APEIRON_EXAMPLE_CUBE_H
