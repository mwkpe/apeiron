#ifndef APEIRON_OPENGL_CUBOID_H
#define APEIRON_OPENGL_CUBOID_H


#include <glm/glm.hpp>
#include "opengl/shape.h"


namespace apeiron::opengl {


class Cuboid final : public Shape
{
public:
  explicit Cuboid(const glm::vec3& size, bool wireframe = false, float line_width = 1.0f);
  void render() const override;

private:
  bool wireframe_;
  float line_width_;
};


}  // namespace apeiron::opengl


#endif  // APEIRON_OPENGL_CUBOID_H
