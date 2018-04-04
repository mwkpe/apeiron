#ifndef APEIRON_OPENGL_RECTANGLE_H
#define APEIRON_OPENGL_RECTANGLE_H


#include <glm/glm.hpp>
#include "opengl/shape.h"


namespace apeiron::opengl {


class Rectangle final : public Shape
{
public:
  explicit Rectangle(float x, float y, bool wireframe = false, float line_width = 1.0f);
  void render() const override;

private:
  bool wireframe_;
  float line_width_;
};


}  // namespace apeiron::opengl


#endif  // APEIRON_OPENGL_RECTANGLE_H
