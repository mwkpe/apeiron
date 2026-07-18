#ifndef APEIRON_ENGINE_CAMERA_H
#define APEIRON_ENGINE_CAMERA_H


#include <glm/glm.hpp>


namespace apeiron::engine {


[[nodiscard]] glm::vec3 direction_from_angles(float pitch, float yaw);


class Camera
{
public:
  Camera() = default;
  Camera(const glm::vec3& position, const glm::vec3& target) { look_at(position, target); }
  Camera(const glm::vec3& position, const glm::vec3& front, const glm::vec3& up);

  void look_at(const glm::vec3& position, const glm::vec3& target);
  void set_orientation(const glm::vec3& position, const glm::vec3& front);
  void set_world_up(const glm::vec3& world_up);

  [[nodiscard]] glm::vec3 position() const { return position_; }
  [[nodiscard]] glm::vec3 front() const { return front_; }
  [[nodiscard]] glm::vec3 right() const { return right_; }
  [[nodiscard]] glm::vec3 up() const { return up_; }
  [[nodiscard]] glm::vec3 world_up() const { return world_up_; }
  [[nodiscard]] glm::mat4 view() const;

private:
  void rebuild_basis();

  glm::vec3 position_ = glm::vec3{0.0f};
  glm::vec3 front_ = glm::vec3{0.0f, 0.0f, -1.0f};
  glm::vec3 right_ = glm::vec3{1.0f, 0.0f, 0.0f};
  glm::vec3 up_ = glm::vec3{0.0f, 1.0f, 0.0f};
  glm::vec3 world_up_ = glm::vec3{0.0f, 1.0f, 0.0f};
};


}  // namespace apeiron::engine


#endif  // APEIRON_ENGINE_CAMERA_H
