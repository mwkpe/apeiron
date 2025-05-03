#ifndef APEIRON_ENGINE_CAMERA_H
#define APEIRON_ENGINE_CAMERA_H


#include <cstdint>
#include <glm/glm.hpp>


namespace apeiron::engine {


class Camera
{
public:
  enum class Direction { Forward, Backward, Left, Right };

  explicit Camera(float pitch = 0.0f, float yaw = 0.0f,
      glm::vec3 position = glm::vec3{0.0f, 0.0f, 0.0f});
  void setup(float pitch = 0.0f, float yaw = 0.0f,
      glm::vec3 position = glm::vec3{0.0f, 0.0f, 0.0f});
  void setup_orbit(float pitch, float yaw, float distance);

  void update();
  void update_orbit();

  void set_position(const glm::vec3& position) { position_ = position; }
  void set_center(const glm::vec3& center) { center_ = center; }
  void set_world_up(const glm::vec3& world_up) { world_up_ = world_up; }

  void set_pitch(float pitch) { pitch_ = pitch; }
  void set_yaw(float yaw) { yaw_ = yaw; }
  void set_distance(float distance) { distance_ = distance; }

  void move(Direction direction, float distances);
  void move(float dx, float dy, float dz) { position_ += glm::vec3{dx, dy, dz}; }
  void move_center(float dx, float dy, float dz) { center_ += glm::vec3{dx, dy, dz}; }
  void zoom(std::int32_t delta, float sensitivity);

  void invert_pitch() { pitch_ = -pitch_; }
  void orient(std::int32_t dx, std::int32_t dy, float sensitivity);
  void orbit(std::int32_t dx, std::int32_t dy, float sensitivity);

  [[nodiscard]] float pitch() const { return pitch_; }
  [[nodiscard]] float yaw() const { return yaw_; }

  [[nodiscard]] glm::vec3 position() const { return position_; }
  [[nodiscard]] glm::vec3 center() const { return center_; }
  [[nodiscard]] glm::mat4 perspective_view() const;
  [[nodiscard]] glm::mat4 isometric_view() const;

private:
  glm::vec3 position_ = glm::vec3{0.0f};
  glm::vec3 front_ = glm::vec3{0.0f, 0.0f, -1.0f};
  glm::vec3 world_up_= glm::vec3{0.0f, 1.0f, 0.0f};
  glm::vec3 right_ = glm::vec3{0.0f};
  glm::vec3 up_ = glm::vec3{0.0f};
  glm::vec3 center_ = glm::vec3{0.0f, 0.0f, 0.0f};
  float pitch_ = 0.0f;
  float yaw_ = 0.0f;
  float distance_ = 1.0f;
};


}  // namespace apeiron::engine


#endif  // APEIRON_ENGINE_CAMERA_H
