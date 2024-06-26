#ifndef APEIRON_OPENGL_POINTS_H
#define APEIRON_OPENGL_POINTS_H


#include <vector>
#include "apeiron/engine/vertex.h"
#include "apeiron/opengl/shape.h"


namespace apeiron::opengl {


class Points final : public Shape
{
public:
  Points() = default;
  explicit Points(const std::vector<engine::Vertex_simple>& vertices);
  explicit Points(const std::vector<engine::Vertex_color>& vertices);
  void set(const std::vector<engine::Vertex_simple>& vertices);
  void set(const std::vector<engine::Vertex_color>& vertices);
  void set_size(float size) { point_size_ = size; }
  void render() const override;
  void render(std::uint32_t start, std::uint32_t count) const override;

private:
  float point_size_ = 1.0f;
};


}  // namespace apeiron::opengl


#endif  // APEIRON_OPENGL_POINTS_H
