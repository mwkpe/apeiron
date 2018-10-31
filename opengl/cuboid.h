#ifndef APEIRON_OPENGL_CUBOID_H
#define APEIRON_OPENGL_CUBOID_H


#include <glm/glm.hpp>
#include "opengl/shape.h"


namespace apeiron::opengl {


class Cuboid final : public Shape
{
public:
  explicit Cuboid(glm::vec3 size);
  Cuboid(glm::vec3 size, glm::vec4 color);
  void render() const override;
};


}  // namespace apeiron::opengl


#endif  // APEIRON_OPENGL_CUBOID_H
