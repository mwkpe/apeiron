#ifndef APEIRON_ENGINE_CONTROLLER_H
#define APEIRON_ENGINE_CONTROLLER_H


#include <glm/glm.hpp>
#include "apeiron/engine/camera.h"
#include "apeiron/engine/enums.h"


namespace apeiron::engine {


class Fps_controller
{
public:
  Fps_controller() = default;
  Fps_controller(float pitch, float yaw, const glm::vec3& position) { init(pitch, yaw, position); }

  void init(float pitch, float yaw, const glm::vec3& position);

  void set_position(const glm::vec3& position) { position_ = position; }
  void set_pitch(float pitch);
  void set_yaw(float yaw);

  void move(Direction direction, float distance);
  void move(float dx, float dy, float dz) { position_ += glm::vec3{dx, dy, dz}; }
  void orient(float dx, float dy, float sensitivity);
  void invert_pitch() { pitch_ = -pitch_; }

  [[nodiscard]] float pitch() const { return pitch_; }
  [[nodiscard]] float yaw() const { return yaw_; }
  [[nodiscard]] glm::vec3 position() const { return position_; }

  void apply(Camera& camera) const;

private:
  glm::vec3 position_ = glm::vec3{0.0f};
  float pitch_ = 0.0f;
  float yaw_ = -90.0f;
};


class Orbit_controller
{
public:
  Orbit_controller() = default;
  Orbit_controller(float pitch, float yaw, float distance, const glm::vec3& center) {
      init(pitch, yaw, distance, center); }

  void init(float pitch, float yaw, float distance, const glm::vec3& center);

  void set_center(const glm::vec3& center) { center_ = center; }
  void set_distance(float distance);
  void set_min_distance(float min_distance);
  void set_pitch(float pitch);
  void set_yaw(float yaw);

  void move_center(float dx, float dy, float dz) { center_ += glm::vec3{dx, dy, dz}; }
  void orbit(float dx, float dy, float sensitivity);
  void zoom(float delta, float sensitivity);

  [[nodiscard]] float pitch() const { return pitch_; }
  [[nodiscard]] float yaw() const { return yaw_; }
  [[nodiscard]] float distance() const { return distance_; }
  [[nodiscard]] glm::vec3 center() const { return center_; }
  [[nodiscard]] glm::vec3 position() const;

  void apply(Camera& camera) const;

private:
  glm::vec3 center_ = glm::vec3{0.0f};
  float pitch_ = 0.0f;
  float yaw_ = -90.0f;
  float distance_ = 1.0f;
  float min_distance_ = 0.1f;
};


}  // namespace apeiron::engine


#endif  // APEIRON_ENGINE_CONTROLLER_H
