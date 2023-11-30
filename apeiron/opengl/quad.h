#ifndef APEIRON_OPENGL_QUAD_H
#define APEIRON_OPENGL_QUAD_H


#include <glm/glm.hpp>
#include "apeiron/engine/vertex.h"
#include "apeiron/engine/primitive.h"
#include "apeiron/opengl/shape.h"


namespace apeiron::opengl {


class Quad final : public Shape
{
public:
  Quad() = default;
  Quad(float width, float height, engine::Face face = engine::Face::Front,
      const glm::vec3& position = glm::vec3{0.0f});
  Quad(float width, float height, const glm::vec4& color, engine::Face face = engine::Face::Front,
      const glm::vec3& position = glm::vec3{0.0f});

  template<typename T = engine::Vertex> void set(float width, float height,
      engine::Face face = engine::Face::Front, const glm::vec3& position = glm::vec3{0.0f});
  template<typename T = engine::Vertex> void set(float width, float height, const glm::vec4& color,
      engine::Face face = engine::Face::Front, const glm::vec3& position = glm::vec3{0.0f});
  template<typename T = engine::Vertex> void set(float width, float height, const glm::mat4& color,
      engine::Face face = engine::Face::Front, const glm::vec3& position = glm::vec3{0.0f});

  void render() const override;
};


}  // namespace apeiron::opengl


#endif  // APEIRON_OPENGL_QUAD_H
