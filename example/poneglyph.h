#ifndef APEIRON_EXAMPLE_PONEGLYPH_H
#define APEIRON_EXAMPLE_PONEGLYPH_H


#include <glm/glm.hpp>
#include "engine/entity.h"
#include "opengl/cube.h"


namespace apeiron::example {


class Poneglyph final : public engine::Entity
{
public:
  Poneglyph(const opengl::Cube* cube, float xrot, float yrot, float zrot)
      : Entity{cube}, rotation_magnitudes_{xrot, yrot, zrot} {}
  glm::vec3 rotation_magnitudes() const { return rotation_magnitudes_; }

private:
  glm::vec3 rotation_magnitudes_;
};


}  // namespace apeiron::example


#endif // APEIRON_EXAMPLE_PONEGLYPH_H