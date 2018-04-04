#ifndef APEIRON_EXAMPLE_PONEGLYPH_H
#define APEIRON_EXAMPLE_PONEGLYPH_H


#include <glm/glm.hpp>
#include "engine/entity.h"
#include "opengl/cuboid.h"


namespace apeiron::example {


class Poneglyph final : public engine::Entity
{
public:
  Poneglyph(const opengl::Cuboid* cuboid, float xrot, float yrot, float zrot)
      : cuboid_{cuboid}, rotation_magnitudes_{xrot, yrot, zrot} {}
  glm::vec3 rotation_magnitudes() const { return rotation_magnitudes_; }
  void render() const override { cuboid_->render(); }

private:
  const opengl::Cuboid* cuboid_;
  glm::vec3 rotation_magnitudes_;
};


}  // namespace apeiron::example


#endif  // APEIRON_EXAMPLE_PONEGLYPH_H
