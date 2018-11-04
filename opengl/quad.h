#ifndef APEIRON_OPENGL_QUAD_H
#define APEIRON_OPENGL_QUAD_H


#include <glm/glm.hpp>
#include "opengl/shape.h"


namespace apeiron::opengl {


class Quad final : public Shape
{
public:
  Quad() = default;
  Quad(float width, float height);
  Quad(float width, float height, glm::vec4 color);
  void set(float width, float height);
  void set(float width, float height, glm::vec4 color);
  void render() const override;
};


}  // namespace apeiron::opengl


#endif  // APEIRON_OPENGL_QUAD_H
