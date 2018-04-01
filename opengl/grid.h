#ifndef APEIRON_OPENGL_GRID_H
#define APEIRON_OPENGL_GRID_H


#include <tuple>
#include "opengl/shape.h"


namespace apeiron::opengl {


class Grid final : public Shape
{
public:
  Grid(std::tuple<float, float, float> size, std::tuple<float, float, float> spacing, float precision);
  void render() const override;
};


}  // namespace apeiron::opengl


#endif  // APEIRON_OPENGL_GRID_H
