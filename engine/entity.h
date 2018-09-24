#ifndef APEIRON_ENGINE_ENTITY_H
#define APEIRON_ENGINE_ENTITY_H


#include <string_view>
#include <glm/glm.hpp>


namespace apeiron::engine {


class Entity
{
public:
  Entity() = default;
  explicit Entity(glm::vec3 size) : size_{size} {}
  void set_size(float x, float y, float z) { size_ = glm::vec3{x, y, z}; };
  void set_size(glm::vec3 size) { size_ = size; };
  void set_center(float x, float y, float z) { center_ = glm::vec3{x, y, z}; };
  void set_center(glm::vec3 center) { center_ = center; };
  void set_position(float x, float y, float z) { position_ = glm::vec3{x, y, z}; };
  void set_position(glm::vec3 position) { position_ = position; };
  void set_rotation(float x, float y, float z) { rotation_ = glm::vec3{x, y, z}; };
  void set_rotation(glm::vec3 rotation) { rotation_ = rotation; };
  void set_scale(float x, float y, float z) { scale_ = glm::vec3{x, y, z}; };
  void set_scale(glm::vec3 scale) { scale_ = scale; };
  void set_color(float r, float g, float b, float a = 1.0f) { color_ = glm::vec4{r, g, b, a}; };
  void set_color(glm::vec4 color) { color_ = color; };
  glm::vec3 center() const { return center_; }
  glm::vec3 size() const { return size_; }
  glm::vec3 position() const { return position_; }
  glm::vec3 rotation() const { return rotation_; }
  glm::vec3 scale() const { return scale_; }
  glm::vec4 color() const { return color_; }
  virtual void render() const {}
  virtual void render_bounds() const {}

protected:
  glm::vec3 size_ = glm::vec3{1.0f, 1.0f, 1.0f};
  glm::vec3 position_ = glm::vec3{0.0f, 0.0f, 0.0f};
  glm::vec3 rotation_ = glm::vec3{0.0f, 0.0f, 0.0f};
  glm::vec3 scale_ = glm::vec3{1.0f, 1.0f, 1.0f};
  glm::vec3 center_ = glm::vec3{0.0f, 0.0f, 0.0f};
  glm::vec4 color_ = glm::vec4{1.0f, 0.0f, 1.0f, 1.0f};
};


}  // namespace apeiron::engine


#endif  // APEIRON_ENGINE_ENTITY_H
