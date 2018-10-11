#include "camera.h"


#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>


apeiron::engine::Camera::Camera(float pitch, float yaw, glm::vec3 position)
{
  setup(pitch, yaw, position);
}


void apeiron::engine::Camera::setup(float pitch, float yaw, glm::vec3 position)
{
  position_ = position;
  front_ = glm::vec3{0.0f, 0.0f, -1.0f};
  world_up_ = glm::vec3{0.0f, 1.0f, 0.0f};
  up_ = world_up_;
  pitch_ = pitch;
  yaw_ = yaw - 90.0f;  // Look to negative z
  orient(0, 0, 0.0f);  // Apply default pitch and yaw
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


void apeiron::engine::Camera::orient(int dx, int dy, float sensitivity)
{
  yaw_ += dx * sensitivity;
  pitch_ += dy * sensitivity;
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
