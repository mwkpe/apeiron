#ifndef APEIRON_ENGINE_ENTITY_H
#define APEIRON_ENGINE_ENTITY_H


#include <string_view>
#include <glm/glm.hpp>
#include "opengl/model.h"


namespace apeiron::engine {


class Entity
{
public:
  void set_position(float x, float y, float z) { position_ = glm::vec3{x, y, z}; };
  void set_rotation(float x, float y, float z) { rotation_ = glm::vec3{x, y, z}; };
  glm::vec3 position() const { return position_; }
  glm::vec3 rotation() const { return rotation_; }
  virtual void render() const {};

protected:
  glm::vec3 position_;
  glm::vec3 rotation_;
  glm::vec3 scale_;
};


}  // namespace apeiron::engine


#endif  // APEIRON_ENGINE_ENTITY_H
