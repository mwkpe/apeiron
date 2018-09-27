#ifndef APEIRON_OPENGL_CUBOID_H
#define APEIRON_OPENGL_CUBOID_H


#include <glm/glm.hpp>
#include "opengl/shape.h"


namespace apeiron::opengl {


class Cuboid final : public Shape
{
public:
  explicit Cuboid(glm::vec3 size, bool wireframe = false, float line_width = 1.0f);
  Cuboid(glm::vec3 size, glm::vec4 color);
  void render() const override;

private:
  bool wireframe_ = false;
  float line_width_ = 1.0f;
};


}  // namespace apeiron::opengl


#endif  // APEIRON_OPENGL_CUBOID_H
