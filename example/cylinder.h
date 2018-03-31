#ifndef APEIRON_EXAMPLE_CYLINDER_H
#define APEIRON_EXAMPLE_CYLINDER_H


#include <glm/glm.hpp>
#include "engine/entity.h"
#include "opengl/cylinder.h"


namespace apeiron::example {


class Cylinder final : public engine::Entity
{
public:
  Cylinder(int points, float xrot, float yrot, float zrot)
      : cylinder_{points}, rotation_magnitudes_{xrot, yrot, zrot} {}
  glm::vec3 rotation_magnitudes() const { return rotation_magnitudes_; }
  int points() const { return cylinder_.points(); }
  void rebuild(int points) { cylinder_.construct(points); }
  void render() const override { cylinder_.render(); }

private:
  opengl::Cylinder cylinder_;
  glm::vec3 rotation_magnitudes_;
};


}  // namespace apeiron::example


#endif  // APEIRON_EXAMPLE_CYLINDER_H
