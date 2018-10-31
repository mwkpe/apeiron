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
  Triangles() = default;
  explicit Triangles(const std::vector<engine::Vertex>& vertices);
  explicit Triangles(const std::vector<engine::Vertex_simple>& vertices);
  explicit Triangles(const std::vector<engine::Vertex_normal>& vertices);
  explicit Triangles(const std::vector<engine::Vertex_color>& vertices);
  explicit Triangles(const std::vector<engine::Vertex_texcoords>& vertices);
  explicit Triangles(const std::vector<engine::Vertex_normal_color>& vertices);
  explicit Triangles(const std::vector<engine::Vertex_normal_texcoords>& vertices);
  void set(const std::vector<engine::Vertex>& vertices);
  void set(const std::vector<engine::Vertex_simple>& vertices);
  void set(const std::vector<engine::Vertex_normal>& vertices);
  void set(const std::vector<engine::Vertex_color>& vertices);
  void set(const std::vector<engine::Vertex_texcoords>& vertices);
  void set(const std::vector<engine::Vertex_normal_color>& vertices);
  void set(const std::vector<engine::Vertex_normal_texcoords>& vertices);
  void render() const override;
  void render(std::uint32_t start, std::uint32_t count) const override;
};


}  // namespace apeiron::opengl


#endif  // APEIRON_OPENGL_TRIANGLES_H
