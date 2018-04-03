#ifndef APEIRON_OPENGL_GRID_H
#define APEIRON_OPENGL_GRID_H


#include <glm/glm.hpp>
#include "opengl/shape.h"


namespace apeiron::opengl {


class Grid final : public Shape
{
public:
  Grid(const glm::vec3& size, const glm::vec3& spacing, float precision,
      const glm::vec3& color, float line_width = 1.0f);
  glm::vec3 size() const { return size_; }
  glm::vec3 spacing() const { return spacing_; }
  void render() const override;

private:
  glm::vec3 size_;
  glm::vec3 spacing_;
  float line_width_;
};


}  // namespace apeiron::opengl


#endif  // APEIRON_OPENGL_GRID_H
