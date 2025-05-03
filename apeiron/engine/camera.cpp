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
  yaw_ = yaw;
  update();
}


void apeiron::engine::Camera::setup_orbit(float pitch, float yaw, float distance)
{
  pitch_ = pitch;
  yaw_ = yaw;
  distance_ = distance;
  update_orbit();
}


void apeiron::engine::Camera::update()
{
  front_.x = std::cos(glm::radians(yaw_)) * std::cos(glm::radians(pitch_));
  front_.y = std::sin(glm::radians(pitch_));
  front_.z = std::sin(glm::radians(yaw_)) * std::cos(glm::radians(pitch_));
  front_ = glm::normalize(front_);
  right_ = glm::normalize(glm::cross(front_, world_up_));
  up_ = glm::normalize(glm::cross(right_, front_));
}


void apeiron::engine::Camera::update_orbit()
{
  float yaw = glm::radians(yaw_);
  float pitch = glm::radians(pitch_);

  position_.x = center_.x + distance_ * std::cos(pitch) * std::cos(yaw);
  position_.y = center_.y + distance_ * std::sin(pitch);
  position_.z = center_.z + distance_ * std::cos(pitch) * std::sin(yaw);

  front_ = glm::normalize(center_ - position_);
  right_ = glm::normalize(glm::cross(front_, world_up_));
  up_ = glm::normalize(glm::cross(right_, front_));
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


void apeiron::engine::Camera::zoom(std::int32_t delta, float sensitivity)
{
  distance_ += static_cast<float>(delta) * sensitivity;
  update_orbit();
}


void apeiron::engine::Camera::orient(std::int32_t dx, std::int32_t dy, float sensitivity)
{
  yaw_ += static_cast<float>(dx) * sensitivity;
  pitch_ += static_cast<float>(dy) * sensitivity;
  yaw_ = yaw_ > 360.0f ? yaw_ - 360.0f : yaw_ < -360.0f ? yaw_ + 360.0f : yaw_;
  pitch_ = std::clamp(pitch_, -89.0f, 89.0f);
  update();
}


void apeiron::engine::Camera::orbit(std::int32_t dx, std::int32_t dy, float sensitivity)
{
  yaw_ += static_cast<float>(dx) * sensitivity;
  yaw_ = yaw_ > 360.0f ? yaw_ - 360.0f : yaw_ < -360.0f ? yaw_ + 360.0f : yaw_;
  pitch_ += static_cast<float>(dy) * sensitivity;
  pitch_ = std::clamp(pitch_, -89.0f, 89.0f);
  update_orbit();
}


glm::mat4 apeiron::engine::Camera::perspective_view() const
{
  return glm::lookAt(position_, position_ + front_, up_);
}


glm::mat4 apeiron::engine::Camera::isometric_view() const
{
  return glm::lookAt(center_ + position_, center_, world_up_);
}
