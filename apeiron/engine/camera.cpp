#include "camera.h"


#include <cmath>
#include <glm/gtc/matrix_transform.hpp>


glm::vec3 apeiron::engine::direction_from_angles(float pitch, float yaw)
{
  const float p = glm::radians(pitch);
  const float y = glm::radians(yaw);

  return glm::normalize(glm::vec3{
      std::cos(y) * std::cos(p),
      std::sin(p),
      std::sin(y) * std::cos(p)});
}


apeiron::engine::Camera::Camera(const glm::vec3& position, const glm::vec3& front,
    const glm::vec3& up)
{
  position_ = position;
  front_ = glm::normalize(front);
  right_ = glm::normalize(glm::cross(front_, glm::normalize(up)));
  up_ = glm::normalize(glm::cross(right_, front_));
  world_up_ = up_;
}


void apeiron::engine::Camera::look_at(const glm::vec3& position, const glm::vec3& target)
{
  position_ = position;
  front_ = glm::normalize(target - position);
  rebuild_basis();
}


void apeiron::engine::Camera::set_orientation(const glm::vec3& position, const glm::vec3& front)
{
  position_ = position;
  front_ = glm::normalize(front);
  rebuild_basis();
}


void apeiron::engine::Camera::set_world_up(const glm::vec3& world_up)
{
  world_up_ = glm::normalize(world_up);
  rebuild_basis();
}


void apeiron::engine::Camera::rebuild_basis()
{
  right_ = glm::normalize(glm::cross(front_, world_up_));
  up_ = glm::normalize(glm::cross(right_, front_));
}


glm::mat4 apeiron::engine::Camera::view() const
{
  return glm::lookAt(position_, position_ + front_, up_);
}
