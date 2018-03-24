#ifndef APEIRON_OPENGL_CUBE_H
#define APEIRON_OPENGL_CUBE_H


#include "opengl/shape.h"


namespace apeiron::opengl {


class Cube final : public Shape
{
public:
  Cube();
  ~Cube();
  void render() const override;
};


}  // namespace apeiron::opengl


#endif  // APEIRON_OPENGL_CUBE_H
