#ifndef APEIRON_OPENGL_WIRE_CUBOID_H
#define APEIRON_OPENGL_WIRE_CUBOID_H


#include <glm/glm.hpp>
#include "opengl/shape.h"


namespace apeiron::opengl {


class Wire_cuboid final : public Shape
{
public:
  Wire_cuboid() = default;
  explicit Wire_cuboid(glm::vec3 size, glm::vec3 position = glm::vec3{0.0f});
  Wire_cuboid(glm::vec3 size, glm::vec4 color, glm::vec3 position = glm::vec3{0.0f});
  void set(glm::vec3 size, glm::vec3 position = glm::vec3{0.0f});
  void set(glm::vec3 size, glm::vec4 color, glm::vec3 position = glm::vec3{0.0f});
  void set_line_width(float line_width) { line_width_ = line_width; }
  void render() const override;

private:
  float line_width_ = 1.0f;
};


}  // namespace apeiron::opengl


#endif  // APEIRON_OPENGL_WIRE_CUBOID_H
