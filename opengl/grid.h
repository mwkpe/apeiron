#ifndef APEIRON_OPENGL_GRID_H
#define APEIRON_OPENGL_GRID_H


#include <glm/glm.hpp>
#include "opengl/shape.h"


namespace apeiron::opengl {


class Grid final : public Shape
{
public:
  Grid(glm::vec2 size, std::size_t x_steps, std::size_t y_steps,
      glm::vec4 color, float line_width = 1.0f);
  glm::vec2 size() const { return size_; }
  void render() const override;

private:
  glm::vec2 size_;
  float line_width_;
};


}  // namespace apeiron::opengl


#endif  // APEIRON_OPENGL_GRID_H
