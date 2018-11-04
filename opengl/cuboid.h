#ifndef APEIRON_OPENGL_CUBOID_H
#define APEIRON_OPENGL_CUBOID_H


#include <glm/glm.hpp>
#include "opengl/shape.h"


namespace apeiron::opengl {


class Cuboid final : public Shape
{
public:
	Cuboid() = default;
  explicit Cuboid(glm::vec3 size, glm::vec3 position = glm::vec3{0.0f});
  Cuboid(glm::vec3 size, glm::vec4 color, glm::vec3 position = glm::vec3{0.0f});
  void set(glm::vec3 size, glm::vec3 position = glm::vec3{0.0f});
  void set(glm::vec3 size, glm::vec4 color, glm::vec3 position = glm::vec3{0.0f});
  void render() const override;
};


}  // namespace apeiron::opengl


#endif  // APEIRON_OPENGL_CUBOID_H
