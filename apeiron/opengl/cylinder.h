#ifndef APEIRON_OPENGL_CYLINDER_H
#define APEIRON_OPENGL_CYLINDER_H


#include <cstdint>
#include <glm/glm.hpp>
#include "apeiron/engine/enums.h"
#include "apeiron/opengl/vertex_array.h"


namespace apeiron::opengl {


class Cylinder final : public Vertex_array
{
public:
  void init(std::uint32_t points, float radius, float height, engine::Axis axis);
  void init(std::uint32_t points, float radius, float height, engine::Axis axis,
      const glm::vec4& color);

  void render() const override;
};


}  // namespace apeiron::opengl


#endif  // APEIRON_OPENGL_CYLINDER_H
