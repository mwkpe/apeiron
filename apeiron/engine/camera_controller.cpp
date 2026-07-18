#include "camera_controller.h"


#include <algorithm>
#include <cmath>


namespace {


constexpr float pitch_limit = 89.0f;


float wrap_angle(float degrees)
{
  return std::fmod(degrees, 360.0f);
}


}  // namespace


void apeiron::engine::Free_controller::init(float pitch, float yaw, const glm::vec3& position)
{
  set_pitch(pitch);
  set_yaw(yaw);
  position_ = position;
}


void apeiron::engine::Free_controller::set_pitch(float pitch)
{
  pitch_ = std::clamp(pitch, -pitch_limit, pitch_limit);
}


void apeiron::engine::Free_controller::set_yaw(float yaw)
{
  yaw_ = wrap_angle(yaw);
}


void apeiron::engine::Free_controller::move(Direction direction, float distance)
{
  const glm::vec3 front = direction_from_angles(pitch_, yaw_);
  const glm::vec3 right = glm::normalize(glm::cross(front, glm::vec3{0.0f, 1.0f, 0.0f}));

  switch (direction) {
    case Direction::Forward: position_ += front * distance; break;
    case Direction::Backward: position_ -= front * distance; break;
    case Direction::Left: position_ -= right * distance; break;
    case Direction::Right: position_ += right * distance; break;
  }
}


void apeiron::engine::Free_controller::orient(float dx, float dy, float sensitivity)
{
  set_yaw(yaw_ + dx * sensitivity);
  set_pitch(pitch_ + dy * sensitivity);
}


void apeiron::engine::Free_controller::apply(Camera& camera) const
{
  camera.set_orientation(position_, direction_from_angles(pitch_, yaw_));
}


void apeiron::engine::Orbit_controller::init(float pitch, float yaw, float distance,
    const glm::vec3& center)
{
  set_pitch(pitch);
  set_yaw(yaw);
  set_distance(distance);
  center_ = center;
}


void apeiron::engine::Orbit_controller::set_distance(float distance)
{
  distance_ = std::max(distance, min_distance_);
}


void apeiron::engine::Orbit_controller::set_min_distance(float min_distance)
{
  min_distance_ = min_distance;
  distance_ = std::max(distance_, min_distance_);
}


void apeiron::engine::Orbit_controller::set_pitch(float pitch)
{
  pitch_ = std::clamp(pitch, -pitch_limit, pitch_limit);
}


void apeiron::engine::Orbit_controller::set_yaw(float yaw)
{
  yaw_ = wrap_angle(yaw);
}


void apeiron::engine::Orbit_controller::orbit(float dx, float dy, float sensitivity)
{
  set_yaw(yaw_ + dx * sensitivity);
  set_pitch(pitch_ + dy * sensitivity);
}


void apeiron::engine::Orbit_controller::zoom(float delta, float sensitivity)
{
  set_distance(distance_ + delta * sensitivity);
}


glm::vec3 apeiron::engine::Orbit_controller::position() const
{
  return center_ - direction_from_angles(pitch_, yaw_) * distance_;
}


void apeiron::engine::Orbit_controller::apply(Camera& camera) const
{
  camera.set_orientation(position(), direction_from_angles(pitch_, yaw_));
}
