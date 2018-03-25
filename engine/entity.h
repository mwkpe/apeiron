#ifndef APEIRON_ENGINE_ENTITY_H
#define APEIRON_ENGINE_ENTITY_H


#include <string_view>
#include <glm/glm.hpp>
#include "opengl/model.h"


namespace apeiron::engine {


class Entity
{
public:
  Entity(const opengl::Shape* shape = nullptr) : shape_{shape}, scale_{1.0f, 1.0f, 1.0f} {}
  void set_position(float x, float y, float z) { position_ = glm::vec3{x, y, z}; };
  void set_position(glm::vec3 position) { position_ = position; };
  void set_rotation(float x, float y, float z) { rotation_ = glm::vec3{x, y, z}; };
  void set_rotation(glm::vec3 rotation) { rotation_ = rotation; };
  void set_scale(float x, float y, float z) { scale_ = glm::vec3{x, y, z}; };
  void set_scale(glm::vec3 scale) { scale_ = scale; };
  glm::vec3 position() const { return position_; }
  glm::vec3 rotation() const { return rotation_; }
  glm::vec3 scale() const { return scale_; }
  virtual void render() const { shape_->render(); };

protected:
  const opengl::Shape* shape_;
  glm::vec3 position_;
  glm::vec3 rotation_;
  glm::vec3 scale_;
};


}  // namespace apeiron::engine


#endif  // APEIRON_ENGINE_ENTITY_H
