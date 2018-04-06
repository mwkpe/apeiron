#ifndef APEIRON_OPENGL_POLYGON_H
#define APEIRON_OPENGL_POLYGON_H


#include <vector>
#include <glm/glm.hpp>
#include "opengl/shape.h"


namespace apeiron::opengl {


class Polygon final : public Shape
{
public:
  explicit Polygon(std::vector<float>&& vertices);
  void render() const override;
};


}  // namespace apeiron::opengl


#endif  // APEIRON_OPENGL_POLYGON_H
