#ifndef APEIRON_OPENGL_LINE_ARRAY_H
#define APEIRON_OPENGL_LINE_ARRAY_H


#include <vector>
#include <glm/glm.hpp>
#include "opengl/shape.h"


namespace apeiron::opengl {


class Line_array final : public Shape
{
public:
  Line_array(std::vector<float>&& vertices, bool vertex_color, float line_width = 1.0f);
  void render() const override;

private:
  float line_width_;
};


}  // namespace apeiron::opengl


#endif  // APEIRON_OPENGL_LINE_ARRAY_H
