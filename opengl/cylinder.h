#ifndef APEIRON_OPENGL_CYLINDER_H
#define APEIRON_OPENGL_CYLINDER_H


#include "opengl/shape.h"


namespace apeiron::opengl {


class Cylinder final : public Shape
{
public:
  explicit Cylinder(int points);
  void render() const override;
  void construct(int points);
  int points() const { return points_; }

private:
  int points_;
};


}  // namespace apeiron::opengl


#endif  // APEIRON_OPENGL_CYLINDER_H
