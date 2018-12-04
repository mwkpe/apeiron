#ifndef APEIRON_OPENGL_QUAD_H
#define APEIRON_OPENGL_QUAD_H


#include <glm/glm.hpp>
#include "engine/vertex.h"
#include "engine/primitive.h"
#include "opengl/shape.h"


namespace apeiron::opengl {


class Quad final : public Shape
{
public:
  Quad() = default;
  Quad(float width, float height, engine::Face face = engine::Face::Front,
      glm::vec3 position = glm::vec3{0.0f});
  Quad(float width, float height, glm::vec4 color, engine::Face face = engine::Face::Front,
      glm::vec3 position = glm::vec3{0.0f});
  template<typename T = engine::Vertex> void set(float width, float height,
      engine::Face face = engine::Face::Front, glm::vec3 position = glm::vec3{0.0f});
  template<typename T = engine::Vertex> void set(float width, float height, glm::vec4 color,
      engine::Face face = engine::Face::Front, glm::vec3 position = glm::vec3{0.0f});
  void render() const override;
};


}  // namespace apeiron::opengl


#endif  // APEIRON_OPENGL_QUAD_H
