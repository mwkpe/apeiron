#ifndef APEIRON_ENGINE_ENTITY_H
#define APEIRON_ENGINE_ENTITY_H


#include <string_view>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>


namespace apeiron::engine {


class Entity
{
public:
  Entity() = default;
  virtual ~Entity() = default;

  void set_parent(const Entity* parent) { parent_ = parent; }
  void set_position(float x, float y, float z) { position_ = glm::vec3{x, y, z}; }
  void set_position(const glm::vec3& position) { position_ = position; }
  void set_origin(float x, float y, float z) { origin_ = glm::vec3{x, y, z}; }
  void set_origin(const glm::vec3& origin) { origin_ = origin; }
  void set_rotation_origin(float x, float y, float z) { rotation_origin_ = glm::vec3{x, y, z}; }
  void set_rotation_origin(const glm::vec3& origin) { rotation_origin_ = origin; }
  void set_size(float x, float y, float z) { size_ = glm::vec3{x, y, z}; }
  void set_size(const glm::vec3& size) { size_ = size; }
  void set_scale(float x, float y, float z) { scale_ = glm::vec3{x, y, z}; }
  void set_scale(const glm::vec3& scale) { scale_ = scale; }
  void set_rotation(const glm::quat& rotation) { rotation_ = rotation; }
  void set_rotation_deg(float x, float y, float z) {
      rotation_ = glm::quat{glm::radians(glm::vec3{x, y, z})}; }
  void set_rotation_deg(const glm::vec3& rotation) {
      rotation_ = glm::quat{glm::radians(rotation)}; }
  void set_rotation_rad(float x, float y, float z) { rotation_ = glm::quat{glm::vec3{x, y, z}}; }
  void set_rotation_rad(const glm::vec3& rotation) { rotation_ = glm::quat{rotation}; }

  [[nodiscard]] const Entity* parent() const { return parent_; };

  [[nodiscard]] glm::vec3 position() const { return position_; }
  [[nodiscard]] glm::vec3 position(float x, float y, float z) const { return position_ +
      glm::vec3{x, y, z}; }
  [[nodiscard]] glm::vec3 position(const glm::vec3& offset) const { return position_ + offset; }

  [[nodiscard]] glm::vec3 position2d() const { return glm::vec3{position_.x, 0.0f, position_.z}; }
  [[nodiscard]] glm::vec3 position2d(float height) const { return position2d() +
      glm::vec3{0.0f, height, 0.0f}; }

  [[nodiscard]] glm::vec3 origin() const { return origin_; }
  [[nodiscard]] glm::vec3 rotation_origin() const { return rotation_origin_; }
  [[nodiscard]] glm::vec3 size() const { return size_; }
  [[nodiscard]] glm::vec3 scale() const { return scale_; }
  [[nodiscard]] glm::quat rotation() const { return rotation_; }
  [[nodiscard]] glm::vec3 rotation_rad() const { return glm::eulerAngles(rotation_); }
  [[nodiscard]] glm::vec3 rotation_deg() const { return glm::degrees(glm::eulerAngles(rotation_)); }

  virtual void render() const {}
  virtual void render_bounds() const {}

protected:
  const Entity* parent_ = nullptr;
  glm::vec3 position_ = glm::vec3{0.0f, 0.0f, 0.0f};
  glm::vec3 origin_ = glm::vec3{0.0f, 0.0f, 0.0f};
  glm::vec3 rotation_origin_ = glm::vec3{0.0f, 0.0f, 0.0f};
  glm::vec3 size_ = glm::vec3{1.0f, 1.0f, 1.0f};
  glm::vec3 scale_ = glm::vec3{1.0f, 1.0f, 1.0f};
  glm::quat rotation_ = glm::quat{1.0f, 0.0f, 0.0f, 0.0f};
};


}  // namespace apeiron::engine


#endif  // APEIRON_ENGINE_ENTITY_H
