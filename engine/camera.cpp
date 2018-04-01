#include "camera.h"


#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>


apeiron::engine::Camera::Camera()
{
  reset();
}


void apeiron::engine::Camera::reset()
{
  position_ = glm::vec3(10.0f, 20.0f, 10.0f);
  front_ = glm::vec3(0.0f, 0.0f, -1.0f);
  world_up_ = glm::vec3(0.0f, 1.0f, 0.0f);
  pitch_ = -45.0f;
  yaw_ = -135.0f;
  orient(0, 0, 0);  // Apply default pitch and yaw
}


void apeiron::engine::Camera::move(Direction direction, float distance)
{
  switch (direction) {
    case Direction::Forward:
      position_ += front_ * distance;
      break;
    case Direction::Backward:
      position_ -= front_ * distance;
      break;
    case Direction::Left:
      position_ -= glm::normalize(glm::cross(front_, world_up_)) * distance;
      break;
    case Direction::Right:
      position_ += glm::normalize(glm::cross(front_, world_up_)) * distance;
      break;
  }
}


void apeiron::engine::Camera::orient(int delta_x, int delta_y, float sensitivity)
{
  yaw_ += delta_x * sensitivity;
  pitch_ += delta_y * sensitivity;
  yaw_ = yaw_ > 360.0f ? yaw_ - 360.0f : yaw_ < -360.0f ? yaw_ + 360.0f : yaw_;
  pitch_ = std::clamp(pitch_, -89.0f, 89.0f);
  front_.x = std::cos(glm::radians(yaw_)) * std::cos(glm::radians(pitch_));
  front_.y = std::sin(glm::radians(pitch_));
  front_.z = std::sin(glm::radians(yaw_)) * std::cos(glm::radians(pitch_));
  front_ = glm::normalize(front_);
  right_ = glm::normalize(glm::cross(front_, world_up_));
  up_ = glm::normalize(glm::cross(right_, front_));
}


glm::mat4 apeiron::engine::Camera::view() const
{
  return glm::lookAt(position_, position_ + front_, up_);
}
