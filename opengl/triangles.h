#ifndef APEIRON_OPENGL_TRIANGLES_H
#define APEIRON_OPENGL_TRIANGLES_H


#include <vector>
#include <glm/glm.hpp>
#include "opengl/shape.h"


namespace apeiron::opengl {


class Triangles final : public Shape
{
public:
  Triangles() = default;
  template<typename T> explicit Triangles(const std::vector<T>& vertices);
  template<typename T> void set(const std::vector<T>& vertices);
  void render() const override;
  void render(std::uint32_t start, std::uint32_t count) const override;
};


}  // namespace apeiron::opengl


#endif  // APEIRON_OPENGL_TRIANGLES_H
