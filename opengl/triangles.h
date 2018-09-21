#ifndef APEIRON_OPENGL_TRIANGLES_H
#define APEIRON_OPENGL_TRIANGLES_H


#include <vector>
#include <glm/glm.hpp>
#include "engine/vertex.h"
#include "opengl/shape.h"


namespace apeiron::opengl {


class Triangles final : public Shape
{
public:
  explicit Triangles(std::vector<engine::Vertex_simple>&& vertices);
  explicit Triangles(std::vector<engine::Vertex_color>&& vertices);
  void render() const override;
  void render(std::uint32_t start, std::uint32_t count) const override;
};


}  // namespace apeiron::opengl


#endif  // APEIRON_OPENGL_TRIANGLES_H
