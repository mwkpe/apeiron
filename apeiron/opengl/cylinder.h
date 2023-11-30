#ifndef APEIRON_OPENGL_CYLINDER_H
#define APEIRON_OPENGL_CYLINDER_H


#include <cstdint>
#include "apeiron/opengl/shape.h"


namespace apeiron::opengl {


class Cylinder final : public Shape
{
public:
  Cylinder() = default;
  explicit Cylinder(std::uint32_t points, float radius = 0.5f, float height = 1.0f);
  void init(std::uint32_t points, float radius = 0.5f, float height = 1.0f);
  void construct(std::uint32_t points, float radius = 0.5f, float height = 1.0f);
  [[nodiscard]] std::uint32_t points() const { return points_; }
  void render() const override;

private:
  std::uint32_t points_ = 8;
};


}  // namespace apeiron::opengl


#endif  // APEIRON_OPENGL_CYLINDER_H
