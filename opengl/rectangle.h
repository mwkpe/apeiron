#ifndef APEIRON_OPENGL_RECTANGLE_H
#define APEIRON_OPENGL_RECTANGLE_H


#include <glm/glm.hpp>
#include "opengl/shape.h"


namespace apeiron::opengl {


class Rectangle final : public Shape
{
public:
  Rectangle(float width, float height);
  void render() const override;
};


}  // namespace apeiron::opengl


#endif  // APEIRON_OPENGL_RECTANGLE_H
