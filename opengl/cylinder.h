#ifndef APEIRON_OPENGL_CYLINDER_H
#define APEIRON_OPENGL_CYLINDER_H


#include "opengl/shape.h"


namespace apeiron::opengl {


class Cylinder final : public Shape
{
public:
  Cylinder() = default;
  explicit Cylinder(int points, float radius = 0.5f, float height = 1.0f);
  void init(int points, float radius = 0.5f, float height = 1.0f);
  void construct(int points, float radius = 0.5f, float height = 1.0f);
  int points() const { return points_; }
  void render() const override;

private:
  int points_;
};


}  // namespace apeiron::opengl


#endif  // APEIRON_OPENGL_CYLINDER_H
