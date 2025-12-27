#ifndef APEIRON_OPENGL_CUBOID_H
#define APEIRON_OPENGL_CUBOID_H


#include <glm/glm.hpp>
#include "apeiron/engine/vertex.h"
#include "apeiron/opengl/vertex_array.h"


namespace apeiron::opengl {


class Cuboid final : public Vertex_array
{
public:
  Cuboid() = default;
  explicit Cuboid(const glm::vec3& size, const glm::vec3& position = glm::vec3{0.0f});
  Cuboid(const glm::vec3& size, const glm::vec4& color,
      const glm::vec3& position = glm::vec3{0.0f});

  template<typename T = engine::Vertex> void set(const glm::vec3& size,
      const glm::vec3& position = glm::vec3{0.0f});
  template<typename T = engine::Vertex> void set(const glm::vec3& size, const glm::vec4& color,
      const glm::vec3& position = glm::vec3{0.0f});

  void render() const override;
};


}  // namespace apeiron::opengl


#endif  // APEIRON_OPENGL_CUBOID_H
